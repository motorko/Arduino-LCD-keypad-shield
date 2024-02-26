#include <Arduino.h>
#include <Buttons.h>
#include <CoordVector.h>
#include <Dot.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define DOT_LOCATION (uint8_t)0

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Dot dot(0, 0);
CoordVector cv((float)dot.coords.x, (float)dot.coords.y, 0, MAX_X, MAX_Y);
Buttons btns;

void bindBtnsCallbacks() {
  btns.bindToClick(Buttons::RIGHT, []() { cv.speedX += ACCELERATION; });
  btns.bindToClick(Buttons::LEFT, []() { cv.speedX -= ACCELERATION; });
  btns.bindToClick(Buttons::UP, []() { cv.speedY -= ACCELERATION; });
  btns.bindToClick(Buttons::DOWN, []() { cv.speedY += ACCELERATION; });
  btns.bindToClick(Buttons::SELECT, []() { cv.speedX = cv.speedY = 0; });
}

void ticks() {
  btns.tick();
  cv.tick();
}

void clearPrevCeil() {
  lcd.setCursor(dot.prevCursorCoords.x, dot.prevCursorCoords.y);
  lcd.write(' ');
}

void printDot() {
  lcd.createChar(DOT_LOCATION, dot.getDotChar());
  lcd.setCursor(dot.cursorCoords.x, dot.cursorCoords.y);
  lcd.write(DOT_LOCATION);
}

void setup() {
  lcd.begin(16, 2);
  bindBtnsCallbacks();
  printDot();
}

void loop() {
  ticks();

  dot.setCoords(cv.x, cv.y);

  if (dot.isCursorChanged()) {
    clearPrevCeil();
  }

  if (dot.isDotChanged()) {
    printDot();
  }
}
