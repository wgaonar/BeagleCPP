/******************************************************************************
TB6612FNG_1.1.cpp
@wgaonar
02/07/2021
https://github.com/wgaonar/BeagleCPP

- Move the motor each second increasing the speed 10% each time and then reversing it.
- Move the motor in the other direction increasing the speed 10% and then reversing it.

Class: TB6612FNG
******************************************************************************/

#include <iostream>
#include "../../../Sources/TB6612FNG.h"

using namespace std;

// Declare the motor object directly with the header pin's names
TB6612FNG myTB6612FNGModule (P8_12, P8_14, P8_13, false, P8_16);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  // Activate the module
  myTB6612FNGModule.Activate();
  
  // Turn the motor in CW direction
  for (int speed = 0; speed < 100; speed += 10)
    myTB6612FNGModule.MotorA.Drive(speed,1000);
  for (int speed = 100; speed > 0; speed -= 10)
    myTB6612FNGModule.MotorA.Drive(speed,1000);

  // Turn the motor in CCW direction
  for (int speed = 0; speed > -100; speed -= 10)
    myTB6612FNGModule.MotorA.Drive(speed,1000);
  for (int speed = -100; speed < 0; speed+=10)
    myTB6612FNGModule.MotorA.Drive(speed,1000);

  // Deactivate the module
  myTB6612FNGModule.Deactivate();
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}