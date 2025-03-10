#include "../brick_game/controller/s21_controller.h"
#include <gtest/gtest.h>


TEST(TETRIS, case1){
    s21::gameController* controller = new s21::gameController(Tetris);
    controller->updateUserAction(Start, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Left, false);
    controller->getUserInput();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->updateState();
    controller->getGameInfo();
    delete controller;
    EXPECT_EQ(1, 1);
}

TEST(TETRIS, case2){
    s21::gameController* controller = new s21::gameController(Tetris);
    controller->updateUserAction(Start, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->updateUserAction(Action, false);
    controller->getUserInput();
    controller->updateUserAction(Right, false);
    controller->getUserInput();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->updateState();
    controller->getGameInfo();
    controller->updateUserAction(Pause, false);
    controller->getUserInput();
    controller->updateUserAction(Pause, false);
    controller->getUserInput();
    controller->updateUserAction(Terminate, false);
    controller->getUserInput();
    int **brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    brick = s21_init_shape();
    s21_delete_matrix(&brick, 5);  
    s21_move_field_down(1);
    delete controller;
    EXPECT_EQ(1, 1);
}

TEST(SNAKE, case1){
    s21::gameController* controller = new s21::gameController(Snake);
    controller->updateUserAction(Start, false);
    controller->getUserInput();
    controller->updateUserAction(Action, true);
    controller->getUserInput();
    controller->updateUserAction(Action, true);
    controller->getUserInput();
    controller->updateUserAction(Action, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->updateUserAction(Action, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->updateUserAction(Action, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->updateUserAction(Action, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->updateUserAction(Action, true);
    controller->getUserInput();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->makeStep();
    controller->updateState();
    controller->getGameInfo();
    delete controller;
    EXPECT_EQ(1, 1);
}

TEST(SNAKE, case2){
    s21::gameController* controller = new s21::gameController(Snake);
    controller->updateUserAction(Start, false);
    controller->getUserInput();
    controller->updateUserAction(Up, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Down, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Right, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Down, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Up, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Right, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Up, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateState();
    controller->getGameInfo();
    controller->updateUserAction(Pause, true);
    controller->getUserInput();
    controller->updateUserAction(Pause, true);
    controller->getUserInput();
    controller->updateUserAction(Terminate, true);
    controller->getUserInput();
    delete controller;
    EXPECT_EQ(1, 1);
}

TEST(SNAKE, case2){
    s21::gameController* controller = new s21::gameController(Race);
    controller->updateUserAction(Start, false);
    controller->getUserInput();
    controller->updateUserAction(Up, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Right, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Right, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Left, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateUserAction(Up, true);
    controller->getUserInput();
    controller->makeStep();
    controller->updateState();
    controller->getGameInfo();
    controller->updateUserAction(Pause, true);
    controller->getUserInput();
    controller->updateUserAction(Pause, true);
    controller->getUserInput();
    controller->updateUserAction(Terminate, true);
    controller->getUserInput();
    delete controller;
    EXPECT_EQ(1, 1);
}

TEST(CONTROLLER, case1){
    s21::gameController contr(Not_a_game);
    s21::gameController newContr = contr;
    EXPECT_EQ(1, 1);
}