#include "s21_apple.h"

namespace s21 {

apple::apple() {
  pos.x = 0;
  pos.y = 0;
}

apple &apple::spawn(std::vector<point_t> free_cells) {
  std::random_device rand_dev;
  std::mt19937 gen(rand_dev());
  std::uniform_int_distribution<> distr(0, free_cells.size() - 1);
  pos = free_cells.at(distr(gen));
  return *this;
}

point_t apple::getPos() { return pos; }

}  // namespace s21