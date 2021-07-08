#include <iostream>
#include <chrono>
#include <thread>

#include "LED.h"

// Default constructor
LED::LED() {}

// Overload constructor
LED::LED(GPIO_ID newId) : GPIO(newId, OUTPUT) {
  std::cout  << RainbowText("Led object was created on pin: ", "Light Blue") 
        << RainbowText(this->GetPinHeaderId(), "Light Blue", "Default", "Bold") 
        << std::endl << std::endl;
}

/*
  Public method to turn on the Led attached to the pin 
*/
void LED::TurnOn() {
  this->DigitalWrite(HIGH);
}

/*
  Public method to turn on the Led attached to the pin 
*/
void LED::TurnOff() {
  this->DigitalWrite(LOW);
}

/*
  Public method to toggle the Led attached to the pin 
*/
void LED::Toggle() {
  if (this->DigitalRead() == LOW)
    this->DigitalWrite(HIGH);
  else
    this->DigitalWrite(LOW);
}

/*
  Public method to make a blink on the pin 
  @param int: The desired duration in milliseconds
*/
void LED::Blink(int duration) {
  std::string message {
    "Blinking has been activated with duration of: "
    + std::to_string(duration) + "ms on pin: " + this->GetPinHeaderId()
  };
  std::cout << RainbowText(message, "Light Blue", "Default", "Bold") << std::endl; 
  blinkThread = std::thread(&LED::MakeBlink, this, duration);
}

/*
  Private method that contains the routine to blink 
  @param int: The desired duration in milliseconds
*/
void LED::MakeBlink(int duration) {
  while (this->stopBlinkFlag == false) {
    this->DigitalWrite(HIGH);
    Delayms(duration);
    this->DigitalWrite(LOW);
    Delayms(duration);
  }
}

/*
  Public method to stop the blinking on the pin 
*/
void LED::StopBlink () {
  this->stopBlinkFlag = true;
}

/*
  Public method to make a flash on the pin 
  @param int: The desired time ON in milliseconds
  @param int: The desired period in milliseconds
*/
void LED::Flash(int timeOn, int period) {
  std::string message {
    "Flashing has been activated with a time ON of: "
    + std::to_string(timeOn) + "ms on a period of: " 
    + std::to_string(period) + "ms on pin: " + this->GetPinHeaderId()
  };
  std::cout << RainbowText(message, "Light Blue", "Default", "Bold") << std::endl;
  flashThread = std::thread(&LED::MakeFlash, this, timeOn, period);
}

/*
  Private method that contains the routine to flash
  @param int: The desired time ON in milliseconds
  @param int: The desired period in milliseconds
*/
void LED::MakeFlash(int timeOn, int period) {
  while (this->stopFlashFlag == false) {
    this->DigitalWrite(HIGH);
    Delayms(timeOn);
    this->DigitalWrite(LOW);
    Delayms(period - timeOn);
  }
}

/*
  Public method to stop the flash on the pin 
*/
void LED::StopFlash () {
  this->stopFlashFlag = true;
}

/*
  Public method to make a digital heart beat on the pin 
  @param int: The desired time On of the pulse in milliseconds
  @param int: The desired period in milliseconds
*/
void LED::HeartBeat(int timeOn, int period)
{
  std::string message {
    "Heart beat has been activated with a time ON of: "
    + std::to_string(timeOn) + " on a period of: " 
    + std::to_string(period) + "ms on pin: " + this->GetPinHeaderId()
  };
  std::cout << RainbowText(message, "Light Blue", "Default", "Bold") << std::endl;
  heartBeatThread = std::thread(&LED::MakeHeartBeat, this, timeOn, period);
}

/*
   Private method that contains the routine to do the digital heart beat 
   @param int: The desired time On of the pulse in milliseconds
   @param int: The desired period in milliseconds
*/
void LED::MakeHeartBeat(int timeOn, int period)
{
  while (this->stopHeartBeatFlag == false) {
    for (int i = 0; i < 2; i++) {
      this->DigitalWrite(HIGH);
      Delayms(timeOn);
      this->DigitalWrite(LOW);
      Delayms(timeOn);
    }
    Delayms(period - 4 * timeOn);
  }
}

/*
  Public method to stop the digital heart beat on the pin 
*/
void LED::StopHeartBeat ()
{
  this->stopHeartBeatFlag = true;
}

// Destructor
LED::~LED() {
  if(this->DigitalRead() == HIGH) 
    this->DigitalWrite(LOW);
  if (blinkThread.joinable()) 
    blinkThread.join();
  if (flashThread.joinable()) 
    flashThread.join();
  if (heartBeatThread.joinable()) 
    heartBeatThread.join();
}