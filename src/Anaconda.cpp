#include <iostream>
#include <vector>
#include "../include/ControlKeys.h"
#include "../include/Position.h"
#include "../include/Anaconda.h"
#include "GameParameter.h"

Anaconda::Anaconda(Position headPosition, int headDirection) :
        head(headPosition),
        headDirection(headDirection),
        lastPoppedTail(0, 0) {

    this->headDirection = headDirection;
    this->head = headPosition;

    for (int i = 1; i <= GameParameter::DEFAULT_SNAKE_LEN; i++) {
        tails.emplace_back(head.getX() - i, head.getY());
    }
}

void Anaconda::move(Position point, int direction) {
    if (direction == ControlKeys::RIGHT && this->headDirection == ControlKeys::LEFT ||
        direction == ControlKeys::LEFT && this->headDirection == ControlKeys::RIGHT ||
        direction == ControlKeys::UP && this->headDirection == ControlKeys::DOWN ||
        direction == ControlKeys::DOWN && this->headDirection == ControlKeys::UP
            ) {
        direction = this->headDirection;
    }

    Position oldHead = this->head;
    switch (direction) {
        case (ControlKeys::RIGHT):
            this->head.setX(this->head.getX() + 1);
            break;
        case (ControlKeys::LEFT):
            this->head.setX(this->head.getX() - 1);
            break;
        case (ControlKeys::UP):
            this->head.setY(this->head.getY() + 1);
            break;
        case (ControlKeys::DOWN):
            this->head.setY(this->head.getY() - 1);
            break;
        default:
            std::cout << GameParameter::INVALID_DIRECTION_MESSAGE << this->headDirection << std::endl;
            break;
    }

    this->headDirection = direction;

    if (!(point == this->head)) {
        this->lastPoppedTail = this->tails.back();
        this->tails.pop_back();
    }

    this->tails.insert(tails.begin(), oldHead);
}

Position Anaconda::getHeadPosition() {
    return this->head;
}

std::vector<Position> Anaconda::getTails() {
    return this->tails;
}

int Anaconda::getHeadDirection() const {
    return this->headDirection;
}

void Anaconda::moveHead(Position point, Position newPosition) {
    this->head = newPosition;
    if (point == this->head) {
        this->tails.push_back(this->lastPoppedTail);
    }
}

void Anaconda::setHeadDirection(int direction) {
    this->headDirection = direction;
}
