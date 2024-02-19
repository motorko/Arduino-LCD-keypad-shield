#include <Buttons.h>

Buttons::State Buttons::getState() {
  static uint64_t lastTime = 0;
  if ((millis() - lastTime) < BTN_THROTTLE) return NONE;
  lastTime = millis();

  uint16_t val = analogRead(0);

  if (val < 50) return RIGHT;
  if (val < 200) return UP;
  if (val < 400) return DOWN;
  if (val < 600) return LEFT;
  if (val < 900) return SELECT;
  return NONE;
}

void Buttons::bindToClick(State state, callback cb) { callbacks[state] = cb; }

void Buttons::tick() {
  State state = Buttons::getState();
  if (state != NONE && callbacks[state] != nullptr) callbacks[state]();
}