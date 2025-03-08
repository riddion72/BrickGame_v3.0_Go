#include "s21_frontend.h"

void s21_init_frontend(void) {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);
  keypad(stdscr, TRUE);
  if (has_colors()) {
    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_WHITE, COLOR_WHITE);
    init_pair(7, COLOR_CYAN, COLOR_CYAN);
  }
  s21_print_rectangle(0, MAIN_WIN_Y, 0, MAIN_WIN_X);
  s21_print_rectangle(POS_FIELD_Y, FIELD_WIN_Y + POS_FIELD_Y - 1, POS_FIELD_X,
                      POS_FIELD_X + FIELD_WIN_X - 1);
  s21_print_rectangle(POS_NEXT_Y, NEXT_WIN_Y + POS_NEXT_Y, POS_NEXT_X,
                      POS_NEXT_X + NEXT_WIN_X - 1);
  mvprintw(1, W_SIZE * 2 + 7, "%s", "NEXT");
}

void s21_print_game(GameInfo_t state, gameName_t gameName) {
  s21_print_game_name(gameName);
  s21_free_field(s21_field_parameter());
  s21_free_field(s21_next_parameter());
  if (state.field != NULL) {
    s21_print_score(state);
    s21_print_game_stat(state);
    if (!state.pause && state.field) {
      s21_fill_field(state.field, s21_field_parameter());
    }
    if (!state.pause && state.next) {
      s21_fill_field(state.next, s21_next_parameter());
    }
  } else {
    s21_print_end_game(s21_field_parameter(),
                       (gameName == Snake && state.score == 200));
  }
  refresh();
}

win_t s21_field_parameter(void) {
  static win_t field = {POS_FIELD_X, POS_FIELD_Y, W_SIZE, H_SIZE};
  return field;
}

win_t s21_next_parameter(void) {
  static win_t next = {POS_NEXT_X, POS_NEXT_Y, NEXT_SIZE - 1, NEXT_SIZE - 1};
  return next;
}

void s21_update_window(void) {
  win_t field = s21_field_parameter();
  s21_free_field(field);
  mvprintw((field.sy + field.y) / 2 - 2, (field.sx + field.x) - 4,
           "SELECT GAME");
  mvprintw((field.sy + field.y) / 2, (field.sx + field.x) - 6,
           "LEFT <- TETRIS");
  mvprintw((field.sy + field.y) / 2 + 2, (field.sx + field.x) - 6,
           "RIGHT -> SNAKE");
  mvprintw((field.sy + field.y) / 2 + 4, (field.sx + field.x) - 6,
           "DOWN V RACE");
  mvprintw((field.sy + field.y) / 2 + 6, (field.sx + field.x) - 7,
           "PRESS Q to exit!");
}

void s21_print_game_name(gameName_t gameName) {
  if (gameName == Tetris) {
    mvprintw(1, 10, "%s", "Tetris");
  } else if (gameName == Snake) {
    mvprintw(1, 10, "%s", "Snake ");
  } else if (gameName == Race){
    mvprintw(1, 10, "%s", "Race");
  } else {
    mvprintw(1, 10, "%s", "      ");
  }
}

void s21_print_score(GameInfo_t state) {
  int space = 8;
  mvprintw(space, (W_SIZE + 2) * 2, "Score:");
  mvprintw(space + 1, (W_SIZE + 2) * 2, "%9d", state.score);
  mvprintw(space + 2, (W_SIZE + 2) * 2, "High");
  mvprintw(space + 3, (W_SIZE + 2) * 2, "score:");
  mvprintw(space + 4, (W_SIZE + 2) * 2, "%9d", state.high_score);
}

void s21_print_game_stat(GameInfo_t state) {
  int space = 15;
  mvprintw(space, (W_SIZE + 2) * 2, "Level:");
  mvprintw(space + 1, (W_SIZE + 2) * 2, "%9d", state.level);
  mvprintw(space + 2, (W_SIZE + 2) * 2, "Speed:");
  mvprintw(space + 3, (W_SIZE + 2) * 2, "%9d", state.speed);
  if (state.pause) {
    mvprintw(space + 6, (W_SIZE + 2) * 2 + 2, "%5s", "Pause");
  } else {
    mvprintw(space + 6, (W_SIZE + 2) * 2 + 2, "%5s", " ");
  }
}

void s21_free_field(win_t win) {
  int space_x = win.sx + 1;
  int space_y = win.sy + 1;
  for (int i = 0; i < win.y; i++) {
    for (int j = 0; j < win.x; j++) {
      mvprintw(space_y + i, space_x + j * 2, "%c", ' ');
      mvprintw(space_y + i, space_x + j * 2 + 1, "%c", ' ');
    }
  }
}

void s21_fill_field(int **field, win_t win) {
  int space_x = win.sx + 1;
  int space_y = win.sy + 1;
  for (int i = 0; i < win.y; i++) {
    for (int j = 0; j < win.x; j++) {
      if (field[i][j]) {
        attron(COLOR_PAIR(field[i][j]));
        mvaddch(space_y + i, space_x + j * 2, SIGN_LEFT);
        mvaddch(space_y + i, space_x + j * 2 + 1, SIGN_RIGHT);
        attroff(COLOR_PAIR(field[i][j]));
      }
      // } else {
      //   mvaddch(space_y + i, space_x + j * 2, '.');
      //   mvaddch(space_y + i, space_x + j * 2 + 1, '.');
      // }
    }
  }
}

void s21_print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
  mvaddch(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(bottom_y, i, ACS_LRCORNER);
}

void s21_print_end_game(win_t field, bool is_win) {
  if (is_win) {
    mvprintw((field.sy + field.y) / 2 - 2, (field.sx + field.x) - 3, "YOU WIN");
  }
  mvprintw((field.sy + field.y) / 2, (field.sx + field.x) - 9,
           "PRESS ENTER to start");
  mvprintw((field.sy + field.y) / 2 + 2, (field.sx + field.x) - 7,
           "PRESS E to menu");
  mvprintw((field.sy + field.y) / 2 + 4, (field.sx + field.x) - 7,
           "PRESS Q to exit");
}

UserAction_t s21_get_key(void) {
  UserAction_t key;
  int ch = getch();
  switch (ch) {
    case '\n':
      key = Start;
      break;
    case 'p':
    case 'P':
      key = Pause;
      break;
    case 'q':
    case 'Q':
      key = Terminate;
      break;
    case KEY_LEFT:
      key = Left;
      break;
    case KEY_RIGHT:
      key = Right;
      break;
    case ' ':
      key = Action;
      break;
    case KEY_DOWN:
      key = Down;
      break;
    case KEY_UP:
      key = Up;
      break;
    case 'e':
    case 'E':
      key = Exit_game;
      break;
    default:
      key = Nothing;
  }
  flushinp();
  return key;
}
