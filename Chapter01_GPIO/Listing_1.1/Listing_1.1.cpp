/************************************************************************
Listing_1.1.cpp
@wgaonar
24/03/2021
https://github.com/wgaonar/BeagleCPP

Blink a led

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
    
    ledPin.DigitalWrite(HIGH);
    DelayMilliseconds(1000);

    ledPin.DigitalWrite(LOW);
    DelayMilliseconds(1000);
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}