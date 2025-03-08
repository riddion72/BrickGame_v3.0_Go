/// @mainpage
/// @file s21_backend.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_BACKEND_SNAKE_H
#define S21_BACKEND_SNAKE_H

#include <fstream>
#include <functional>
#include <memory>

#include "../../common/header.h"
#include "s21_apple.h"
// #include "s21_snake.h"

/// Название файла с рекордом
#define SCORE_FILE_SNAKE "snake_score.txt"

/// Сколько яблок собрать до лвл апа
#define SNAKE_LEVEL_UP 5
/// Максимальный уровень
#define SNAKE_MAX_LEVEL 10
/// Максимальный счет для победы
#define SNAKE_MAX_SCORE 200

namespace s21 {

/// @brief Класс игры змейки
class gameSnake {
 private:
  /// @brief enum с состояниями fms
  enum GameState_e { START, MOVE, PAUSE, END };

  /// @brief Структура с указателями на объекты игры
  struct instance_t {
    std::unique_ptr<GameInfo_t> game;
    std::unique_ptr<snake> _snake;
    std::unique_ptr<apple> _apple;
  };

 public:
  /// @brief Стандартный конструктор игры
  gameSnake();

  /// @brief Деструктор игры
  ~gameSnake();

  /// @brief Метод для выполнения игрвого автомата
  /// @param action Действие игрока
  /// @param hold Зажато ли действие
  void userInput(UserAction_t action, bool hold);

  /// @brief Получение нынешнего состояния игры
  /// @return Состояние игры
  GameInfo_t updateCurrentState();

 private:
  /// @brief Старт игры
  void start();
  /// @brief Пауза
  void pause();
  /// @brief Выход из игры
  void exit();
  /// @brief Поворот влево
  void turnLeft();
  /// @brief Поворот вправо
  void turnRight();
  /// @brief Поворот вверх
  void turnUp();
  /// @brief Поворот вниз
  void turnDown();
  /// @brief Движение вперед
  void nextStep();

  /// @brief инициализация игры
  void initGame();
  /// @brief Загрузка рекорда из файла
  /// @return Значение рекорда
  int loadHighScore();
  /// @brief Сохранение рекорда
  void saveHighScore();
  // void stepCounter();

  /// @brief Проверка пересечения головы со стенками или с телом
  /// @return true - пересечение было, false - не было
  bool checkCollision();

  /// @brief Инициализация таблицы методов и состояний для fms
  void initializeStateTable();
  /// @brief Обновление рекорда
  void updateScore();
  /// @brief Обновление уровня
  void updateLevel();
  /// @brief Создание игрового поля
  /// @return Указатель на двумерный массив поля
  int **createField();
  /// @brief Удаления поля
  void deleteField();
  /// @brief Удаление точки с поля
  /// @param point Точка, которую нужно удалить
  void removeFromField(point_t point);
  /// @brief Размещение точки на поле
  /// @param point Точка, которую нужно поставить
  /// @param is_apple Является ли точка яблоком
  void copyToField(point_t point, bool is_apple);
  /// @brief Собираем все пустые точки в вектор
  /// @return Вектор со всеми свободными клектами поля
  std::vector<point_t> allFreeCells();

  /// @brief Состояние игры
  instance_t _instance;
  /// @brief Состояние автомата
  GameState_e _state;
  /// @brief Куда был произведен последний шаг
  dir_e _prev_step = RIGHT;
  /// @brief Таблица состояний конечного автомата.
  std::function<void()> stateTable[4][10];
  /// @brief Зажатие клавиши
  bool _hold = false;
};
}  // namespace s21

#endif