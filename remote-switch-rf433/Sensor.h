#ifndef __SENSOR_h__
#define __SENSOR_h__

#include "Arduino.h"
#include <CapacitiveSensor.h>

class Sensor: public CapacitiveSensor
{
  public:
    Sensor(uint8_t srcPin, uint8_t drainPin, uint16_t treshold, uint16_t clickTime);
    uint8_t loop();
    
    uint16_t capacity = 0;
  private:
    uint8_t samples = 100;
    uint16_t treshold;
    uint16_t clickTime;

    bool btn_state = 0;
    bool btn_clicked = 0;
    unsigned long btn_on_since = 0;
};

#endif

