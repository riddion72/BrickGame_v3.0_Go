/// @mainpage
/// @file s21_backend.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_BACKEND_TETRIS_H
#define S21_BACKEND_TETRIS_H

#include "../../common/header.h"
#include "s21_helper.h"
#include "s21_singletones.h"

typedef void (*GameEvent_t)(void);

/// @brief Проверка ввода с клавиатуры и применение необходимой функции к игре
/// @param action Действие, которое совершил игрок
void userInput(UserAction_t action, bool hold);

/// @brief Получаем состояние игры в данный момент, необходимо для отрисовки
/// @return На выходе получаем копию игрового состояния, куда записано положение
/// фигуры игрока на поле
GameInfo_t updateCurrentState(void);

/// @brief Начало игры с генерацией синглтонов
void s21_start_game(void);

/// @brief Совершение вращения игрока
void s21_action(void);

/// @brief Перемещение блока вправо
void s21_right(void);

/// @brief Перемещение блока влево
void s21_left(void);

/// @brief Перемещение блока вниз
void s21_down(void);

/// @brief Спавн новой фигруы
void s21_spawn(void);

/// @brief Пауза игры
void s21_pause(void);

/// @brief Прикрепление фигру к полю
void s21_attach(void);

/// @brief Завершение игры
void s21_terminate(void);

// void s21_update_timer(void);

#endif
