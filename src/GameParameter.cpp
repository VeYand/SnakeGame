#include "../include/GameParameter.h"

const int GameParameter::MIN_WIDTH = 8;
const int GameParameter::MIN_HEIGHT = 8;
const std::string GameParameter::INVALID_FIELD_SIZE_MESSAGE =
        "[WARNING] Field's width and height cannot be less than " +
        std::to_string(GameParameter::MIN_WIDTH) + " and " +
        std::to_string(GameParameter::MIN_HEIGHT) + " symbols!";
const std::string GameParameter::INVALID_GAME_MODE_MESSAGE = "[WARNING] Invalid game mode!";
const std::string GameParameter::INVALID_DIRECTION_MESSAGE = "[WARNING] Invalid direction: ";
const std::string GameParameter::VICTORY_MESSAGE = "Победа!";
const std::string GameParameter::TAIL_HIT_MESSAGE = "Ударился об свой хвост";
const std::string GameParameter::WALL_HIT_MESSAGE = "Ударился об стену";
const char GameParameter::WALL_SYMBOL = '#';
const char GameParameter::BACK_WALL_SYMBOL = '.';
const char GameParameter::SNAKE_HEAD_SYMBOL = '&';
const char GameParameter::SNAKE_TAIL_SYMBOL = '@';
const char GameParameter::APPLE_SYMBOL = '%';
const int GameParameter::DEFAULT_SNAKE_LEN = 2;
const int GameParameter::KEYBOARD_LISTENER_TIMEOUT = 50;
const int GameParameter::KEY_DOWN_CODE = 0x8000;
const int GameParameter::MAX_KEYBOARD_CODE = 256;

