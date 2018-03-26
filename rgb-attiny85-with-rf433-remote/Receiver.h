#ifndef __RECEIVER_h__
#define __RECEIVER_h__

#include "Arduino.h"

class Receiver
{

public:
  Receiver(uint8_t rfrPin, uint16_t speed);

  void start();
  uint8_t message(uint8_t* buffer, uint8_t* buflen);

protected:
  void init();

private:
  uint8_t pin;
  uint16_t speed;
  bool initialized;

}; 

#endif

