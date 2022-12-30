/******************************************************************************
28BYJ48-ULN2003_1.6.cpp
@wgaonar
28/12/2022
https://github.com/wgaonar/BeagleCPP

- Move 2 stepper motors by steps in fullStep with 1 Coil mode

Class: STEPPERMOTOR
******************************************************************************/

#include <iostream>
#include "../../../Sources/STEPPERMOTOR.h"

using namespace std;

// Declaring the pins for left stepper motor
GPIO leftIN1 (P8_12);
GPIO leftIN2 (P8_14);
GPIO leftIN3 (P8_16);
GPIO leftIN4 (P8_18);

// Declaring the pins for right stepper motor
GPIO rightIN1 (P8_07);
GPIO rightIN2 (P8_08);
GPIO rightIN3 (P8_09);
GPIO rightIN4 (P8_10);

/*
  Declare the 28BYJ-48 stepper motor object with default parameters:
  full step with the activation of 1 coil, 
  default 2048 steps per revolution 
  and a default maximum speed of 500 steps/second
*/
StepperMotor leftStepper (leftIN1, leftIN2, leftIN3, leftIN4);

/*
  Declare the 28BYJ-48 stepper motor object with default parameters:
  full step with the activation of 1 coil, 
  default 2048 steps per revolution 
  and a default maximum speed of 500 steps/second
*/
StepperMotor rightStepper (rightIN1, rightIN2, rightIN3, rightIN4);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  while (true)
  {
    /* 
      Turn the left and right stepper motors 1/4-turn in the same direction at 500 steps/second
    */

    leftStepper.TurnBySteps(CW, 512);
    rightStepper.TurnBySteps(CCW, 512);

    /* 
    Turn the left and right stepper motors 1/4-turn in another direction at 500 steps/second
    */
    leftStepper.TurnBySteps(CCW, 512);
    rightStepper.TurnBySteps(CW, 512);

    cout << "Steps executed by the left stepper motor: " << leftStepper.GetStepsCounter() << endl;
    cout << "Actual position of the left stepper motor axis: " << leftStepper.GetCurrentStep() << endl;
    cout << "Steps executed by the right stepper motor: " << rightStepper.GetStepsCounter() << endl;
    cout << "Actual position of the right stepper motor axis: " << rightStepper.GetCurrentStep() << endl;

    DelayMilliseconds(1000);
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}