#include <Arduino.h>

#define BTN_THROTTLE 100

typedef void (*callback)();

class Buttons {
 public:
  enum State { RIGHT, UP, DOWN, LEFT, SELECT, NONE };
  void bindToClick(State state, callback cb);
  void tick();

 private:
  State getState();
  callback callbacks[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
};
