#include <iostream>

#ifndef DIFFICULTY_H
#define DIFFICULTY_H

class GameMode {
public:
    static const std::string EASY;
    static const std::string MEDIUM;
    static const std::string HARD;
    static const std::string HARD_PLUS;

    static bool isValidMode(const std::string &mode);
};

#endif // DIFFICULTY_H