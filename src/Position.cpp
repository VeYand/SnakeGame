#include "../include/Position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position::getX() {
    return this->x;
}

int Position::getY() {
    return this->y;
}

void Position::setX(int x) {
    this->x = x;
}

void Position::setY(int y) {
    this->y = y;
}

bool operator==(Position p1, Position p2) {
    return (p1.getX() == p2.getX()) && (p1.getY() == p2.getY());
}