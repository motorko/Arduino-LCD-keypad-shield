#include <Arduino.h>

#define ACCELERATION 0.2
#define FRICTION 0.99
#define BOUNCE 0.7
#define FPS 30

class CoordVector {
 public:
  CoordVector(float initialX, float initialY, float initialSpeed, uint8_t maxX,
              uint8_t maxY);
  float speedX;
  float speedY;
  float x;
  float y;

  void step();

 private:
  uint8_t MAX_X;
  uint8_t MAX_Y;
};
