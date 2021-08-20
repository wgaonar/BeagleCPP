#ifndef GPIO_H
#define GPIO_H

#include <string>
#include <fstream>
#include <thread>
#include <map>

#include "RAINBOWCOLORS.h"
#include "BLACKPIN_ID.h"
#include "SYSFILEACCESS.h"
#include "MISCELLANEOUS.h"

/* 
  Declare a type for a function pointer
  It is the construct for: using function_type = int (*) ()
    function_type:  the function name
    int: return type  
    (*): the dereference operator due to the address of the function name
    (): the arguments of the function, in this case void
  Stores the address of a function 
*/
using callbackType = int (*)();

const std::string GPIO_PATH("/sys/class/gpio/");

/* The numeric mode for MODE: e.g. 0/1 for OUTPUT/INPUT */
enum MODE {
  OUTPUT = 0,
  INPUT = 1,
};

/* The numeric value for VALUE: e.g. 0/1 for LOW/HIGH */
enum STATE {
  LOW = 0,
  HIGH = 1,
};

class GPIO : public SYSFILEACCESS
{
  protected:
    GPIO_ID id;         /* Enum for the Kernel GPIO number of the object */
    MODE mode;          /* The GPIO mode e.g. OUTPUT / INPUT*/
    std::string name;   /* The name of the GPIO e.g. gpio44 */
    std::string path;   /* The full path to the GPIO e.g. /sys/class/gpio/gpio44 */

    std::ofstream stream;

    /* Map to store the BeagleBone Black pin`s kernel number with its header name */
    std::map <int, std::string> blackPinIdMap;

    // Initialize the GPIO pin with the data provided by the constructor
    void InitGPIOPin();

    // Initialize the GPIO pin id map kernel's number -> header's name
    void InitPinIdMap();  

  public:
    // Default constructor
    GPIO ();

    // Overload constructor with the pin`s name
    GPIO (GPIO_ID);

    // Overload constructor with the pin id and mode
    GPIO (GPIO_ID, MODE);

    // Copy construnctor
    GPIO (GPIO&);

    // Accessor method to get the kernel pin's number
    virtual int GetPinKernelId();

    // Accessor method to get the header pin's name
    virtual std::string GetPinHeaderId();

    // Accessor method to get the pin's mode
    virtual MODE GetMode();

    // Mutator method to set the pin's mode
    virtual int SetMode(MODE);

    // Method to export the GPIO pin
    virtual int ExportGPIO();

    // Method to unexport the GPIO pin
    virtual int UnexportGPIO();

    // Interface method to set the GPIO pin state
    virtual int DigitalWrite(STATE);

    // Overload Interface method to set the GPIO pin state and printing the value
    virtual int DigitalWrite(STATE, bool);

    //Interface method to open the stream to fast write
    virtual int StreamOpen();

    // Overload Interface method to set the GPIO pin state using stringstream
    virtual int StreamWrite(STATE);
    
    //Interface method to close the stream to fast write
    virtual int StreamClose();

    // Interface method to get the GPIO pin state
    virtual STATE DigitalRead();

    // Method to do execute an user function
    virtual int DoUserFunction(callbackType);

    // Destructor
    virtual ~GPIO ();    
};

#endif // GPIO_H