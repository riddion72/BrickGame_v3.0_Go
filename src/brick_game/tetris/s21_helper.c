#include "s21_helper.h"

int **s21_create_matrix(int x, int y) {
  int **res = (int **)calloc(y, sizeof(int *));
  for (int i = 0; i < y; i++) {
    res[i] = (int *)calloc(x, sizeof(int));
  }
  return res;
}

void s21_delete_matrix(int ***matrix, int y) {
  for (int i = 0; *matrix && i < y; i++) {
    free((*matrix)[i]);
  }
  free(*matrix);
  *matrix = NULL;
}

int s21_get_high_score(void) {
  int res = 0;
  FILE *file;
  if ((file = fopen(SCORE_FILE_TETRIS, "r"))) {
    fscanf(file, "%d", &res);
    fclose(file);
  }
  return res;
}

void s21_save_high_score(void) {
  GameInfo_t *state = s21_get_state();
  FILE *file;
  file = fopen(SCORE_FILE_TETRIS, "w+");
  if (file) {
    fprintf(file, "%d", state->high_score);
    fclose(file);
  }
}

int **s21_init_shape(void) {
  int **brick = s21_create_matrix(NEXT_SIZE, NEXT_SIZE);
  int seed = rand() % BRICK_COUNT;
  switch (seed) {
    case 0:  // l
      brick[2][0] = seed + 1;
      brick[2][1] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
    case 1:  // o
      brick[1][1] = seed + 1;
      brick[1][2] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][1] = seed + 1;
      break;
    case 2:  // T
      brick[1][2] = seed + 1;
      brick[2][1] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
    case 3:  // z
      brick[1][1] = seed + 1;
      brick[1][2] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
    case 4:  // s
      brick[1][2] = seed + 1;
      brick[1][3] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][1] = seed + 1;
      break;
    case 5:  // L
      brick[1][3] = seed + 1;
      brick[2][1] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
    case 6:  // J
      brick[1][1] = seed + 1;
      brick[2][1] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
  }
  return brick;
}

void s21_transpose(int **matrix) {
  for (int i = 0; i < NEXT_SIZE; i++) {
    for (int j = i; j < NEXT_SIZE; j++) {
      int stash = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = stash;
    }
  }
}

void s21_mirror(int **matrix) {
  for (int i = 0; matrix[2][2] > 2 && i < NEXT_SIZE; i++) {
    for (int j = 0; j < NEXT_SIZE / 2; j++) {
      int stash = matrix[i][j];
      matrix[i][j] = matrix[i][NEXT_SIZE - 1 - j];
      matrix[i][NEXT_SIZE - 1 - j] = stash;
    }
  }
}

void s21_copy_figure(int **dir) {
  brick_t *brick = s21_get_brick();
  for (int i = 0; i < NEXT_SIZE; i++) {
    for (int j = 0; j < NEXT_SIZE; j++) {
      dir[i][j] = brick->matrix[i][j];
    }
  }
}

int s21_check_brick_pos(int **matrix, int wall) {
  int res = -1;
  int start;
  int step;
  if (wall == Left) {
    start = 0;
    step = 1;
  } else {
    start = 4;
    step = -1;
  }
  for (int j = start; res < 0 && j * step < NEXT_SIZE - start; j += step) {
    for (int i = 0; res < 0 && i < NEXT_SIZE; i++) {
      if (matrix[i][j]) res = j;
    }
  }
  return res;
}

void s21_check_lines(void) {
  GameInfo_t *state = s21_get_state();
  int num_rows = 0;
  for (int i = 0; i < H_SIZE; i++) {
    int row_full = 1;
    for (int j = 0; row_full && j < W_SIZE; j++) {
      row_full = state->field[i][j];
    }
    if (row_full) {
      s21_move_field_down(i);
      num_rows++;
    }
  }
  while (num_rows) {
    num_rows--;
    state->score += pow(2, num_rows) * 100;
  }
  if (state->score > state->high_score) {
    state->high_score = state->score;
  }
}

void s21_move_field_down(int row) {
  GameInfo_t *state = s21_get_state();
  for (int i = 0; i < W_SIZE && state->field; i++) {
    for (int j = row; j >= 0; j--) {
      if (j == 0) {
        state->field[j][i] = 0;
      } else {
        state->field[j][i] = state->field[j - 1][i];
      }
    }
  }
}

void s21_copy_figure_to_field(void) {
  GameInfo_t *state = s21_get_state();
  brick_t *brick = s21_get_brick();
  for (int i = 0; i < NEXT_SIZE; i++) {
    for (int j = 0; j < NEXT_SIZE; j++) {
      if (i + brick->pos_y >= 0 && j + brick->pos_x >= 0 && brick->matrix[i][j])
        state->field[i + brick->pos_y][j + brick->pos_x] = brick->matrix[i][j];
    }
  }
}

void s21_delete_figure_from_field(void) {
  GameInfo_t *state = s21_get_state();
  brick_t *brick = s21_get_brick();
  for (int i = 0; i < NEXT_SIZE; i++) {
    for (int j = 0; j < NEXT_SIZE; j++) {
      if (i + brick->pos_y >= 0 && j + brick->pos_x >= 0 && brick->matrix[i][j])
        state->field[i + brick->pos_y][j + brick->pos_x] = 0;
    }
  }
}

int s21_check_colission(int **brick, int pos_x, int pos_y) {
  int res = 0;
  GameInfo_t *state = s21_get_state();
  for (int i = 0; i < NEXT_SIZE && !res; i++) {
    for (int j = 0; j < NEXT_SIZE && !res; j++) {
      if (brick[i][j] && i + pos_y >= H_SIZE) {
        res = 1;
      }
    }
  }
  for (int i = 0; i < H_SIZE && !res; i++) {
    for (int j = 0; j < W_SIZE && !res; j++) {
      res = s21_check_colission_with_field(j - pos_x, i - pos_y,
                                           state->field[i][j], brick);
    }
  }
  return res;
}

int s21_check_colission_with_field(int pos_x, int pos_y, int cel, int **brick) {
  int res = 0;
  for (int i = 0; i < NEXT_SIZE && !res; i++) {
    for (int j = 0; j < NEXT_SIZE && !res; j++) {
      if (cel && brick[i][j] && pos_x == j && pos_y == i) {
        res = 1;
      }
    }
  }
  return res;
}

void s21_check_level(void) {
  GameInfo_t *state = s21_get_state();
  state->level = state->score / LVL_UP + 1;
  if (state->level > MAX_LVL) {
    state->level = MAX_LVL;
  }
  state->speed = (MAX_LVL - state->level) + 1;
}
