/************************************************************************
Listing_1.3.cpp
@wgaonar
16/03/2025
https://github.com/wgaonar/BeagleCPP

Turning ON / OFF  six LEDs in a cylon pattern

Class: GPIO
************************************************************************/
#include <iostream>
#include "../../Sources/GPIO.h"

using namespace std;

int main()
{

  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  GPIO redLed(P8_12, OUTPUT);
  GPIO yellowLed(P8_14, OUTPUT);
  GPIO greenLed(P8_16, OUTPUT);
  GPIO whiteLed(P8_18, OUTPUT);
  GPIO blueLed(P8_26, OUTPUT);

  char userInput = 'y';
  while (userInput == 'y')
  {
    int delay = 100;

    redLed.DigitalWrite(HIGH);
    DelayMilliseconds(delay);
    
    yellowLed.DigitalWrite(HIGH);
    DelayMilliseconds(delay);
    
    greenLed.DigitalWrite(HIGH);
    DelayMilliseconds(delay);
    
    whiteLed.DigitalWrite(HIGH);
    DelayMilliseconds(delay);
    
    blueLed.DigitalWrite(HIGH);
    DelayMilliseconds(delay);
    
    blueLed.DigitalWrite(LOW);
    DelayMilliseconds(delay);
    
    whiteLed.DigitalWrite(LOW);
    DelayMilliseconds(delay);
    
    greenLed.DigitalWrite(LOW);
    DelayMilliseconds(delay);
    
    yellowLed.DigitalWrite(LOW);
    DelayMilliseconds(delay);
    
    redLed.DigitalWrite(LOW);
    DelayMilliseconds(delay);
    
    cout << "Enter 'y', to do a cylon pattern again or another key to exit: " << endl;
    cin >> userInput;
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  return 0;
}