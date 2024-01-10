#ifndef POSITION_H
#define POSITION_H

struct Position {
private:
    int x;
    int y;
public:
    Position(int x, int y);

    int getX();

    int getY();

    void setX(int x);

    void setY(int y);
};

bool operator==(Position p1, Position p2);

#endif // POSITION_H