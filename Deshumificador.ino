/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

#include "HumiditySensor.h"
#include "ParametersReader.h"
#include "Display.h"
#include "PIN_CONFIG.h"

HumiditySensor humiditySensor;
ParametersReader parametersReader;
Display display;

void turnOnFan() {
  Serial.println("turn on");
  digitalWrite(FANPIN, HIGH);
}

void turnOffFan() {
  Serial.println("turn off");
  digitalWrite(FANPIN, LOW);
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  humiditySensor.start();
  humiditySensor.setHighThresholdCallback(turnOnFan);
  humiditySensor.setLowThresholdCallback(turnOffFan);

  display.init();
  
  humiditySensor.setOutput(&display);
  parametersReader.setOutput(&display);
  pinMode(FANPIN, OUTPUT);
}

void loop() {
  humiditySensor.tick();
  parametersReader.tick();
   
  int targetHumidity = parametersReader.getTargetHumidity();
  humiditySensor.setTargetHumidity(targetHumidity);
}
