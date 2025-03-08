/// @mainpage
/// @file s21_engine.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_ENGINE_H
#define S21_ENGINE_H

#include <time.h>

#include "../../brick_game/controller/s21_controller.h"
extern "C" {
#include "s21_frontend.h"
}

#define SLEEP_MS 80

namespace s21 {

/// @brief На сколько заснуть игре
/// @param ms_sleep Время в мс
void sleep_ms(int ms_sleep);

/// @brief Игровой цикл
/// @param gameName Название игры
/// @param key Последняя нажатая клавиша
/// @return возвращает последнюю нажатую клавишу
UserAction_t gameLoop(gameName_t gameName, UserAction_t key);
}  // namespace s21

#endif