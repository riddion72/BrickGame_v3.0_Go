#include "s21_singletones.h"

game_t *s21_get_game(void) {
  static game_t game = {START};
  return &game;
}

GameInfo_t *s21_get_state(void) {
  static GameInfo_t state = {NULL, NULL, 0, 0, 0, 0, 0};
  return &state;
}

brick_t *s21_get_brick(void) {
  static brick_t brick = {NULL, 0, 0};
  return &brick;
}

brick_t *s21_get_next(void) {
  static brick_t next = {NULL, 0, 0};
  return &next;
}

void s21_init_next(void) {
  brick_t *brick = s21_get_next();
  if (brick->matrix) {
    s21_delete_matrix(&brick->matrix, NEXT_SIZE);
  }
  brick->matrix = s21_init_shape();
  brick->pos_x = 3;
  brick->pos_y = -2;
}

void s21_init_state(void) {
  GameInfo_t *state = s21_get_state();
  if (state->field) {
    s21_delete_matrix(&state->field, H_SIZE);
  }
  state->field = s21_create_matrix(W_SIZE, H_SIZE);

  brick_t *next = s21_get_next();
  state->next = next->matrix;

  state->score = 0;
  state->high_score = s21_get_high_score();
  state->level = 1;
  state->speed = (MAX_LVL - state->level) + 1;
  state->pause = 0;
}
