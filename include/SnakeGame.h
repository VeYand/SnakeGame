#include <vector>
#include <atomic>
#include <conio.h>
#include "Anaconda.h"

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

class SnakeGame {
private:
    int width;
    int height;
    std::vector<std::vector<char>> fieldVector;

    Position baseCursorPosition;
    Anaconda anaconda;
    Position point;
    int fps;
    std::string mode;
    std::atomic<int> lastPressedKey{};
    std::atomic<bool> isGame{};

    bool isFreePosition(Position pos);

    static Position getCursorPosition();

    void setCursorPosition();

    void keyboardListener();

    void renderField();

    void handleGameLogic(char pressedKey);

    void handleEasyModeEvent();

    void handleMediumModeEvent();

    void handleHardModeEvent();

    void handleHardPlusModeEvent();

    std::string getRenderString();

    Position getNewPointPosition();

    int checkEvent();

    void endGame();

public:
    SnakeGame(int width, int height, std::string difficulty, int fps);

    void startGame();
};

#endif // SNAKE_GAME_H
