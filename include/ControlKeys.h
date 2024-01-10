#ifndef CONTROL_KEYS_H
#define CONTROL_KEYS_H

class ControlKeys {
public:
    static const char UP = 38;
    static const char DOWN = 40;
    static const char LEFT = 37;
    static const char RIGHT = 39;
    static const char EXIT = 81;

    static bool isValidKey(char key);
};

#endif // CONTROL_KEYS_H