#ifndef H_STEPPERMOTOR_H
#define H_STEPPERMOTOR_H

#include <thread>
#include <mutex>
#include <vector>

#include "GPIO.h"

enum STEPPER_MODE 
{
  fullStep1Coil,
  fullStep2Coils,
  halfStep,
  driver,
};

enum DIRECTION
{
  CW = 1,
  CCW = 2,
};

const std::vector <std::vector<STATE>> fullStep1CoilVector 
{   
  {HIGH, LOW, LOW, LOW},
  {LOW, HIGH, LOW, LOW},
  {LOW, LOW, HIGH, LOW},
  {LOW, LOW, LOW, HIGH},
};

const std::vector <std::vector<STATE>> halfStepVector 
{   
  {HIGH, LOW, LOW, LOW},
  {HIGH, HIGH, LOW, LOW},
  {LOW, HIGH, LOW, HIGH},
  {LOW, HIGH, HIGH, LOW},
  {LOW, LOW, HIGH, LOW},
  {LOW, LOW, HIGH, HIGH},
  {LOW, LOW, LOW, HIGH},
  {HIGH, LOW, LOW, HIGH},
};

const std::vector <std::vector<STATE>> fullStep2CoilsVector 
{   
  {HIGH, HIGH, LOW, LOW},
  {LOW, HIGH, HIGH, LOW},
  {LOW, LOW, HIGH, HIGH},
  {HIGH, LOW, LOW, HIGH}
};

/* 
  Vector of threads to store each turn.
  C++17 inline signals the linker that only one instance 
  of the variable should exist
*/ 
// inline std::vector <std::thread> stepperThreads;


/* 
  Mutex instance to protect the GPIO access from the threads
  C++17 inline signals the linker that only one instance 
  of the variable should exist
*/ 
// inline std::mutex stepperMutex;

class StepperMotor
{
private:
  GPIO motorPin1;
  GPIO motorPin2;
  GPIO motorPin3;
  GPIO motorPin4;

  STEPPER_MODE controlMode;

  // Explicit default stepper motor's parameters
  static const unsigned int defaultStepsPerRevolution {2048};
  static const unsigned int defaultMaxStepsPerSecond {500};

  unsigned int stepsPerRevolution;
  unsigned int maxStepsPerSecond;

  // Number of the steps required to be activated according to the stepper motor's  mode
  unsigned int stepsPerMode;

  // Absolute steps counter during the program execution
  int stepsCounter;

  // Actual position in steps, of the stepper motor axis
  int currentStep;

  // Initialize the GPIO pins with the data provided by the constructor
  virtual void InitMotorPins();

  // Method to activate the coils for only 1 step  
  virtual void Turn1Step(int, int);

  // Mutexes to protect the shared variables
  std::mutex mut;
 
  // Flag for stopping the thread from the main program
  bool finishThreadFlag {false};

  // Method to turn the motor by steps continuously in a thread
  virtual void MakeTurnByStepsInThread(DIRECTION, unsigned int, unsigned int, bool);

  // Vector of threads to store each turn.
  std::vector <std::thread> stepperThreadsVector;

public:
  // Default constructor
  StepperMotor();

  // Overload constructor
  StepperMotor( 
                GPIO, GPIO, GPIO, GPIO, 
                STEPPER_MODE controlMode = fullStep1Coil,
                unsigned int stepsPerRevolution = defaultStepsPerRevolution, 
                unsigned int maxStepsPerSecond = defaultMaxStepsPerSecond 
              );

  // Interface method to turn the motor by steps
  virtual void TurnBySteps(
                            DIRECTION, 
                            unsigned int stepsRequired, 
                            unsigned int speed = defaultMaxStepsPerSecond, 
                            bool printMessages = false
                          );

  // Interface method to turn the motor by degrees
  virtual void TurnByDegrees(
                            DIRECTION, 
                            double degreesRequired, 
                            double speed = defaultMaxStepsPerSecond, 
                            bool printMessages = false
                          );

  // Interface method to turn the motor by steps continuously
  virtual void TurnByStepsInThread(
                                    DIRECTION, 
                                    unsigned int stepsRequired,
                                    unsigned int speed = defaultMaxStepsPerSecond, 
                                    bool printMessages = false
                                  );

  // Interface method to turn the motor by degrees continuously
  virtual void TurnByDegreesInThread(
                                    DIRECTION, 
                                    double degreesRequired,
                                    double speed = defaultMaxStepsPerSecond, 
                                    bool printMessages = false
                                  );

  // Interface method to get the stopping flag
  virtual bool GetFinishThreadFlag();

  // Interface method to set the stopping flag
  virtual void SetFinishThreadFlag(bool);


  // Interface method to get the absolute steps counter
  virtual int GetStepsCounter();

  // Interface method to set the absolute steps counter 
  virtual void SetStepsCounter(int);

   // Interface method to get the current step position of the axis
  virtual int GetCurrentStep();

  // Interface method to set the current step position of the axis 
  virtual void SetCurrentStep(int);

  // Destructor
  virtual ~StepperMotor();
};

#endif // H_STEPPERMOTOR_H