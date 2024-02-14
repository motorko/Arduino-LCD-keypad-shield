#include <Arduino.h>

#define BTN_RATTLE 100

enum Buttons { RIGHT = 1, UP = 2, DOWN = 3, LEFT = 4, SELECT = 0, NONE = -1 };

Buttons getPressedButton();