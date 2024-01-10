#include <thread>
#include <iostream>
#include <chrono>
#include "../include/SnakeGame.h"
#include "../include/GameMode.h"
#include "../include/GameParameter.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <utility>

Position SnakeGame::getCursorPosition() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

    if (GetConsoleScreenBufferInfo(hConsole, &bufferInfo)) {
        int currentX = bufferInfo.dwCursorPosition.X;
        int currentY = bufferInfo.dwCursorPosition.Y;
        return {currentX, currentY};
    }
    return {0, 0};
}

void SnakeGame::setCursorPosition() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD newPosition;
    newPosition.X = static_cast<short>(this->baseCursorPosition.getX());
    newPosition.Y = static_cast<short>(this->baseCursorPosition.getY());
    SetConsoleCursorPosition(hConsole, newPosition);
}

void SnakeGame::keyboardListener() {
    while (this->isGame) {
        for (int key = 0; key < GameParameter::MAX_KEYBOARD_CODE; ++key) {
            if (GetAsyncKeyState(key) & GameParameter::KEY_DOWN_CODE) {
                char charKey = static_cast<char>(key);
                if (ControlKeys::isValidKey(charKey)) {
                    lastPressedKey.store(charKey, std::memory_order_relaxed);
                }
            }
        }

        std::this_thread::sleep_for(
                std::chrono::milliseconds(GameParameter::KEYBOARD_LISTENER_TIMEOUT));
    }
}

void SnakeGame::renderField() {
    this->fieldVector.clear();
    for (int x = 0; x < this->width; x++) {
        std::vector<char> verticalVector;
        for (int y = 0; y < this->height; y++) {
            if (x == 0) {
                verticalVector.push_back(GameParameter::WALL_SYMBOL);
            } else if (x == (width - 1)) {
                verticalVector.push_back(GameParameter::WALL_SYMBOL);
            } else if (y == 0) {
                verticalVector.push_back(GameParameter::WALL_SYMBOL);
            } else if (y == (height - 1)) {
                verticalVector.push_back(GameParameter::WALL_SYMBOL);
            } else {
                verticalVector.push_back(GameParameter::BACK_WALL_SYMBOL);
            }
        }
        this->fieldVector.push_back(verticalVector);
    }

    std::vector<Position> tails = this->anaconda.getTails();

    for (auto &tail: tails) {
        this->fieldVector[tail.getX()][tail.getY()] = GameParameter::SNAKE_TAIL_SYMBOL;
    }

    if (!(this->point == Position(-1, -1))) {
        this->fieldVector[this->point.getX()][this->point.getY()] = GameParameter::APPLE_SYMBOL;
    }

    Position headPosition = this->anaconda.getHeadPosition();
    this->fieldVector[headPosition.getX()][headPosition.getY()] = GameParameter::SNAKE_HEAD_SYMBOL;
}

std::string SnakeGame::getRenderString() {
    std::string renderString;
    for (int y = (this->height - 1); y >= 0; y--) {
        for (int x = 0; x < this->width; x++) {
            renderString += this->fieldVector[x][y];
        }
        renderString += '\n';
    }
    return renderString;
}

SnakeGame::SnakeGame(int width, int height, std::string mode, int fps = 2) :
        anaconda(Position(width / 2, height / 2), ControlKeys::RIGHT),
        width(width + 2),
        height(height + 2),
        point(this->getNewPointPosition()),
        baseCursorPosition(this->getCursorPosition()) {
    if (width < GameParameter::MIN_WIDTH || height < GameParameter::MIN_HEIGHT) {
        std::cout << GameParameter::INVALID_FIELD_SIZE_MESSAGE << std::endl;
        this->baseCursorPosition = getCursorPosition();
        if (width < GameParameter::MIN_WIDTH) {
            this->width = GameParameter::MIN_WIDTH;
        } else if (height < GameParameter::MIN_HEIGHT) {
            this->height = GameParameter::MIN_HEIGHT;
        }
    }
    this->lastPressedKey.store(ControlKeys::RIGHT, std::memory_order_relaxed);
    this->isGame = false;
    if (!GameMode::isValidMode(mode)) {
        std::cout << GameParameter::INVALID_GAME_MODE_MESSAGE << std::endl;
        mode = GameMode::EASY;
    }
    this->mode = std::move(mode);
    this->fps = fps;
}

int SnakeGame::checkEvent() {
    Position head = this->anaconda.getHeadPosition();
    std::vector<Position> tails = this->anaconda.getTails();

    for (auto &tail: tails) {
        if (head == tail) {
            return GameParameter::TAIL_HIT_EVENT;
        }
    }

    if (head.getX() == 0 || head.getX() == (this->width - 1) || head.getY() == 0 || head.getY() == (this->height - 1)) {
        return GameParameter::WALL_HIT_EVENT;
    }

    if (head == this->point) {
        return GameParameter::APPLE_EATEN_EVENT;
    }

    return GameParameter::PASS_EVENT;
}

Position SnakeGame::getNewPointPosition() {
    std::vector<Position> freePositions;

    for (int y = 1; y < (this->height - 1); y++) {
        for (int x = 1; x < (this->width - 1); x++) {
            Position pos = Position(x, y);
            if (this->isFreePosition(pos)) {
                freePositions.push_back(pos);
            }
        }
    }

    if (!freePositions.empty()) {
        std::srand(time(nullptr));
        int randomIndex = std::rand() % static_cast<int>(freePositions.size());
        return freePositions[randomIndex];
    }
    return {-1, -1};
}

bool SnakeGame::isFreePosition(Position pos) {
    if (pos == this->anaconda.getHeadPosition()) {
        return false;
    }

    int x = pos.getX();
    int y = pos.getY();
    if (x == 0 || x == (width - 1) || y == 0 || y == (height - 1)) {
        return false;
    }

    std::vector<Position> tails = this->anaconda.getTails();
    for (auto &tail: tails) {
        if (pos == tail) {
            return false;
        }
    }
    return true;
}

void SnakeGame::startGame() {
    this->isGame = true;

    std::thread listenerThread([this] { keyboardListener(); });

    while (isGame) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));

        char pressedKey = static_cast<char>(lastPressedKey.load(std::memory_order_relaxed));

        if (pressedKey == ControlKeys::EXIT) {
            this->isGame = false;
            break;
        }

        this->handleGameLogic(pressedKey);
        this->renderField();
        this->setCursorPosition();
        std::cout << this->getRenderString();
    }

    listenerThread.join();
    this->endGame();
}

void SnakeGame::handleGameLogic(char pressedKey) {
    this->anaconda.move(this->point, pressedKey);
    int event = this->checkEvent();
    switch (event) {
        case GameParameter::TAIL_HIT_EVENT:
            this->isGame = false;
            break;
        case GameParameter::WALL_HIT_EVENT:
            if (this->mode == GameMode::EASY) {
                this->handleEasyModeEvent();
            } else if (this->mode == GameMode::MEDIUM) {
                this->handleMediumModeEvent();
            } else if (this->mode == GameMode::HARD) {
                this->handleHardModeEvent();
            } else if (this->mode == GameMode::HARD_PLUS) {
                this->handleHardPlusModeEvent();
            }
            break;
        case GameParameter::APPLE_EATEN_EVENT:
            this->point = this->getNewPointPosition();
            break;
    }
}

void SnakeGame::handleEasyModeEvent() {
    this->isGame = false;
}

void SnakeGame::handleMediumModeEvent() {
    Position head = this->anaconda.getHeadPosition();
    int headDirection = this->anaconda.getHeadDirection();
    Position pos = Position(0, 0);
    if (head.getX() == 0 && headDirection == ControlKeys::LEFT) {
        pos = Position((this->width - 2), head.getY());
    } else if (head.getX() == (this->width - 1) && headDirection == ControlKeys::RIGHT) {
        pos = Position(1, head.getY());
    } else if (head.getY() == 0 && headDirection == ControlKeys::DOWN) {
        pos = Position(head.getX(), (this->height - 2));
    } else if (head.getY() == (this->height - 1) && headDirection == ControlKeys::UP) {
        pos = Position(head.getX(), 1);
    }
    if (!this->isFreePosition(pos)) {
        this->isGame = false;
    }
    this->anaconda.moveHead(this->point, pos);
    if (this->point == pos) {
        this->point = this->getNewPointPosition();
    }
}

void SnakeGame::handleHardModeEvent() {
    Position head = this->anaconda.getHeadPosition();
    int headDirection = this->anaconda.getHeadDirection();
    Position pos = Position(0, 0);
    int newDirection;
    if (head.getX() == 0 && headDirection == ControlKeys::LEFT) {
        newDirection = ControlKeys::DOWN;
        pos = Position(head.getX() + 1, head.getY() - 1);
    } else if (head.getX() == (this->width - 1) && headDirection == ControlKeys::RIGHT) {
        newDirection = ControlKeys::UP;
        pos = Position(head.getX() - 1, head.getY() + 1);
    } else if (head.getY() == 0 && headDirection == ControlKeys::DOWN) {
        newDirection = ControlKeys::RIGHT;
        pos = Position(head.getX() + 1, head.getY() + 1);
    } else if (head.getY() == (this->height - 1) && headDirection == ControlKeys::UP) {
        newDirection = ControlKeys::LEFT;
        pos = Position(head.getX() - 1, head.getY() - 1);
    }
    this->anaconda.setHeadDirection(newDirection);
    this->lastPressedKey.store(newDirection, std::memory_order_relaxed);

    if (!this->isFreePosition(pos)) {
        this->isGame = false;
    }
    this->anaconda.moveHead(this->point, pos);
    if (this->point == pos) {
        this->point = this->getNewPointPosition();
    }
}

void SnakeGame::handleHardPlusModeEvent() {
    Position head = this->anaconda.getHeadPosition();
    int headDirection = this->anaconda.getHeadDirection();
    Position pos = Position(0, 0);
    int newDirection;
    if (head.getX() == 0 && headDirection == ControlKeys::LEFT) {
        newDirection = ControlKeys::DOWN;
        pos = Position(head.getX() + 1, head.getY() - 1);
        if (!this->isFreePosition(pos)) {
            newDirection = ControlKeys::UP;
            pos = Position(head.getX() + 1, head.getY() + 1);
        }
    } else if (head.getX() == (this->width - 1) && headDirection == ControlKeys::RIGHT) {
        newDirection = ControlKeys::UP;
        pos = Position(head.getX() - 1, head.getY() + 1);
        if (!this->isFreePosition(pos)) {
            newDirection = ControlKeys::DOWN;
            pos = Position(head.getX() - 1, head.getY() - 1);
        }
    } else if (head.getY() == 0 && headDirection == ControlKeys::DOWN) {
        newDirection = ControlKeys::RIGHT;
        pos = Position(head.getX() + 1, head.getY() + 1);
        if (!this->isFreePosition(pos)) {
            newDirection = ControlKeys::LEFT;
            pos = Position(head.getX() - 1, head.getY() + 1);
        }
    } else if (head.getY() == (this->height - 1) && headDirection == ControlKeys::UP) {
        newDirection = ControlKeys::LEFT;
        pos = Position(head.getX() - 1, head.getY() - 1);
        if (!this->isFreePosition(pos)) {
            newDirection = ControlKeys::RIGHT;
            pos = Position(head.getX() + 1, head.getY() - 1);
        }
    }
    this->anaconda.setHeadDirection(newDirection);
    this->lastPressedKey.store(newDirection, std::memory_order_relaxed);

    if (!this->isFreePosition(pos)) {
        this->isGame = false;
    }
    this->anaconda.moveHead(this->point, pos);
    if (this->point == pos) {
        this->point = this->getNewPointPosition();
    }
}


void SnakeGame::endGame() {
    bool filledField = true;
    for (int y = 1; y < (this->height - 1 - 1); y++) {
        for (int x = 1; x < (this->width - 1 - 1); x++) {
            if (this->isFreePosition(Position(x, y))) {
                filledField = false;
            }
        }
        if (!filledField) {
            break;
        }
    }
    if (filledField) {
        std::cout << GameParameter::VICTORY_MESSAGE << std::endl;
        return;
    }
    int event = this->checkEvent();
    switch (event) {
        case GameParameter::TAIL_HIT_EVENT:
            std::cout << GameParameter::TAIL_HIT_MESSAGE << std::endl;
            break;
        case GameParameter::WALL_HIT_EVENT:
            std::cout << GameParameter::WALL_HIT_MESSAGE << std::endl;
            break;
        default:
            break;
    }
}


