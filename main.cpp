#include "include/SnakeGame.h"
#include "include/GameMode.h"
#include <Windows.h>
#include <cstdlib>

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc < 5) {
        std::cout << "Usage: " << argv[0] << " <field_width> <field_height> <game_mode> <fps>" << std::endl;
        return 1;
    }

    int width;
    int height;
    std::string mode = argv[3];
    int fps;

    try {
        width = std::atoi(argv[1]);
        height = std::atoi(argv[2]);
        fps = std::atoi(argv[4]);
    } catch (const std::invalid_argument &e) {
        std::cerr << "[ERROR] Invalid argument!" << std::endl;
        return 1;
    }

    if (!GameMode::isValidMode(mode)) {
        std::cerr << "[ERROR] game_mode can be only " << GameMode::EASY << "||" << GameMode::MEDIUM << "||"
                  << GameMode::HARD << "||" << GameMode::HARD_PLUS << std::endl;
        return 1;
    }

    SnakeGame game(width, height, mode, fps);
    game.startGame();

    return 0;
}