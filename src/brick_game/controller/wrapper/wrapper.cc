#include "wrapper.h"
#include "../s21_controller.h"

extern "C" {
    void* createGameController(gameName_t gameName) {
        return new s21::gameController(static_cast<gameName_t>(gameName));
    }

    void destroyGameController(void* controller) {
        delete static_cast<s21::gameController*>(controller);
    }

    void getUserInput(void* controller) {
        static_cast<s21::gameController*>(controller)->getUserInput();
    }

    void updateState(void* controller) {
        static_cast<s21::gameController*>(controller)->updateState();
    }

    void makeStep(void* controller) {
        static_cast<s21::gameController*>(controller)->makeStep();
    }

    void updateUserAction(void* controller, int action, int hold) {
        static_cast<s21::gameController*>(controller)->updateUserAction(
            static_cast<UserAction_t>(action), 
            static_cast<bool>(hold)
        );
    }

    GameInfo getGameInfo(void* controller) {
        auto info = static_cast<s21::gameController*>(controller)->getGameInfo();
        GameInfo result;
        // Копируем данные из C++ структуры в C структуру
        result.field = info.field;
        result.next = info.next;
        result.score = info.score;
        result.high_score = info.high_score;
        result.level = info.level;
        result.speed = info.speed;
        result.pause = info.pause;
        return result;
    }
}