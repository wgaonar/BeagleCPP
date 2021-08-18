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

  for (int i = 0; i < 10; i++)   
  {
    cout << "Blinking " << i+1 << " times of " << 10 <<  endl;
    
    ledPin.DigitalWriteFast(HIGH);
    DelayMicroseconds(10);

    ledPin.DigitalWriteFast(LOW);
    DelayMicroseconds(10);
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}