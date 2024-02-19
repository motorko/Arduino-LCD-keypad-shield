#include <CoordVector.h>

CoordVector::CoordVector(float initialX, float initialY, float initialSpeed,
                         uint8_t maxX, uint8_t maxY) {
  x = initialX;
  y = initialY;
  speedX = speedY = initialSpeed;
  MAX_X = maxX + 1;
  MAX_Y = maxY + 1;
}

void CoordVector::step() {
  static uint64_t lastTime = millis();
  if (millis() - lastTime < (1000 / FPS)) return;
  lastTime = millis();

  float newX = x + speedX;
  float newY = y + speedY;

  if (newX > MAX_X || newX < 0) {
    speedX *= -BOUNCE;
    newX = newX >= MAX_X ? MAX_X - 1 : 0;
  } else {
    speedX *= FRICTION;
  }

  if (newY > MAX_Y || newY < 0) {
    speedY *= -BOUNCE;
    newY = newY >= MAX_Y ? MAX_Y - 1 : 0;
  } else {
    speedY *= FRICTION;
  }

  x = newX;
  y = newY;
}