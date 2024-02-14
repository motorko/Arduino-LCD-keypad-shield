#include <Arduino.h>
#include <Buttons.h>
#include <Dot.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

Dot dot;

const uint8_t DOT_LOCATION = 0;

void handleButtons() {
  switch (getPressedButton()) {
    case Buttons::RIGHT:
      dot.goRight();
      break;
    case Buttons::UP:
      dot.goTop();
      break;
    case Buttons::DOWN:
      dot.goBottom();
      break;
    case Buttons::LEFT:
      dot.goLeft();
      break;
    case Buttons::SELECT:
      break;
    case Buttons::NONE:
      break;
  }
}

void setup() { lcd.begin(16, 2); }

void loop() {
  handleButtons();

  if (dot.isCursorChanged()) {
    lcd.setCursor(dot.prevCursorCoords.x, dot.prevCursorCoords.y);
    lcd.write(' ');
  }

  if (dot.isDotChanged()) {
    lcd.createChar(DOT_LOCATION, dot.getDotChar());
    lcd.setCursor(dot.cursorCoords.x, dot.cursorCoords.y);
    lcd.write(DOT_LOCATION);
  }
}
