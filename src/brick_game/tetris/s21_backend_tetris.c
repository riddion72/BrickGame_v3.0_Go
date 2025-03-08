#include "s21_backend.h"

GameInfo_t updateCurrentState(void) { return *s21_get_state(); }

void userInput(UserAction_t action, bool hold) {
  game_t *game = s21_get_game();
  static GameEvent_t fsm_table[5][10] = {
      {s21_start_game, NULL, s21_terminate, NULL, NULL, NULL, NULL, NULL,
       s21_terminate, NULL},  // start
      {NULL, s21_pause, s21_terminate, s21_left, s21_right, NULL, s21_down,
       s21_action, s21_terminate, NULL},  // move
      {s21_attach, s21_attach, s21_terminate, s21_attach, s21_attach,
       s21_attach, s21_attach, s21_attach, s21_terminate,
       s21_attach},  // attach
      {s21_start_game, NULL, s21_terminate, NULL, NULL, NULL, NULL, NULL,
       s21_terminate, NULL},  // end
      {NULL, s21_pause, s21_terminate, NULL, NULL, NULL, NULL, NULL,
       s21_terminate, NULL}};  // pause

  if (action == Down && !hold) {
    action = Nothing;
  }
  GameEvent_t event = fsm_table[game->game_state][action];
  // s21_update_timer();
  if (event) {
    event();
  }
}

void s21_start_game(void) {
  game_t *game = s21_get_game();
  srand(time(NULL));
  s21_init_next();
  s21_init_state();
  s21_spawn();
  game->game_state = MOVE;
}

void s21_action(void) {
  brick_t *brick = s21_get_brick();
  s21_delete_figure_from_field();
  int **buff = s21_create_matrix(NEXT_SIZE, NEXT_SIZE);
  s21_copy_figure(buff);
  s21_transpose(buff);
  s21_mirror(buff);
  int pos_buf = brick->pos_x;
  int pos_left = s21_check_brick_pos(buff, Left);
  int pos_right = s21_check_brick_pos(buff, Right);
  while (pos_buf + pos_left < 0) {
    pos_buf += 1;
  }
  while (pos_buf + pos_right >= W_SIZE) {
    pos_buf -= 1;
  }
  if (!s21_check_colission(buff, pos_buf, brick->pos_y)) {
    s21_delete_matrix(&brick->matrix, NEXT_SIZE);
    brick->matrix = buff;
    brick->pos_x = pos_buf;
  } else {
    s21_delete_matrix(&buff, NEXT_SIZE);
  }
  s21_copy_figure_to_field();
}

void s21_right(void) {
  brick_t *brick = s21_get_brick();
  s21_delete_figure_from_field();
  brick->pos_x += 1;
  int pos = s21_check_brick_pos(brick->matrix, Right);
  if (brick->pos_x + pos >= W_SIZE ||
      s21_check_colission(brick->matrix, brick->pos_x, brick->pos_y)) {
    brick->pos_x -= 1;
  }
  s21_copy_figure_to_field();
}

void s21_left(void) {
  brick_t *brick = s21_get_brick();
  s21_delete_figure_from_field();
  brick->pos_x -= 1;
  int pos = s21_check_brick_pos(brick->matrix, Left);
  if (brick->pos_x + pos < 0 ||
      s21_check_colission(brick->matrix, brick->pos_x, brick->pos_y)) {
    brick->pos_x += 1;
  }
  s21_copy_figure_to_field();
}

void s21_down(void) {
  game_t *game = s21_get_game();
  brick_t *brick = s21_get_brick();
  s21_delete_figure_from_field();
  brick->pos_y += 1;
  if (s21_check_colission(brick->matrix, brick->pos_x, brick->pos_y)) {
    brick->pos_y -= 1;
    game->game_state = ATTACH;
  } else {
    game->game_state = MOVE;
  }
  s21_copy_figure_to_field();
}

void s21_spawn(void) {
  game_t *game = s21_get_game();
  GameInfo_t *state = s21_get_state();
  brick_t *brick = s21_get_brick();
  brick_t *next = s21_get_next();
  if (brick->matrix) {
    s21_delete_matrix(&brick->matrix, NEXT_SIZE);
  }
  brick->matrix = next->matrix;
  brick->pos_x = next->pos_x;
  brick->pos_y = next->pos_y;
  next->matrix = s21_init_shape();
  if (s21_check_colission(brick->matrix, brick->pos_x, brick->pos_y)) {
    s21_delete_matrix(&state->field, H_SIZE);
    state->pause = 3;
    game->game_state = END;
  } else {
    game->game_state = MOVE;
    state->next = next->matrix;
    s21_copy_figure_to_field();
  }
}

void s21_attach(void) {
  s21_check_lines();
  s21_check_level();
  s21_spawn();
}

void s21_terminate(void) {
  GameInfo_t *state = s21_get_state();
  brick_t *brick = s21_get_brick();
  brick_t *next = s21_get_next();
  if (state->field) {
    s21_delete_matrix(&state->field, H_SIZE);
  }
  state->next = NULL;
  if (brick->matrix) {
    s21_delete_matrix(&brick->matrix, NEXT_SIZE);
  }
  if (next->matrix) {
    s21_delete_matrix(&next->matrix, NEXT_SIZE);
  }
  s21_save_high_score();
  game_t *game = s21_get_game();
  state->pause = 0;
  game->game_state = START;
}

// void s21_update_timer() {
//   GameInfo_t *state = s21_get_state();
//   game_t *game = s21_get_game();
//   if (game->game_state == MOVE) {
//     state->speed++;
//     if (state->speed > 11 - state->level) {
//       s21_down();
//       state->speed = 0;
//     }
//   }
// }

void s21_pause(void) {
  GameInfo_t *state = s21_get_state();
  game_t *game = s21_get_game();
  if (!state->pause) {
    state->pause = 1;
    game->game_state = PAUSE;
  } else {
    game->game_state = MOVE;
    state->pause = 0;
  }
}
