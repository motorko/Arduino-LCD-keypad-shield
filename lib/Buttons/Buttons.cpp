#include <Buttons.h>

Buttons getPressedButton() {
  static uint64_t last_time = 0;
  if ((millis() - last_time) < BTN_RATTLE) return NONE;
  last_time = millis();

  uint16_t val = analogRead(0);

  if (val < 50) return RIGHT;
  if (val < 200) return UP;
  if (val < 400) return DOWN;
  if (val < 600) return LEFT;
  if (val < 900) return SELECT;
  return NONE;
}