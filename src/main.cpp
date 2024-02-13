#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const uint8_t dot = 0;

uint8_t dot_char[] = {B10000, B00000, B00000, B00000,
                      B00000, B00000, B00000, B00000};

enum Button { RIGHT, UP, DOWN, LEFT, SELECT, NONE };

Button getButton() {
  static uint64_t last_time = 0;
  if ((millis() - last_time) < 50) return NONE;
  last_time = millis();

  uint16_t val = analogRead(0);

  if (val < 50) return RIGHT;
  if (val < 200) return UP;
  if (val < 400) return DOWN;
  if (val < 600) return LEFT;
  if (val < 900) return SELECT;
  return NONE;
}

struct dot_coords_t {
  uint8_t x;
  uint8_t y;
  uint8_t dot_x;
  uint8_t dot_y;
  uint8_t cursor_x;
  uint8_t cursor_y;
  uint8_t old_cursor_x;
  uint8_t old_cursor_y;
  void change(int8_t new_x, int8_t new_y) {
    x = new_x >= 80 ? 79 : new_x < 0 ? 0 : new_x;
    y = new_y >= 16 ? 15 : new_y < 0 ? 0 : new_y;

    dot_x = x % 5;
    dot_y = y % 8;

    cursor_x = x / 5;
    cursor_y = y / 8;
  }
};

const uint8_t dot_x[] = {
    B10000, B01000, B00100, B00010, B00001,
};

void create_dot(struct dot_coords_t dot_coords) {
  for (uint8_t i = 0; i < 8; i++) {
    dot_char[i] = B00000;
  }

  dot_char[dot_coords.dot_y] = dot_x[dot_coords.dot_x];

  lcd.createChar(dot, dot_char);
}

void print_dot(struct dot_coords_t dot_coords) {
  create_dot(dot_coords);
  lcd.setCursor(dot_coords.cursor_x, dot_coords.cursor_y);

  lcd.write(dot);
}

void setup() { lcd.begin(16, 2); }

void loop() {
  static struct dot_coords_t dot_coords;
  static struct dot_coords_t old_dot_coords;

  switch (getButton()) {
    case Button::RIGHT:
      dot_coords.change(dot_coords.x + 1, dot_coords.y);
      break;
    case Button::UP:
      dot_coords.change(dot_coords.x, dot_coords.y - 1);
      break;
    case Button::DOWN:
      dot_coords.change(dot_coords.x, dot_coords.y + 1);
      break;
    case Button::LEFT:
      dot_coords.change(dot_coords.x - 1, dot_coords.y);
      break;
    case Button::SELECT:
      break;
    case Button::NONE:
      break;
  }

  if (dot_coords.x != old_dot_coords.x || dot_coords.y != old_dot_coords.y) {
    print_dot(dot_coords);
    if (dot_coords.cursor_x != old_dot_coords.cursor_x ||
        dot_coords.cursor_y != old_dot_coords.cursor_y) {
      lcd.setCursor(old_dot_coords.cursor_x, old_dot_coords.cursor_y);
      lcd.print(" ");
    }
    old_dot_coords.change(dot_coords.x, dot_coords.y);
  }
}
