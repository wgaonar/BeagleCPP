/************************************************************************
Listing_1.3.cpp
@wgaonar
24/03/2021
https://github.com/wgaonar/BeagleCPP

Turning ON / OFF  six LEDs in order

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

  char userInput = '\0';
  while (userInput != 'y')
  {
    int time = 100;

    redLed.DigitalWrite(HIGH);
    DelayMilliseconds(time);

    yellowLed.DigitalWrite(HIGH);
    DelayMilliseconds(time);

    greenLed.DigitalWrite(HIGH);
    DelayMilliseconds(time);

    whiteLed.DigitalWrite(HIGH);
    DelayMilliseconds(time);

    blueLed.DigitalWrite(HIGH);
    DelayMilliseconds(time);

    blueLed.DigitalWrite(LOW);
    DelayMilliseconds(time);

    whiteLed.DigitalWrite(LOW);
    DelayMilliseconds(time);

    greenLed.DigitalWrite(LOW);
    DelayMilliseconds(time);

    yellowLed.DigitalWrite(LOW);
    DelayMilliseconds(time);

    redLed.DigitalWrite(LOW);
    DelayMilliseconds(time);

    cout << "Enter 'y', to finish the program or another key to repeat: " << endl;
    cin >> userInput;
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  return 0;
}