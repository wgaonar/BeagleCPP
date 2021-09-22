#include <iostream>

#include "DHT.h"

// Overload Constructor with dataPin
DHT::DHT (GPIO newDataPin, DHT_TYPE newTypeID) : 
          dataPin(newDataPin), type_ID(newTypeID)
{ 

  std::string message;
  message = "DHT object with data on pin: " +
            dataPin.GetPinHeaderId() +
            " was created!\n\n";
  std::cout << RainbowText(message, "Violet");
  
  InitSensor();
}

/*
  Private method to prepare the sensor for reading data
*/
void DHT::InitSensor() 
{

  // Put the pin in OUTPUT mode to send out the start signal
  dataPin.SetMode(OUTPUT);
    
  dataPin.StreamOpen();
  // Set pin LOW for ~18 milliseconds.
  dataPin.StreamWrite(LOW);
  DelayMilliseconds(20);

  // Set pin HIGH for 40 microseconds.
  dataPin.StreamWrite(HIGH);
  DelayMicroseconds(40);
  dataPin.StreamClose();

  // Put the pin in INPUT Mode to wait for the DHT response signal
  dataPin.SetMode(INPUT);


  const int maxTimings = 85;
  uint8_t counter = 0;
  STATE lastState = HIGH;
  uint8_t i = 0, index = 0;
  int data[5] = {0,0,0,0,0};

  for (i = 0; i < maxTimings; i++)
  {
    counter = 0;
    while (dataPin.DigitalRead() == lastState)
    {
      counter++;
      DelayMicroseconds(1);
      if (counter == 255)
        break;
    }
    lastState = dataPin.DigitalRead();

    if(counter == 255)
      break;

    if ((i >= 4) && (i % 2 == 0))
    {
      data[index / 8] <<= 1;
      if (counter > 16)
        data[index / 8] |= 1;
      index++;
    }
  }


  std::cout << "Relative Humidity: " << data[0] << "." << data[1] << "%" << std::endl;
  std::cout << "Temperature: " << data[2] << "." << data[3] << "°C" << std::endl;

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
