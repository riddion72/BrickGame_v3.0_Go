#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../../../common/header.h"
typedef struct {
    int** field;
    int** next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo;

// Функции-обертки
void* createGameController(gameName_t gameName);
void destroyGameController(void* controller);
void getUserInput(void* controller);
void updateState(void* controller);
void makeStep(void* controller);
void updateUserAction(void* controller, int action, int hold);
GameInfo getGameInfo(void* controller);

#ifdef __cplusplus
}
#endif

#endif