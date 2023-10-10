#include <iostream>

#include "STEPPERMOTOR.h"

// Default constructor
StepperMotor::StepperMotor() {}

// Overload Constructor
StepperMotor::StepperMotor (GPIO newMotorPin1, 
                            GPIO newMotorPin2,
                            GPIO newMotorPin3,
                            GPIO newMotorPin4,
                            STEPPER_MODE newControlMode,
                            unsigned int newStepsPerRevolution,
                            unsigned int newMaxStepsPerSecond) :
                            motorPin1 (newMotorPin1),
                            motorPin2 (newMotorPin2),
                            motorPin3 (newMotorPin3),
                            motorPin4 (newMotorPin4),
                            controlMode (newControlMode),
                            stepsPerRevolution (newStepsPerRevolution),
                            maxStepsPerSecond (newMaxStepsPerSecond)
{
  InitMotorPins();
  stepsCounter = 0;
  currentStep = 0;

  std::string modeString; 
  switch (controlMode)
  {
    case fullStep1Coil:
      modeString = "Full step with 1 Coil";
      stepsPerMode = fullStep1CoilVector.size(); 
      break;
    case halfStep:
      modeString = "Half step";
      stepsPerMode = halfStepVector.size(); 
      break;
    case fullStep2Coils:
      modeString = "Full step with 2 coils"; 
      stepsPerMode = fullStep2CoilsVector.size(); 
      break;
    case driver:
      modeString = "Driver mode was chosen"; 
      break;
  }

  std::string message;
  message = "\nStepperMotor object with the next parameters / pins was created:\n" + 
            std::string("\tMotorPin1: ") + this->motorPin1.GetPinHeaderId() + 
            "\n" + 
            std::string("\tMotorPin2: ") + this->motorPin2.GetPinHeaderId() + 
            "\n" + 
            std::string("\tMotorPin3: ") + this->motorPin3.GetPinHeaderId() + 
            "\n" +
            std::string("\tMotorPin4: ") + this->motorPin4.GetPinHeaderId() + 
            "\n" +
            std::string("\tControl Mode: ") + modeString + "\n" +
            std::string("\tMax speed: ") + std::to_string(this->maxStepsPerSecond) + "\n\n";
  std::cout << RainbowText(message, "Light Gray");
}

/*
  Private method to initialize the Pins
*/
void StepperMotor::InitMotorPins()
{
  // Set the right modes for the pins
  motorPin1.SetMode(OUTPUT);
  motorPin2.SetMode(OUTPUT);
  motorPin3.SetMode(OUTPUT);
  motorPin4.SetMode(OUTPUT);
}

/*
  Private method to activate 1 step the coils in CW or CCW direction
  @param: int: The proper step to activate the coils 
  @param: int: The desired speed in steps / second   
*/
void StepperMotor::Turn1Step(int coilStep, int speed)
{
  // Move one step the stepper motor with correct coil activation sequence
  switch (controlMode)
  {
    case fullStep1Coil:
      motorPin1.DigitalWrite(fullStep1CoilVector.at(coilStep).at(0));
      motorPin2.DigitalWrite(fullStep1CoilVector.at(coilStep).at(1));
      motorPin3.DigitalWrite(fullStep1CoilVector.at(coilStep).at(2));
      motorPin4.DigitalWrite(fullStep1CoilVector.at(coilStep).at(3));
      break;
    case fullStep2Coils:
      motorPin1.DigitalWrite(fullStep2CoilsVector.at(coilStep).at(0));
      motorPin2.DigitalWrite(fullStep2CoilsVector.at(coilStep).at(1));
      motorPin3.DigitalWrite(fullStep2CoilsVector.at(coilStep).at(2));
      motorPin4.DigitalWrite(fullStep2CoilsVector.at(coilStep).at(3));
      break;
    case halfStep:
      motorPin1.DigitalWrite(halfStepVector.at(coilStep).at(0));
      motorPin2.DigitalWrite(halfStepVector.at(coilStep).at(1));
      motorPin3.DigitalWrite(halfStepVector.at(coilStep).at(2));
      motorPin4.DigitalWrite(halfStepVector.at(coilStep).at(3));
      break;
    case driver:
      break;
    default:
      break;
  }

  // Wait the proper microseconds before the next step
  DelayMicroseconds(static_cast<int>(1000000/speed));
}

/*
  Public method to turn the motor by steps
  @param DIRECTION: The desired direction for the motor rotation
  @param unsigned int: The steps required
  @param unsigned int: The rotation's speed in steps / sec (0,MaxStepsPerSecond]    
  @param bool: Flag to print / no print the messages on the console. Default value: <false>     
*/
void StepperMotor::TurnBySteps(
                                DIRECTION direction, 
                                unsigned int stepsRequired, 
                                unsigned int speed, 
                                bool printMessages
                              )
{
  // Check the speed limit value
  if (speed > maxStepsPerSecond)
    speed = maxStepsPerSecond;

  int coilStep {0};

  if (printMessages == true)
  {
    std::string message;
    if (direction == CW) 
      message = "Turning stepper motor CW ";
    else
      message = "Turning stepper motor CCW ";

    message +=
    std::to_string(stepsRequired) + " steps at " + 
    std::to_string(speed) + " steps/second\n";

    std::cout << RainbowText(message, "Light Gray");
  }

  // Turn in CW direction
  if (direction == CW)
  {
    for (int i = 0; i < stepsRequired; i++)
    {
      coilStep = stepsPerMode - 1 - (i % stepsPerMode);
      this->Turn1Step(coilStep, speed);
      
      // Update counters
      stepsCounter++;
      currentStep++;
    }
  }
  // Turn in CCW direction
  else if (direction == CCW)
  {
    for (int i = 0; i < stepsRequired; i++)
    {
      coilStep = i % stepsPerMode;
      this->Turn1Step(coilStep, speed);
      
      // Update counters
      stepsCounter++;
      currentStep--;
    }
  }
}

/*
  Public method to turn the motor by degrees
  @param DIRECTION: The desired direction for the motor rotation
  @param double: The degrees required
  @param double: The rotation's speed in degrees/sec (0,MaxStepsPerSecond * 360 / stepsPerRevolution]    
  @param bool: Flag to print / no print the messages on the console. Default value: <false>     
*/
void StepperMotor::TurnByDegrees(
                                DIRECTION direction, 
                                double degreesRequired, 
                                double speed, 
                                bool printMessages
                              )
{
  // Convert degrees to steps
  unsigned int degreesToStepsRequired = static_cast<unsigned int>(degreesRequired * stepsPerRevolution / 360);

  // Convert speed degrees/sec to steps/sec
  unsigned int speedInSteps = static_cast<unsigned int>(speed * stepsPerRevolution / 360);

  // Turn the motor
  TurnBySteps(direction, degreesToStepsRequired, speedInSteps);
}

/*
  Public method to turn the motor by steps continuously inside a thread
  @param DIRECTION: The desired direction for the motor rotation
  @param unsigned int: The steps required
  @param unsigned int: The rotation's speed in steps/sec (0,MaxStepsPerSecond] 
  @param bool: Flag to print / no print the messages on the console. Default value: <false> 
*/
void StepperMotor::TurnByStepsInThread( 
                                        DIRECTION direction, 
                                        unsigned int stepsRequired,
                                        unsigned int speed, 
                                        bool printMessages
                                      )
{
  if (printMessages == true)
  {
    std::string message = "Rotation in a thread has been activated with a speed of: " + 
                          std::to_string(speed) + " steps/second\n";
    std::cout << RainbowText(message, "Light Gray");
  }
  
  std::thread rotationThread ( 
                              &StepperMotor::MakeTurnByStepsInThread, 
                              this,
                              direction,
                              stepsRequired, 
                              speed,
                              printMessages
                            );
  
  rotationThread.detach();

  stepperThreadsVector.push_back(std::move(rotationThread)); 
}

/*
  Private method that contains the routine to turn the motor by steps continuously
  @param DIRECTION: The desired direction for the motor rotation
  @param unsigned int: The steps required
  @param unsigned int: The rotation's speed in steps/sec (0,MaxStepsPerSecond]
  @param bool: Flag to print / no print the messages on the console. Default value: <false>     
*/
void StepperMotor::MakeTurnByStepsInThread(
                                            DIRECTION direction,
                                            unsigned int stepsRequired, 
                                            unsigned int speed, 
                                            bool printMessages
                                          )
{

  // Unset the flag to false
  finishThreadFlag = false;

  // Check the speed limit value
  if (speed > maxStepsPerSecond)
    speed = maxStepsPerSecond;

  if (printMessages == true)
  {
    std::string message;
    if (direction == CW) 
      message = "Turning stepper motor CW ";
    else
      message = "Turning stepper motor CCW ";

    message +=
    std::to_string(stepsRequired) + " steps at " + 
    std::to_string(speed) + " steps/second\n";

    std::cout << RainbowText(message, "Light Gray");
  }

  // local counter for the coils steps
  int coilStep {0};

  // Turn in CW direction
  if (direction == CW)
  {
    for (int i = 0; i < stepsRequired; i++)
    {
      // Update the appropiate the coil sequence activation 
      coilStep = stepsPerMode - 1 - (i % stepsPerMode);

      // Turn the motor 1 step while the flag is to false
      std::unique_lock<std::mutex> uniq_lck(mut);
      if (!finishThreadFlag)
      {
        uniq_lck.unlock();
        this->Turn1Step(coilStep, speed);
        uniq_lck.lock();
      }
      else
      {
        // Set the flag back to false
        finishThreadFlag = false;
        uniq_lck.unlock();
        break;
      }
      
      // Update counters
      stepsCounter++;
      currentStep++;
    }
  }
  // Turn in CCW direction
  else if (direction == CCW)
  {
    for (int i = 0; i < stepsRequired; i++)
    {
      // Update the appropiate the coil sequence activation 
      coilStep = i % stepsPerMode;

      // Turn the motor 1 step while the flag is to false
      std::unique_lock<std::mutex> uniq_lck(mut);
      if (!finishThreadFlag)
      {
        uniq_lck.unlock();
        this->Turn1Step(coilStep, speed);
        uniq_lck.lock();
      }
      else
      {
        // Set the flag back to false
        finishThreadFlag = false;
        uniq_lck.unlock();
        break;
      }
      
      // Update counters
      stepsCounter++;
      currentStep--;
    }
  }
}

/*
  Public method to turn the motor by degrees continuously inside a thread
  @param DIRECTION: The desired direction for the motor rotation
  @param double: The degrees required
  @param double: The rotation's speed in degrees/sec (0,MaxStepsPerSecond * 360 / stepsPerRevolution]    
  @param bool: Flag to print / no print the messages on the console. Default value: <false>   
*/
void StepperMotor::TurnByDegreesInThread( 
                                        DIRECTION direction, 
                                        double degreesRequired,
                                        double speed, 
                                        bool printMessages
                                      )
{
  if (printMessages == true)
  {
    std::string message = "Rotation in a thread has been activated with a speed of: " + 
                          std::to_string(speed) + " steps/second\n";
    std::cout << RainbowText(message, "Light Gray");
  }

  // Convert degrees to steps
  unsigned int degreesToStepsRequired = static_cast<unsigned int>(degreesRequired * stepsPerRevolution / 360);

  // Convert speed degrees/sec to steps/sec
  unsigned int speedInSteps = static_cast<unsigned int>(speed * stepsPerRevolution / 360);
  
  /*
    Call the method to turn by steps with the converted variables: degrees to steps, and speed to 
    steps per seconds 
  */
  std::thread rotationThread ( 
                              &StepperMotor::MakeTurnByStepsInThread, 
                              this,
                              direction,
                              degreesToStepsRequired, 
                              speedInSteps,
                              printMessages
                            );
  
  rotationThread.detach();

  stepperThreadsVector.push_back(std::move(rotationThread)); 
}

// Interface method to get the stopping flag
bool StepperMotor::GetFinishThreadFlag()
{
  return finishThreadFlag;
}

// Interface method to set the stopping flag
void StepperMotor::SetFinishThreadFlag(bool value) 
{
  finishThreadFlag = value;
}

/*
  Public method to get the absolute steps counter of the stepper motor
  @return int: The counter value   
*/  
int StepperMotor::GetStepsCounter()
{
  return stepsCounter;
}

/*
  Public method to set the absolute steps counter of the stepper motor
  @param int: The desired counter value   
*/  
void StepperMotor::SetStepsCounter(int desiredCounterValue)
{
  stepsCounter = desiredCounterValue;
}

/*
  Public method to get the current step position of the axis
  @return int: The current step  
*/  
int StepperMotor::GetCurrentStep()
{
  return currentStep;
}

/*
  Public method to set the current step position of the axis
  @param int: The desired current step   
*/  
void StepperMotor::SetCurrentStep(int desiredStepValue)
{
  currentStep = desiredStepValue;
}

StepperMotor::~StepperMotor() 
{
  // Iterate over the threads vector
  for (std::thread & th : stepperThreadsVector)
  {
    if (th.joinable())
      th.join();
  }

  // Set the LOW state to the GPIO pins
  motorPin1.DigitalWrite(LOW);
  motorPin2.DigitalWrite(LOW);
  motorPin3.DigitalWrite(LOW);
  motorPin4.DigitalWrite(LOW);
}