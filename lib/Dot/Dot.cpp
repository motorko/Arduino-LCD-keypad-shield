#include <Dot.h>

Dot::Dot(uint8_t initialX, uint8_t initialY) {
  setCoords(initialX, initialY);
  onChange();
}

void Dot::goTop() { setCoords(coords.x, coords.y - 1); }

void Dot::goBottom() { setCoords(coords.x, coords.y + 1); }

void Dot::goLeft() { setCoords(coords.x - 1, coords.y); }

void Dot::goRight() { setCoords(coords.x + 1, coords.y); }

void Dot::setCoords(uint8_t x, uint8_t y) {
  coords.x = x == UINT8_MAX ? 0 : x > MAX_X ? MAX_X : x;
  coords.y = y == UINT8_MAX ? 0 : y > MAX_Y ? MAX_Y : y;
  onChange();
}

void Dot::onChange() {
  prevCursorCoords = cursorCoords;

  uint8_t cursorX = coords.x / DOTS_IN_CEIL_ROW;
  uint8_t cursorY = coords.y / DOTS_IN_CEIL_COLUMN;
  cursorCoords = {cursorX, cursorY};

  prevDotCoords = dotCoords;

  uint8_t dotX = coords.x % DOTS_IN_CEIL_ROW;
  uint8_t dotY = coords.y % DOTS_IN_CEIL_COLUMN;
  dotCoords = {dotX, dotY};
}

bool Dot::isCursorChanged() {
  return prevCursorCoords.x != cursorCoords.x ||
         prevCursorCoords.y != cursorCoords.y;
}

bool Dot::isDotChanged() {
  return prevDotCoords.x != dotCoords.x || prevDotCoords.y != dotCoords.y;
}

uint8_t* Dot::getDotChar() {
  for (uint8_t i = 0; i < 8; i++) {
    dotChar[i] = 0;
  }
  dotChar[dotCoords.y] = dotXs[dotCoords.x];
  return dotChar;
}
