#ifndef PWM_H
#define PWM_H

#include <string>
#include <thread>

#include "SYSFILEACCESS.h"

/* 
  Declare a type for a function pointer
  It is the construct for: using function_type = int (*) ()
    function_type:  the function name
    int: return type  
    (*): the dereference operator due to the address of the function name
    (): the arguments of the function, in this case: void
  Stores the address of a function 
*/
using callbackType = int (*)();

const std::string PWM_PATH ("/sys/devices/platform/ocp/");
const std::string EHRPWM0_PATH = "48300000.epwmss/48300200.pwm/pwm/";
const std::string EHRPWM1_PATH = "48302000.epwmss/48302200.pwm/pwm/";
const std::string EHRPWM2_PATH = "48304000.epwmss/48304200.pwm/pwm/";

class PWM : public SYSFILEACCESS
{
  private:
    PWM_ID id; /* The PWM number of the object */
    std::string idMap[6];
    std::string chipName; /* The chip name of the PWM*/
    std::string name;   /* The name with the number of the PWM e.g. pwm0 */
    std::string path;   /* The variable to store the path to the name of the pwm pin */
    int interfaceNumber; /* The interface number of each chip (0/1)*/
    int period;
    int dutyCycle;

    // Initialize the PWM pin with the data provided by the constructor
    void InitPWMPin();

  public:
    // Default constructor
    PWM();

    // Overload constructor with pin's id
    PWM(PWM_ID);

    // Overload constructor with the pin id and period
    PWM(PWM_ID, int);

    // Helper method to export the pwm module on the pin
    virtual int Export(int);

    // Helper method to enable the pwm on the pin
    virtual int Enable();

    // Helper method to disable the pwm on the pin
    virtual int Disable();

    // Accessor method to get the header pin's name
    virtual std::string GetPinHeaderId();

    // Interface method to get the period
    virtual int GetPeriod();

    // Interface method to get the duty cycle
    virtual int GetDutyCycle();

    // Interface method to set the period
    virtual int SetPeriod(int);

    // Interface method to set the duty cycle
    virtual int SetDutyCycle(int);

    // Interface method to set the duty cycle by period
    virtual int SetDutyCycleByPeriod(int);
    
    // Method to execute an user function
    virtual int DoUserFunction(callbackType);

    // Destructor
    virtual ~PWM();

};
#endif // PWM_H