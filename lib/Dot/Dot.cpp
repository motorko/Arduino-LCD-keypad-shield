#include <Dot.h>

void Dot::goTop() {
  coords.y = (coords.y <= 0) ? 0 : coords.y - 1;
  onChange();
}

void Dot::goBottom() {
  coords.y = (coords.y >= MAX_Y) ? MAX_Y : coords.y + 1;
  onChange();
}

void Dot::goLeft() {
  coords.x = (coords.x <= 0) ? 0 : coords.x - 1;
  onChange();
}

void Dot::goRight() {
  coords.x = (coords.x >= MAX_X) ? MAX_X : coords.x + 1;
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
