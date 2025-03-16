/******************************************************************************
Listing_5.1.cpp
@wgaonar
02/04/2021
https://github.com/wgaonar/BeagleCPP

Read 100 times the analog value on AIN0 (P9_39) each 100 milliseconds

Class: ADC
******************************************************************************/
#include <iostream>
#include "../../Sources/ADC.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "Setting  ADC mode on a pin";
  cout << RainbowText(message, "Blue") << endl;
  ADC adcPin(P9_39);

  message = "Read an analog value [0-4095] and wait 100 milliseconds between each read";
  cout << RainbowText(message, "Blue") << endl;

  int adcValue = 0;
  int intervalTime = 100;
  for (int i = 0; i < 100; i++) 
  {
    adcValue = adcPin.ReadADC(intervalTime);
    cout << "Reading " << i+1 << " of " << "100: " << adcValue << " [0 - 4095]" << endl;
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}

// Bone  | Pocket | AIN
// ----- | ------ | ---
// P9_39 | P1_19  | 0
// P9_40 | P1_21  | 1
// P9_37 | P1_23  | 2
// P9_38 | P1_25  | 3
// P9_33 | P1_27  | 4
// P9_36 | P2_35  | 5
// P9_35 | P1_02  | 6

//  AIN    |  Bone  | Pocket | AIN
// ------- | ------ | -----  | ----
// VDD_ADC | P9_32  | P1.18  | 1.8V
// GND_ADC | P9_34  | P1.17  | 0V 
