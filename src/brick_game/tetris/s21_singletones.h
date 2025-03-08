/// @mainpage
/// @file s21_singletones.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_SINGLETONES_H
#define S21_SINGLETONES_H

#include "s21_backend.h"
#include "s21_helper.h"

/// @brief Получение состояния игры
/// @return указатель на нынешнее состояние
GameInfo_t *s21_get_state(void);

/// @brief Получение состояния автомата
/// @return Указатель на состояние автомата
game_t *s21_get_game(void);

/// @brief Получение фигуры
/// @return указатель на нынешнюю фигуру
brick_t *s21_get_brick(void);

/// @brief Получение след фигуры
/// @return Указатель на след фигуру
brick_t *s21_get_next(void);

/// @brief Инициализация след фигуры
void s21_init_next(void);

/// @brief Инициализация состояния игры
void s21_init_state(void);

#endif
