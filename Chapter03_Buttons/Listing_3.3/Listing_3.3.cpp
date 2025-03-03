/******************************************************************************
Listing_3.3.cpp
@wgaonar
02/03/2025
https://github.com/wgaonar/BeagleCPP

Uses the AddEventDetection() method to call a user defined callback 
function to wait for the press on a button connected with a Pulldown resistor

Class: BUTTON
******************************************************************************/

#include <iostream>
#include "../../Sources/BUTTON.h"

using namespace std;

// Global pin declaration
BUTTON redButtonPin(P8_08);

int UserCallBackFunction_ButtonRed() {
  cout << "Hello, I am a USER defined callback function!\n"; 
  cout << "The red button was pressed!!!" << endl;
  return 0;   
}

int main() {
  string message = "Main function starting here...";
  cout << endl << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  cout  << "The program is timing for 10 seconds and is awaiting " << endl
        << "if a press on a button occurs" << endl;

  redButtonPin.AddEventDetection(RISING, &UserCallBackFunction_ButtonRed);
  for (int i = 10; i > 0; i--) {
    cout << i << endl;
    DelayMilliseconds(1000);
  }

  message = "Main function ends here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl << endl;
  return 0;
}