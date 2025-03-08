/// @mainpage
/// @file s21_snake.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_SNAKE_H
#define S21_SNAKE_H

#include <vector>

namespace s21 {

/// @brief enum с направлениями змейки
enum dir_e { UP, DOWN, LEFT, RIGHT };

/// @brief структура точки
struct point_t {
  /// @brief позиция по х
  int x;
  /// @brief позиция по у
  int y;

  /// @brief Стандартный конструктор точки
  /// @param xp Положение по х
  /// @param yp Положение по у
  point_t(int xp = 0, int yp = 0) : x(xp), y(yp) {}
  /// @brief Перегрузка оператора ==
  /// @param other точка, с которой нужно сравнить this
  /// @return true - точки совпадают, false - точки в разных местах
  bool operator==(const point_t &other) {
    return (x == other.x && y == other.y);
  }
};

/// @brief структура змейки
class snake {
 public:
  /// @brief стандартный конструктор
  snake();

  /// @brief Получение координат змейки
  /// @return ссылка на вектор со всеми точками тела змейки
  std::vector<point_t> &getBody();
  /// @brief Совершение шага вперед
  void moveForvard();
  /// @brief Удаление хвостовой клекти
  void notGrow();

  /// @brief Направление, куда смотрит голова
  /// @return Направление движения
  dir_e getDir();
  /// @brief Установка направления движения
  /// @param new_dir Новое направление движения змейки
  void setDir(dir_e new_dir);

 private:
  /// @brief Вектор со всеми точками змеи
  std::vector<point_t> _body;
  /// @brief Направление движения
  dir_e _direction = RIGHT;
};

}  // namespace s21

#endif