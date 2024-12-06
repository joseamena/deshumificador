#ifndef __DEHUMIDIFIER_H__
#define __DEHUMIDIFIER_H__

#include <DHT11.h>

#include "SystemComponent.h"
#include "Output.h"

class HumiditySensor : public SystemComponent
{
public:
    HumiditySensor();
    virtual ~HumiditySensor();
    void start();
    void stop();
    void tick();
    
    void setTargetHumidity(int targetHumidity);
    void setHumidityHysteresis(int humidityHysteresis);
    
    void setHighThresholdCallback(void (*f)());
    void setLowThresholdCallback(void (*f)());
    void setOutput(Output *output);

private:
    DHT11 *dht11;
    int targetHumidity = 50;
    int humidityHysteresis = 2;
    int lastReadtemperature = 0;
    int lastReadHumidity = 0;

    unsigned long refreshRate = 5000;  // miliseconds
    unsigned long previousTimestamp = 0;
    unsigned long currentTimestamp = 0;
    void (*shouldTurnOn)() = nullptr;
    void (*shouldTurnOff)() = nullptr;

    Output *output;
};

#endif