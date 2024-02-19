#include <Arduino.h>
#include <Buttons.h>
#include <CoordVector.h>
#include <Dot.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define DOT_LOCATION (uint8_t)0

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Dot dot;
CoordVector cv((float)dot.coords.x, (float)dot.coords.y, 0, MAX_X, MAX_Y);

void handleButtons() {
  switch (getPressedButton()) {
    case Buttons::RIGHT:
      cv.speedX += ACCELERATION;
      break;
    case Buttons::UP:
      cv.speedY -= ACCELERATION;
      break;
    case Buttons::DOWN:
      cv.speedY += ACCELERATION;
      break;
    case Buttons::LEFT:
      cv.speedX -= ACCELERATION;
      break;
    case Buttons::SELECT:
      cv.speedX = cv.speedY = 0;
      break;
    case Buttons::NONE:
      break;
  }
}

void printDot() {
  lcd.createChar(DOT_LOCATION, dot.getDotChar());
  lcd.setCursor(dot.cursorCoords.x, dot.cursorCoords.y);
  lcd.write(DOT_LOCATION);
}

void clearPrevCeil() {
  lcd.setCursor(dot.prevCursorCoords.x, dot.prevCursorCoords.y);
  lcd.write(' ');
}

void setup() {
  lcd.begin(16, 2);
  printDot();
}

void loop() {
  cv.step();
  handleButtons();

  dot.setCoords(cv.x, cv.y);

  if (dot.isCursorChanged()) {
    clearPrevCeil();
  }

  if (dot.isDotChanged()) {
    printDot();
  }
}
