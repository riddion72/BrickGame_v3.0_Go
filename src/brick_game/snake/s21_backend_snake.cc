#include "s21_backend.h"

namespace s21 {

gameSnake::gameSnake() : _state(START) {
  initializeStateTable();
  _instance.game = std::make_unique<GameInfo_t>();
  _instance.game->field = NULL;
  _instance.game->pause = 0;
}

gameSnake::~gameSnake() { exit(); }

void gameSnake::initializeStateTable() {
  // Start STATE
  stateTable[START][Start] = [this]() { start(); };
  stateTable[START][Terminate] = [this]() { exit(); };
  // Move STATE
  stateTable[MOVE][Pause] = [this]() { pause(); };
  stateTable[MOVE][Terminate] = [this]() { exit(); };
  stateTable[MOVE][Left] = [this]() { turnLeft(); };
  stateTable[MOVE][Right] = [this]() { turnRight(); };
  stateTable[MOVE][Up] = [this]() { turnUp(); };
  stateTable[MOVE][Down] = [this]() { turnDown(); };
  stateTable[MOVE][Action] = [this]() { nextStep(); };
  // Pause STATE
  stateTable[PAUSE][Pause] = [this]() { pause(); };
  stateTable[PAUSE][Terminate] = [this]() { exit(); };
  // End STATE
  stateTable[END][Start] = [this]() { start(); };
  stateTable[END][Terminate] = [this]() { exit(); };
}

void gameSnake::userInput(UserAction_t action, bool hold) {
  _hold = hold;
  // stepCounter();
  if (stateTable[_state][action]) {
    stateTable[_state][action]();
  }
}

GameInfo_t gameSnake::updateCurrentState() { return *_instance.game; }

void gameSnake::start() {
  _instance.game = std::make_unique<GameInfo_t>();
  _instance.game->field = createField();
  _instance.game->high_score = loadHighScore();
  _instance.game->pause = 0;
  _instance._snake = std::make_unique<snake>();
  _instance._apple = std::make_unique<apple>();
  updateLevel();
  for (auto cell : _instance._snake->getBody()) {
    copyToField(cell, false);
  }
  _instance._apple->spawn(allFreeCells());
  copyToField(_instance._apple->getPos(), true);
  _state = MOVE;
}

void gameSnake::pause() {
  if (_instance.game->pause) {
    _instance.game->pause = 0;
    _state = MOVE;
  } else {
    _instance.game->pause = 1;
    _state = PAUSE;
  }
}

void gameSnake::exit() {
  deleteField();
  _instance._apple = nullptr;
  _instance._snake = nullptr;
  saveHighScore();
}

void gameSnake::turnLeft() {
  if (_instance._snake->getDir() == dir_e::LEFT) {
    nextStep();
  } else if (_prev_step != dir_e::RIGHT) {
    _instance._snake->setDir(dir_e::LEFT);
  }
}

void gameSnake::turnRight() {
  if (_instance._snake->getDir() == dir_e::RIGHT) {
    nextStep();
  } else if (_prev_step != dir_e::LEFT) {
    _instance._snake->setDir(dir_e::RIGHT);
  }
}

void gameSnake::turnUp() {
  if (_instance._snake->getDir() == dir_e::UP) {
    nextStep();
  } else if (_prev_step != dir_e::DOWN) {
    _instance._snake->setDir(dir_e::UP);
  }
}

void gameSnake::turnDown() {
  if (_instance._snake->getDir() == dir_e::DOWN) {
    nextStep();
  } else if (_prev_step != dir_e::UP) {
    _instance._snake->setDir(dir_e::DOWN);
  }
}

void gameSnake::nextStep() {
  if (_hold) {
    _instance._snake->moveForvard();
    std::vector<point_t> body = _instance._snake->getBody();
    point_t apple = _instance._apple->getPos();

    if (checkCollision()) {
      exit();
      _instance.game->pause = 3;
      _state = END;
    } else {
      if (body.front() == apple) {
        _instance._apple->spawn(allFreeCells());
        copyToField(_instance._apple->getPos(), true);
        updateScore();
      } else {
        removeFromField(body.back());
        _instance._snake->notGrow();
      }
      copyToField(body.front(), false);
      _prev_step = _instance._snake->getDir();
      if (_instance.game->score == SNAKE_MAX_SCORE) {
        exit();
        _instance.game->pause = 2;
        _state = END;
      }
    }
  }
}

bool gameSnake::checkCollision() {
  bool collision = false;
  std::vector<point_t> body = _instance._snake->getBody();
  auto head = body.front();
  if (head.x < 0 || head.x >= W_SIZE || head.y < 0 || head.y >= H_SIZE) {
    collision = true;
  }
  for (size_t i = 1; !collision && i < body.size(); ++i) {
    if (body.front() == body[i]) {
      collision = true;
    }
  }
  return collision;
}

std::vector<point_t> gameSnake::allFreeCells() {
  std::vector<point_t> free_cells(0);
  for (int i = 0; i < H_SIZE; ++i) {
    for (int j = 0; j < W_SIZE; ++j) {
      if (!_instance.game->field[i][j]) {
        free_cells.push_back(point_t(j, i));
      }
    }
  }
  return free_cells;
}

void gameSnake::removeFromField(point_t point) {
  if (point.x >= 0 && point.x < W_SIZE && point.y >= 0 && point.y < H_SIZE &&
      _instance.game->field) {
    _instance.game->field[point.y][point.x] = 0;
  }
}

void gameSnake::copyToField(point_t point, bool is_apple) {
  if (point.x >= 0 && point.x < W_SIZE && point.y >= 0 && point.y < H_SIZE &&
      _instance.game->field) {
    _instance.game->field[point.y][point.x] = is_apple ? 1 : 2;
  }
}

int gameSnake::loadHighScore() {
  int high_score = 0;
  std::ifstream score_file(SCORE_FILE_SNAKE);
  if (score_file.is_open()) {
    score_file >> high_score;
    score_file.close();
  }
  return high_score;
}

void gameSnake::saveHighScore() {
  std::ofstream score_file(SCORE_FILE_SNAKE);
  if (score_file.is_open()) {
    score_file << _instance.game->high_score;
    score_file.close();
  }
}

int **gameSnake::createField() {
  int **field = new int *[H_SIZE];
  for (int i = 0; i < H_SIZE; ++i) {
    field[i] = new int[W_SIZE]{};
  }
  return field;
}

void gameSnake::deleteField() {
  for (int i = 0; _instance.game->field && i < H_SIZE; ++i) {
    if (_instance.game->field[i]) {
      delete[] _instance.game->field[i];
    }
  }
  if (_instance.game->field) {
    delete[] _instance.game->field;
  }
  _instance.game->field = nullptr;
}

// void gameSnake::stepCounter() {
//   if (_state == MOVE) {
//     _instance.game->speed++;
//     if (_instance.game->speed > 11 - _instance.game->level) {
//       nextStep();
//       _instance.game->speed = 0;
//     }
//   }
// }

void gameSnake::updateScore() {
  _instance.game->score++;
  if (_instance.game->score > _instance.game->high_score) {
    _instance.game->high_score = _instance.game->score;
  }
  updateLevel();
}

void gameSnake::updateLevel() {
  _instance.game->level =
      _instance.game->score / SNAKE_LEVEL_UP > SNAKE_MAX_LEVEL
          ? SNAKE_MAX_LEVEL
          : _instance.game->score / SNAKE_LEVEL_UP + 1;
  _instance.game->speed = (SNAKE_MAX_LEVEL - _instance.game->level) + 1;
}

}  // namespace s21
