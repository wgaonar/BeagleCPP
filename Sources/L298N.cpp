#include <iostream>

#include "L298N.h"

// No-args default constructor
L298N::L298N () {}

// Overload constructor from DCMotor object for ONLY the MotorA
L298N::L298N (DCMotor& newMotorA) :
              MotorA (newMotorA)
{
  // Set the flags about which motors are used 
  motorAisUsed = true;
  motorBisUsed = false;

  std::string message;
  std::string swapStringMotorA {this->MotorA.swapSpinFlag ? "True" : "False"};
  message = "\nTB6612FNG driver module with the next components / pins was created and activated:\n" +
            std::string("\tMotorA:\n") +
            std::string("\t\tAIN1: ") + this->MotorA.input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tAIN2: ") + this->MotorA.input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tPWMA: ") + this->MotorA.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\t\tSwap Spin: ") + swapStringMotorA + "\n" +
            "\n\n"; 
  std::cout << RainbowText(message, "Light Red");
}

// Overload constructor from DCMotor objects and for MotorA and MotorB
L298N::L298N (DCMotor& newMotorA, 
              DCMotor& newMotorB):
              MotorA (newMotorA), 
              MotorB (newMotorB)
{
  // Set the flags about which motors are used 
  motorAisUsed = true;
  motorBisUsed = true;

  std::string message;
  std::string swapStringMotorA {this->MotorA.swapSpinFlag ? "True" : "False"};
  std::string swapStringMotorB {this->MotorB.swapSpinFlag ? "True" : "False"};
  message = "\nTB6612FNG driver module with the next components / pins was created and activated:\n" +
            std::string("\tMotorA:\n") +
            std::string("\t\tAIN1: ") + this->MotorA.input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tAIN2: ") + this->MotorA.input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tPWMA: ") + this->MotorA.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\t\tSwap Spin: ") + swapStringMotorA + "\n" +
            std::string("\tMotorB:\n") +
            std::string("\t\tBIN1: ") + this->MotorB.input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tBIN2: ") + this->MotorB.input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tPWMB: ") + this->MotorB.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\t\tSwap Spin: ") + swapStringMotorB + "\n" +
            "\n\n"; 
  std::cout << RainbowText(message, "Light Red");
}

/*
  Interface method to BRAKE the attached motors to the module 
*/ 
void L298N::Brake()
{
  // Set the motor A in brake mode
  if (motorAisUsed)
    this->MotorA.Stop(HIGH, HIGH, HIGH);

  // Set the motor B in brake mode if it is used
  if (motorBisUsed)
    this->MotorB.Stop(HIGH, HIGH, HIGH);
}

/*
  Interface method to IDLE the attached motors to the module 
*/ 
void L298N::Idle()
{
  // Set the motor A in idle mode
  if (motorAisUsed)
    this->MotorA.Stop(LOW, LOW, LOW);

  // Set the motor B in idle mode if it is used
  if (motorBisUsed)
    this->MotorB.Stop(LOW, LOW, LOW);
}

/*
  Interface method to drive FORWARD both motors
  @param int speed: The desired speed (0,100). It set up the correct value if
                    the user enters a negative value.
  @param int duration:  The desired duration in milliseconds with 0 as
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it, 
                                        with <idle> as default action. 
*/
void L298N::Forward(int speed, int duration, STOPMODE action)
{
  if (speed < 0)
    speed *= -1;

  if (motorAisUsed)
    this->MotorA.Drive(speed);
  if (motorBisUsed)  
    this->MotorB.Drive(speed);

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    if (action == idle)
      this->Idle();
    else
      this->Brake();
  }
}

/*
  Interface method to drive BACKWARD both motors
  @param int speed: The desired speed (-100,0). It set up the correct value if
                    the user enters a positive value.
  @param int duration:  The desired duration in milliseconds with 0 as 
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void L298N::Backward(int speed, int duration, STOPMODE action)
{
  if (speed > 0)
    speed *= -1;

  if (motorAisUsed)
    this->MotorA.Drive(speed);
  if (motorBisUsed)  
    this->MotorB.Drive(speed);

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    if (action == idle)
      this->Idle();
    else
      this->Brake();
  }
}

/*
  Interface method to DRIVE in OPPOSITE direction both motors
  @param int speed: The desired speed (0,100). It set up the correct value if
                    the user enters a positive value.
  @param int duration:  The desired duration in milliseconds with 0 as 
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void L298N::TurnLeft(int speed, int duration, STOPMODE action)
{
  if (speed < 0)
    speed *= -1;

  if (motorAisUsed)
    this->MotorA.Drive(-speed);
  if (motorBisUsed)  
    this->MotorB.Drive(speed);

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    if (action == idle)
      this->Idle();
    else
      this->Brake();
  }
}

/*
  Interface method to DRIVE in ANOTHER OPPOSITE direction both motors
  @param int speed: The desired speed (0,100). It set up the correct value if
                    the user enters a positive value.
  @param int duration:  The desired duration in milliseconds with 0 as 
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void L298N::TurnRight(int speed, int duration, STOPMODE action)
{
  if (speed < 0)
    speed *= -1;

  if (motorAisUsed)
    this->MotorA.Drive(speed);
  if (motorBisUsed)  
    this->MotorB.Drive(-speed);

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    if (action == idle)
      this->Idle();
    else
      this->Brake();
  }
}

/*
  Getter method that lets to know if the Motor A is used
  @return bool: motorAisUsed
*/
bool L298N::GetMotorAisUsed()
{
  return motorAisUsed;
}

/*
  Getter method that lets to know if the Motor B is used
  @return bool: motorBisUsed
*/
bool L298N::GetMotorBisUsed()
{
  return motorBisUsed;
}

// Destructor
L298N::~L298N() {} 