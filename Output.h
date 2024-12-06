#ifndef __OUTPUT_H__
#define __OUTPUT_H__


class Output {
public:
    virtual void updateTemperature(int temperature) = 0;
    virtual void updateTargetHumidity(int targetHumidity) = 0;
    virtual void updateHumidity(int humidity) = 0;
};
#endif