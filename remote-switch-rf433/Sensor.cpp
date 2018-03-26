#include "Sensor.h"

Sensor::Sensor(uint8_t srcPin, uint8_t drainPin, uint16_t treshold, uint16_t clickTime)
  : CapacitiveSensor(srcPin, drainPin) {
  this->treshold = treshold;
  this->clickTime = clickTime;
}

// 0 - no action detected
// 1 - button is touched less then click time
// 2 - button is touched and click is detected - will fire once
// 3 - button is touched, click already fired 
uint8_t Sensor::loop() {
  capacity = this->capacitiveSensor(100);

  if (capacity > treshold) {
    // button is touched
    if (btn_state == 0) {
      btn_state = 1;
      btn_on_since = millis();
      return 1;
    } else if (btn_state == 1) {
      if (btn_clicked)
        return 3;
      else if (millis() > btn_on_since + clickTime) {
        btn_clicked = 1;
        return 2;
      } else {
        return 1;
      }
    }
  } else {
    // no touch detected
    btn_state = 0;
    btn_clicked = 0;
    return 0;
  }
  
}

