
#include "Display.h"

#define SCREEN_WIDTH    128 // OLED display width, in pixels
#define SCREEN_HEIGHT   32 // OLED display height, in pixels
#define OLED_RESET      -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Display::Display()
{
}

Display::~Display()
{
    if (ssd1306) {
        delete ssd1306;
    }
}

bool Display::init() {
    ssd1306 = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    bool success = ssd1306->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    if (!success) {
        delete ssd1306;
        ssd1306 = nullptr;
        Serial.println("Failed to initialize display");
    } else {
        Serial.println("Initialized Display");
        ssd1306->clearDisplay();
        ssd1306->setCursor(0,0);
        ssd1306->setTextSize(1);
        ssd1306->setTextColor(SSD1306_WHITE); 
        ssd1306->println(F("Target Humidity: "));
        ssd1306->println(F("Temperature: "));

        ssd1306->setCursor(0, 20);
        ssd1306->print(F("Humidity: "));
 
        ssd1306->display();
    }
    return success;
}

void Display::updateTemperature(int temperature) {
    int16_t x = 78;
    int16_t y = 8;

    if (!ssd1306) {
        return;
    }
    ssd1306->setTextSize(1);
    ssd1306->setCursor(x, y);
    int farenheit = (temperature * 9 / 5) + 32;

    char buffer[8];
    sprintf(buffer, "%dC/%dF", temperature, farenheit);
    int16_t x1;
    int16_t y1;
    uint16_t w;
    uint16_t h;

    ssd1306->getTextBounds(buffer, x, y, &x1, &y1, &w, &h);
    clearPixels(x1, y1, w, h);

    ssd1306->print(buffer);
    ssd1306->display();
}

void Display::updateTargetHumidity(int targetHumidity) {
    int16_t x = 102;
    int16_t y = 0;

    static int count = 0;

    if (!ssd1306) {
        return;
    }

    count++;

    ssd1306->setTextSize(1);
    ssd1306->setCursor(x, y);

    char buffer[5];
    sprintf(buffer, "%d%%", targetHumidity);
    int16_t x1;
    int16_t y1;
    uint16_t w;
    uint16_t h;

    ssd1306->getTextBounds(buffer, x, y, &x1, &y1, &w, &h);

    clearPixels(x1, y1, w, h);

    ssd1306->print(buffer);

    ssd1306->display();
}

void Display::updateHumidity(int humidity) {
    int16_t x = 60;
    int16_t y = 16;

    if (!ssd1306) {
        return;
    }

    ssd1306->setTextSize(2);
    ssd1306->setCursor(x, y);

    char buffer[5];
    sprintf(buffer, "%d%%", humidity);
    int16_t x1;
    int16_t y1;
    uint16_t w;
    uint16_t h;

    ssd1306->getTextBounds(buffer, x, y, &x1, &y1, &w, &h);
    clearPixels(x1, y1, w, h);

    ssd1306->print(buffer);
    ssd1306->display();
}

void Display::clearPixels(int16_t x, int16_t y, int16_t w, int16_t h) {
    if (!ssd1306) {
        return;
    }
    for (int16_t i = x; i < x + w; i++) {
        for (int16_t j = y; j < y + h; j++) {
            ssd1306->drawPixel(i, j, SSD1306_BLACK);
        }
    }
}