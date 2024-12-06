
#include <Arduino.h>

#include "HumiditySensor.h"
#include "PIN_CONFIG.h"

HumiditySensor::HumiditySensor()
{
    refreshRate = 5000;
}

HumiditySensor::~HumiditySensor()
{
    delete dht11;
}

void HumiditySensor::start()
{
    dht11 = new DHT11(DHT11PIN);
}

void HumiditySensor::stop()
{
}

void HumiditySensor::tick()
{
    currentTimestamp = millis();

    if (shouldRefresh()) {
        int currentTemperature = 0;
        int currentHumidity = 0;

        int result = dht11->readTemperatureHumidity(currentTemperature, currentHumidity);

        if (currentTemperature != lastReadtemperature) {
            if (output) {
                output->updateTemperature(currentTemperature);
            }
            lastReadtemperature = currentTemperature;
        }

        if (currentHumidity != lastReadHumidity) {
            if (output) {
                output->updateHumidity(currentHumidity);
            }
            lastReadHumidity = currentHumidity;
        }

        if (result == 0)
        {
            // Serial.printf(PSTR("read code %d\n"), result);
            // Serial.print("Humidity (%): ");
            // Serial.println(humidity);
            // Serial.printf("Temperature  (C): %d\n", temperature);

            if (currentHumidity >= targetHumidity) {
                // turn on fan or whatever
                Serial.print("Humidity is over target: ");
                Serial.println(targetHumidity);
                Serial.println("Turning on fan\n");
                if (shouldTurnOn) {
                    shouldTurnOn();
                }
            } else if (currentHumidity <= targetHumidity - humidityHysteresis) {
                // turn off the fan or whatever
                Serial.print("Humidity is under target");
                
                Serial.print("Turning off fan at ");
                Serial.println(targetHumidity);

                if (shouldTurnOff) {
                    shouldTurnOff();
                }
            }
        }
        else
        {
            Serial.println(DHT11::getErrorString(result));
        }
    }
}

void HumiditySensor::setTargetHumidity(int targetHumidity) {
    this->targetHumidity = targetHumidity;
}

void HumiditySensor::setHumidityHysteresis(int humidityHysteresis) {
    this->humidityHysteresis = humidityHysteresis;
}

void HumiditySensor::setHighThresholdCallback(void (*f)()) {
    shouldTurnOn = f;
}

void HumiditySensor::setLowThresholdCallback(void (*f)()) {
    shouldTurnOff = f;
}

void HumiditySensor::setOutput(Output *output) {
    this->output = output;
}