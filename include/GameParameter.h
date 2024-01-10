#include <iostream>

#ifndef ANACONDA_GAMEPARAMETER_H
#define ANACONDA_GAMEPARAMETER_H

class GameParameter {
public:
    static const int MIN_WIDTH;
    static const int MIN_HEIGHT;
    static const std::string INVALID_FIELD_SIZE_MESSAGE;
    static const std::string INVALID_GAME_MODE_MESSAGE;
    static const std::string INVALID_DIRECTION_MESSAGE;
    static const std::string VICTORY_MESSAGE;
    static const std::string TAIL_HIT_MESSAGE;
    static const std::string WALL_HIT_MESSAGE;
    static const char WALL_SYMBOL;
    static const char BACK_WALL_SYMBOL;
    static const char SNAKE_HEAD_SYMBOL;
    static const char SNAKE_TAIL_SYMBOL;
    static const char APPLE_SYMBOL;
    static const int DEFAULT_SNAKE_LEN;
    static const int PASS_EVENT = 0;
    static const int TAIL_HIT_EVENT = 1;
    static const int WALL_HIT_EVENT = 2;
    static const int APPLE_EATEN_EVENT = 3;
    static const int KEYBOARD_LISTENER_TIMEOUT;
    static const int KEY_DOWN_CODE;
    static const int MAX_KEYBOARD_CODE;
};

#endif //ANACONDA_GAMEPARAMETER_H
