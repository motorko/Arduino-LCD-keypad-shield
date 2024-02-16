#include <Arduino.h>

#define MAX_X 79
#define MAX_Y 15

#define DOTS_IN_CEIL_ROW 5
#define DOTS_IN_CEIL_COLUMN 8

typedef struct {
  uint8_t x;
  uint8_t y;
} dot_coords_t;

class Dot {
 public:
  dot_coords_t prevCursorCoords = {0, 0};
  dot_coords_t cursorCoords = {0, 0};

  void goTop();
  void goBottom();
  void goLeft();
  void goRight();

  void setCoords(uint8_t x, uint8_t y);

  bool isCursorChanged();
  bool isDotChanged();

  uint8_t* getDotChar();

 private:
  uint8_t dotChar[8] = {B10000, 0, 0, 0, 0, 0, 0, 0};
  uint8_t dotXs[5] = {B10000, B01000, B00100, B00010, B00001};

  dot_coords_t coords = {0, 0};

  dot_coords_t dotCoords = {0, 0};
  dot_coords_t prevDotCoords = {0, 0};

  void onChange();
};
