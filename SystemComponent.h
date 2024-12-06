#ifndef __SYSTEM_COMPONENT_H__
#define __SYSTEM_COMPONENT_H__

#include <Arduino.h>

class SystemComponent {
public:
  virtual void tick() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;

  bool shouldRefresh() {
    currentTimestamp = millis();
    if (currentTimestamp >= previousTimestamp + refreshRate) {
      previousTimestamp = currentTimestamp;
      return true;
    }

    return false;
  }

  protected:
    unsigned long refreshRate = 5000;  // miliseconds
    unsigned long previousTimestamp = 0;
    unsigned long currentTimestamp = 0;
};

#endif