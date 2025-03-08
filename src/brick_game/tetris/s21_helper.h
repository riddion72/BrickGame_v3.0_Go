/// @mainpage
/// @file s21_helper.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_HELPER_H
#define S21_HELPER_H

/// @brief Структура игрового кирпичика (тетриса)
/// @param brick Ссылка на двумерный массив с фигурой
/// @param pos_x Положение тетриса по оси х
/// @param pos_y Положение тетриса по оси у
typedef struct {
  int **matrix;
  int pos_x;
  int pos_y;
} brick_t;

/// @brief Перечисление, содержащие в себе состояние автомата
typedef enum { START, MOVE, ATTACH, END, PAUSE } State_t;

/// @brief Структура с переменными конечного автомата
/// @param game_state Эта переменная отвечат за то, должен ли выполнятся игровой
/// цикл
typedef struct {
  State_t game_state;
} game_t;

typedef void (*GameEvent_t)(void);

#include "../../common/header.h"
#include "s21_backend.h"
#include "s21_singletones.h"

/// Размер массива с Фигурами
#define NEXT_SIZE 5

/// Кол-во очков для повышения уровня
#define LVL_UP 800

/// Максимальный уровень
#define MAX_LVL 10

/// Количество фигур
#define BRICK_COUNT 7

/// Путь до файла с рекордами
#define SCORE_FILE_TETRIS "tetris_score.txt"

/// @brief Функция по созданию матрицы
/// @param x Кол-во столбцов
/// @param y Кол-во строк
/// @return Указатель на матриц у*х
int **s21_create_matrix(int x, int y);

/// @brief Удаление матрицы
/// @param matrix Указатель на матрицу
/// @param y Кол-во строк
void s21_delete_matrix(int ***matrix, int y);

/// @brief Получение рекорда из файла
/// @return Числовое значение прошлого рекорда
int s21_get_high_score(void);

/// @brief Инициализация новой фигуры
/// @return Указатель на матрицу новой фигуры
int **s21_init_shape(void);

/// @brief Сохранение рекорда
void s21_save_high_score(void);

/// @brief Транспонирование матрицы
/// @param matrix Указатель на матрицу
void s21_transpose(int **matrix);

/// @brief Отражение матрицы
/// @param matrix Указатель на матрицу
void s21_mirror(int **matrix);

/// @brief Проверка, вышла ли фигура за стенку
/// @param matrix Указатель на матрицу с фигурой
/// @param wall Какую стенку проверить
/// @return Значени на сколько глубоко фигура вошла в стенку
int s21_check_brick_pos(int **matrix, int wall);

/// @brief Копирование фигуры
/// @param dir Куда скопировать фигуру
void s21_copy_figure(int **dir);

/// @brief Проверка линии на заполненность
void s21_check_lines(void);

/// @brief Перемещения поля вниз
/// @param row Сколько строк удаляется
void s21_move_field_down(int row);

/// @brief Копирование фигуры на поле
void s21_copy_figure_to_field(void);

/// @brief Удаление фигуры с поля
void s21_delete_figure_from_field(void);

/// @brief Проверка колизии фигуры с полем
/// @param brick Матрица фигуры
/// @param pos_x Положение фигуры по х
/// @param pos_y Положение фигуры по у
/// @return 1 - есть пересечение, 0 - нету
int s21_check_colission(int **brick, int pos_x, int pos_y);

/// @brief Проверка пересечения точки поля с фигурой
/// @param pos_x позиция по х
/// @param pos_y позиция по у
/// @param cel значение в точке поля
/// @param brick Матрица фигуры
/// @return 1 - есть пересечение, 0 - нету
int s21_check_colission_with_field(int pos_x, int pos_y, int cel, int **brick);

/// @brief Проверка уровня
void s21_check_level(void);

#endif
