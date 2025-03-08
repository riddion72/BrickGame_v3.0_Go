/// @mainpage
/// @file s21_apple.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_APPLE_H
#define S21_APPLE_H

#include <random>

#include "s21_snake.h"

namespace s21 {

/// @brief Класс яблока
class apple {
 public:
  /// @brief Стандартный конструктор класса
  apple();

  /// @brief Спавн нового яблока на поле
  /// @param free_cells Список свободных клеток
  /// @return Возвращает ссылку на новое яблоко
  apple &spawn(std::vector<point_t> free_cells);

  /// @brief Получаем поозицию яблока
  /// @return Возвращает координаты яблока на поле
  point_t getPos();

 private:
  /// @brief Позиция яблока
  point_t pos;
};
}  // namespace s21

#endif