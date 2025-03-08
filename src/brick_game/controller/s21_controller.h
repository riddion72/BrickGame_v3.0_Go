/// @mainpage
/// @file s21_controller.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include "../snake/s21_backend.h"
#include "../race/libs21_backend_race.h"
#include <iostream>
extern "C" {
#include "../tetris/s21_backend.h"
}
// #include "../../common/header.h"

namespace s21 {

/// @brief Класс контроллера
class gameController {
 public:
  /// @brief Базовый конструктор
  /// @param gameName Имя игры
  gameController(gameName_t gameName);

  /// @brief Конструктор копированмя
  /// @param other Другой объект
  gameController(const gameController &other);

  /// @brief Десткрукторв
  ~gameController();

  /// @brief Перегрузка для оператора =
  /// @param other Другой объект
  /// @return Возвращает ссылку на объект, кугда присвоено значение
  gameController &operator=(const gameController &other);

  /// @brief Вызвать метод UserInput для нынешней игры
  void getUserInput();

  /// @brief Вызвать метод updateCurrentState для нынешней игры
  void updateState();

  /// @brief Записать в контроллер ввод игрока
  /// @param act Действие игрока
  /// @param hld Удерживается ли кнопка
  void updateUserAction(UserAction_t act, bool hld);

  /// @brief Выполнить следующий ход игры
  void makeStep();

  /// @brief Получить gameInfo
  /// @return Вовращает нынешнее состояние игры
  GameInfo_t getGameInfo();

 private:
  /// @brief Название игры
  gameName_t _gameName;

  /// @brief Указатель на объект змейки
  gameSnake *snake_g;

  /// @brief Нынешнее состояние игры
  GameInfo_t game = {nullptr, nullptr, 0, 0, 0, 0, 0};

  /// @brief Последнее действие игрока
  UserAction_t action = Nothing;

  /// @brief Зажата ли кнопка действия у игрока
  bool hold = false;
};

}  // namespace s21

#endif