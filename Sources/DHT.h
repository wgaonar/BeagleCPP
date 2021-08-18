#ifndef DHT_H
#define DHT_H

#include "GPIO.h"

enum DHT_TYPE
{
  DHT11=0,
  DHT22=1
};

class DHT : public GPIO 
{
private:
  GPIO dataPin;
  DHT_TYPE type_ID;

  // Initialize the sensor with the data provided by the constructor
  virtual void InitSensor();

  // Read data from the sensor
  virtual void ReadDataFromSensor();

public:

  // Overload constructor with ADC pin
  DHT(GPIO, DHT_TYPE);

  // Public method to read the Temperature in °C
  double ReadTemperatureCelsius();
  
  // Public method to read the Temperature in °F
  double ReadTemperatureFahrenheit();

  // Destructor
  ~DHT();
};

#endif // DHT_H
