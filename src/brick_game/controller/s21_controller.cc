#include "s21_controller.h"

namespace s21 {

gameController::gameController(gameName_t gameName)
    : _gameName(gameName), snake_g(nullptr) {
  if (_gameName == Snake) {
    snake_g = new gameSnake();
  } else if (_gameName == Race) {
    InitRace();
  }
}

gameController::gameController(const gameController &other) {
  if (this != &other) {
    *this = other;
  }
}

gameController::~gameController() {
  if (_gameName == Snake) {
    delete snake_g;
  } else if (_gameName == Tetris) {
    s21_terminate();
  } else if (_gameName == Race) {
    FreeGameInfo();
  }
}

gameController &gameController::operator=(const gameController &other) {
  if (this != &other) {
    _gameName = other._gameName;
    snake_g = other.snake_g;
    game = other.game;
    action = other.action;
    hold = other.hold;
  }
  return *this;
}

void gameController::getUserInput() {
  if (_gameName == Snake) {
    snake_g->userInput(action, hold);
  } else if (_gameName == Tetris) {
    userInput(action, hold);
  } else if (_gameName == Race) {
    UserInput(action, hold);
  }
}

void gameController::updateState() {
  if (_gameName == Snake) {
    game = snake_g->updateCurrentState();
  } else if (_gameName == Tetris) {
    game = updateCurrentState();
  } else if (_gameName == Race) {
    game = *UpdateGameInfo(); // TOD
  }
}

void gameController::makeStep() {
  if (_gameName == Snake) {
    snake_g->userInput(Action, true);
  } else if (_gameName == Tetris) {
    userInput(Down, true);
  } else if (_gameName == Race) {
    UserInput(Action, true);
  }
}

void gameController::updateUserAction(UserAction_t act, bool hld) {
  action = act;
  hold = hld;
}

GameInfo_t gameController::getGameInfo() { return game; }

}  // namespace s21