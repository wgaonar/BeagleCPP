/******************************************************************************
DHT11_1.1.cpp
@wgaonar
08/08/2021
https://github.com/wgaonar/BeagleCPP

Read continuously the temperature

Class: DHT
******************************************************************************/

#include <iostream>
#include "../../../Sources/DHT.h"

using namespace std;

// Global ADC pin declaration 
DHT mySensor(P9_23, DHT11);

// Global Variables
bool stopReadTemperature = false;
double temperatureCelsius = 0.0;
double temperatureFahrenheit = 0.0;

int ReadTemperature() {
  while (stopReadTemperature == false) 
  {
    DelayMilliseconds(250);
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Call the function to read the temperature
  mySensor.DoUserFunction(&ReadTemperature);

  char userInput = '\0';
  while (userInput != 'y') 
  {
    message = "Do you want to stop the readings on the pin? Enter 'y' for yes: ";
    cout << RainbowText(message, "Blue")  << endl;
    
    cin >> userInput;
    if (userInput == 'y') 
      stopReadTemperature = true;
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}