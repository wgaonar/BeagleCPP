#include <iostream>

#include "DHT.h"

// Overload Constructor with dataPin
DHT::DHT (GPIO newDataPin, DHT_TYPE newTypeID) : 
          dataPin(newDataPin), type_ID(newTypeID)
{ 
  InitSensor();

  std::string message;
  message = "DHT object with data on pin: " +
            dataPin.GetPinHeaderId() +
            " was created!\n\n";
  std::cout << RainbowText(message, "Violet");
}

/*
  Private method to prepare the sensor for reading data
*/
void DHT::InitSensor() 
{
  dataPin.SetMode(OUTPUT);
  while (true)
  {
    
  

  // Set pin LOW for ~18 milliseconds.
  dataPin.DigitalWriteFast(LOW);
  DelayMicroseconds(40);

  // Set pin HIGH for 40 microseconds.
  dataPin.DigitalWriteFast(HIGH);
  DelayMicroseconds(40);

  // Put the pin in INPUT Mode
  // dataPin.SetMode(INPUT);

  }
  const int maxTimings = 85;
  int index = 0;
  int data[5] = {};
  for (size_t i = 0; i < maxTimings; i++)
  {
    int counter = 0;
    while (dataPin.DigitalRead() == HIGH)
    {
      counter++;
      DelayMicroseconds(1);
      if (counter == 255)
        break;
    }
    
    if(counter == 255)
      break;
    
    if ((i >= 4) && (i % 2 == 0))
    {
      data[index / 8] <<= 2;
      if (counter > 16)
        data[index / 8] |= 1;
      index++;
    }
  }
  
  if ((index >= 40) && data[4] == ((data[0] + data[1] + data[2] + data[3] & 0xFF)))
  {
    std::cout << "Relative Humidity: " << data[0] << "." << data[1] << "%" << std::endl;
    std::cout << "Temperature: " << data[2] << "." << data[3] << "°C" << std::endl;
  }
  else
    std::cout << "Data is not good, skip\n";
}

/*
  Private method to read and store the data from the sensor
*/
void DHT::ReadDataFromSensor() 
{
  
}

/*
  Public method to get the temperature in °C
  @return double: the measured temperature (0°C - 50°C)
*/
double DHT::ReadTemperatureCelsius() 
{
  // Get the reading
  this->ReadDataFromSensor();

  return 0; 
}

/*
  Public method to get the temperature in °F
  @return double: the measured temperature (32°F - 122°F)
*/
double DHT::ReadTemperatureFahrenheit() 
{
  // Get the reading
  this->ReadDataFromSensor();

  return 0; 
}

// Destructor
DHT::~DHT() {}
