#include "ParametersReader.h"

#include "PIN_CONFIG.h"

ParametersReader::ParametersReader()
{
    refreshRate = 100;
}

ParametersReader::~ParametersReader()
{

}

void ParametersReader::start()
{

}

void ParametersReader::stop()
{
}

void ParametersReader::tick()
{
    if (shouldRefresh()) {
        int sensorValue = analogRead(ANALOG_INPUT);
        int targetHumidity = sensorValue * 10 / 1024 * 10;

        if (targetHumidity != lastReadTargetHumidity) {
            Serial.print("Target humidity: ");
            Serial.println(targetHumidity);
            lastReadTargetHumidity = targetHumidity;
            if (output) {
                output->updateTargetHumidity(targetHumidity);
            }
        }
    }
}

int ParametersReader::getTargetHumidity() {
    return lastReadTargetHumidity;
}

void ParametersReader::setOutput(Output *output) {
    this->output = output;
}