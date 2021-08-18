/************************************************************************
Listing_1.7.cpp
@wgaonar
17/08/2021
https://github.com/wgaonar/BeagleCPP

Blink a led with fast write files

Class: GPIO
************************************************************************/
#include <iostream>
#include "../../Sources/GPIO.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  
  GPIO ledPin(P8_12, OUTPUT);

  ledPin.StreamOpen();
  for (int i = 0; i < 1000000; i++)   
  {
    ledPin.StreamWrite(HIGH);
    ledPin.StreamWrite(LOW);
  }
  ledPin.StreamClose();

  for (int i = 0; i < 1000000; i++)   
  {
    ledPin.DigitalWrite(HIGH);
    ledPin.DigitalWrite(LOW);
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}