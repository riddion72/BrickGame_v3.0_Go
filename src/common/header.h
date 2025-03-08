/// @mainpage header.h
/// @file header.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-07-07
///
/// @copyright Copyright (c) 2024

#ifndef S21_COMMON_H
#define S21_COMMON_H

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

/// Ширина игрового поля
#define W_SIZE 10

/// Высота игрового поля
#define H_SIZE 20

/// @brief Перечисление, содержащие в себе все возможные действия, которые может
/// совершить игрок
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Exit_game,
  Nothing
} UserAction_t;

typedef enum { Tetris, Snake, Race, Not_a_game } gameName_t;

/// @brief Структура игрового состояния
/// @param field Двумерный массив поля
/// @param next Двумерный массив след фигуры
/// @param score Счет игры
/// @param high_score Максимальный рекорд
/// @param level Нынешний уровень
/// @param speed Ныняшняя скорость
/// @param pause Пауза игры
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif
