#include <iostream>
#include "../include/GameMode.h"

const std::string GameMode::EASY = "easy";
const std::string GameMode::MEDIUM = "medium";
const std::string GameMode::HARD = "hard";
const std::string GameMode::HARD_PLUS = "hard+";

bool GameMode::isValidMode(const std::string &mode) {
    return mode == GameMode::EASY || mode == GameMode::MEDIUM || mode == GameMode::HARD || mode == GameMode::HARD_PLUS;
}
