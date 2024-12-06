#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Adafruit_SSD1306.h>

#include "Output.h"

class Display : public Output {

public:
    Display();
    virtual ~Display();

    bool init();
    void updateTemperature(int temperature);
    void updateTargetHumidity(int targetHumidity);
    void updateHumidity(int humidity);

private:
    Adafruit_SSD1306 *ssd1306;

    void clearPixels(int16_t x, int16_t y, int16_t w, int16_t h);
};

#endif