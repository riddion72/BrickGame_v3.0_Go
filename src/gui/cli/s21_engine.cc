#include "s21_engine.h"

int main() {
  s21_init_frontend();
  UserAction_t key = Nothing;
  gameName_t gameName = Not_a_game;
  while (key != Terminate) {
    key = s21_get_key();
    if (key == Left) {
      gameName = Tetris;
    } else if (key == Right) {
      gameName = Snake;
    } else if (key == Down) {
      gameName = Race;
    } else {
      gameName = Not_a_game;
    }
    key = s21::gameLoop(gameName, key);
    s21::sleep_ms(SLEEP_MS);
    s21_update_window();
  }
  endwin();
  return 0;
}

UserAction_t s21::gameLoop(gameName_t gameName, UserAction_t key) {
  s21::gameController controller(gameName);
  UserAction_t prev_key = Nothing;
  bool hold = false;
  int step = 0;
  while (gameName != Not_a_game && key != Terminate && key != Exit_game) {
    key = s21_get_key();
    hold = prev_key == key ? true : false;
    prev_key = key;
    if (step > controller.getGameInfo().speed) {
      controller.makeStep();
      step = 0;
    }
    controller.updateUserAction(key, hold);
    controller.getUserInput();
    controller.updateState();
    s21_print_game(controller.getGameInfo(), gameName);
    s21::sleep_ms(SLEEP_MS);
    step++;
  }
  return key;
}

void s21::sleep_ms(int ms_sleep) {
  struct timespec ts;
  ts.tv_sec = ms_sleep / 1000;
  ts.tv_nsec = (ms_sleep % 1000) * 1000000;
  nanosleep(&ts, NULL);
}