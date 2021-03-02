#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>
#include <cstdlib>  // system()

#include "PWM.h"

using namespace std;

class PWM_Exception : public exception 
{
  private:
    string reason;
  public:
    PWM_Exception (const char* why) : reason (why) {};
    virtual const char* what() 
    {
      return reason.c_str();
    }
};

// Default constructor
PWM::PWM() {}

// Overload constructor with the pin's id
PWM::PWM(int newPWMPin)
{
  id = newPWMPin;
  period = 500000;
  InitPWMPin();
  SetPeriod(period);
}

// Overload constructor 
PWM::PWM(int pwmPin, int newPeriod)
{
  id = pwmPin;
  period = newPeriod;
  InitPWMPin();
  SetPeriod(newPeriod); 
  cout  << RainbowText("Setting the PWM pin with a period of ", "Pink")
        << RainbowText(to_string(GetPeriod()), "Pink") 
        << RainbowText("ns was a success!", "Pink") << endl; 
}

// Public method to initialize the PWM pin
void PWM::InitPWMPin()
{
  idMap[P8_13] = "P8.13";
  idMap[P8_19] = "P8.19";
  idMap[P9_14] = "P9.14";
  idMap[P9_16] = "P9.16";
  idMap[P9_21] = "P9.21";
  idMap[P9_22] = "P9.22";

  switch (id)
  {
  case P8_13:
    name = EHRPWM2_PATH + "pwmchip6/pwm-6:1/";
    break;
  case P8_19:
    name = EHRPWM2_PATH + "pwmchip6/pwm-6:0/";
    break;
  case P9_14:
    name = EHRPWM1_PATH + "pwmchip3/pwm-3:0/";
    break;
  case P9_16:
    name = EHRPWM1_PATH + "pwmchip3/pwm-3:1/";
    break;
  case P9_21:
    name = EHRPWM0_PATH + "pwmchip1/pwm-1:1/";
    break;
  case P9_22:
    name = EHRPWM0_PATH + "pwmchip1/pwm-1:0/";
    break;
  default:
    break;
  }
  path = PWM_PATH + name;

  cout  << RainbowText("Trying to enable the PWM pin: ","Pink") 
        << RainbowText(idMap[id], "Pink", "Default", "Bold") << endl;
  string commandString = "config-pin " + idMap[id] + " pwm";
  const char* command = commandString.c_str();
  system(command);

  Enable();
}

/*
   Private method to enable the PWM on the pin.
   It is used in the constructor
   @return int: 1 set duty cycle has succeeded / throw an exception if not
*/
int PWM::Enable()
{
  if (WriteFile(path, "enable", 1) != 1)
  {
    perror("Error trying to enable the PWM on the pin");
    throw PWM_Exception("Error in the 'Enable' method");
  }
  else 
  {
    return 1;
  }
}

/*
   Private method to disable the PWM on the pin.
   It is used in the constructor
   @return int: 1 set duty cycle has succeeded / throw an exception if not
*/
int PWM::Disable()
{
  if (WriteFile(path, "enable", 0) != 1)
  {
    perror("Error trying to disable the PWM on the pin");
    throw PWM_Exception("Error in the 'Disable' method");
  }
  else 
  {
    return 1;
  }
}

/*
   Public method to get the period 
   @return int: The pin's period
*/
int PWM::GetPeriod()
{
  return period;
}

/*
   Public method to get the period 
   @return int: The pin's duty cycle
*/
int PWM::GetDutyCycle()
{
  return dutyCycle;
}

/*
  Public method to set the period of the PWM
  The chosen period is in nanoseconds 
  @param int: The desired period
  @return int: 1 set period has succeeded / throw an exception if not
*/
int PWM::SetPeriod(int newPeriod)
{
  period = newPeriod;
  if (WriteFile(path, "period", period) != 1)
  {
    perror("Error setting the PWM period for the pin");
    throw PWM_Exception("Error in the 'SetPeriod' method");
  }
  else 
  {
    return 1;
  }
}

/*
   Public method to set the duty cycle of the PWM
   @param int: The desired duty cycle in pertentage: 0-100
   @return  int: 1 set duty cycle has succeeded / throw an exception if not
*/
int PWM::SetDutyCycle(int newDutyCycle)
{
  if (newDutyCycle >= 0 && newDutyCycle <= 100)
    dutyCycle = static_cast<int>(newDutyCycle / 100.0 * period);
  else if (newDutyCycle < 0)
    dutyCycle = 0;
  else
    dutyCycle = 100;
  
  if (WriteFile(path, "duty_cycle", dutyCycle) == 1)
    return 1;
  else 
  {
    perror("Error setting the PWM duty cycle for the pin");
    throw PWM_Exception("Error in WritePWMDutyCycle method");
  }
}

/*
  Public method to do a delay in milliseconds
  @param int: duration of the delay
*/
void PWM::Delayms(int millisecondsToSleep) 
{
  this_thread::sleep_for(chrono::milliseconds(millisecondsToSleep));
}

/*
  Public callback method to do a user customized function when is called
  @param callbackType: user function pointer to execute 
  @return int: 1 the user function was called      
*/
int PWM::DoUserFunction (callbackType callbackFunction)
{
  string message = "'UserFunction' method has been activated!";
  cout << RainbowText(message, "Orange") << endl;

  std::thread functionThread(callbackFunction);
  functionThread.detach();
  return 1;
}

// Destructor
PWM::~PWM() 
{
  this->SetDutyCycle(0);
}