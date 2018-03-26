#ifndef __SENDER_h__
#define __SENDER_h__

#include "Arduino.h"

class Sender
{
  public:
    Sender(uint8_t rftPin, uint16_t speed);

    void start();
    uint8_t send(uint8_t* buffer, uint8_t buflen);

protected:
      void init();

private:
      uint8_t pin;
      uint16_t speed;
      bool initialized;

};

#endif

