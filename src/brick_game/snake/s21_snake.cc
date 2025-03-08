#include "s21_snake.h"

namespace s21 {

snake::snake() {
  _body.push_back(point_t(4, 10));
  _body.push_back(point_t(3, 10));
  _body.push_back(point_t(2, 10));
  _body.push_back(point_t(1, 10));
}

std::vector<point_t> &snake::getBody() { return _body; }

void snake::moveForvard() {
  auto head = _body.begin();
  if (_direction == UP) {
    _body.insert(head, point_t(head->x, head->y - 1));
  } else if (_direction == DOWN) {
    _body.insert(head, point_t(head->x, head->y + 1));
  } else if (_direction == LEFT) {
    _body.insert(head, point_t(head->x - 1, head->y));
  } else {
    _body.insert(head, point_t(head->x + 1, head->y));
  }
}

void snake::notGrow() { _body.pop_back(); }

dir_e snake::getDir() { return _direction; }

void snake::setDir(dir_e new_dir) { _direction = new_dir; }

}  // namespace s21