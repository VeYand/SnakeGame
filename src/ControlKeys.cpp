#include "../include/ControlKeys.h"

bool ControlKeys::isValidKey(char key) {
    return (key == UP || key == DOWN || key == LEFT || key == RIGHT || key == EXIT);
}