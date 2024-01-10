#include <iostream>
#include <vector>
#include "ControlKeys.h"
#include "Position.h"

#ifndef ANACONDA_H
#define ANACONDA_H

class Anaconda {
private:
    Position head;
    int headDirection;
    std::vector<Position> tails;
    Position lastPoppedTail;
public:
    Anaconda(Position headPosition, int headDirection);

    void move(Position point, int direction);

    int getHeadDirection() const;

    void setHeadDirection(int direction);

    void moveHead(Position point, Position newPosition);

    Position getHeadPosition();

    std::vector<Position> getTails();
};

#endif // ANACONDA_H