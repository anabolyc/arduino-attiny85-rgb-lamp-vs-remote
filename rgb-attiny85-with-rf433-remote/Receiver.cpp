#include "Receiver.h"
#include <VirtualWire.h>


Receiver::Receiver(uint8_t rfrPin, uint16_t speed) {
  this->pin = rfrPin;
  this->speed = speed;
  this->initialized = false;
}

void Receiver::init() {
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(pin);
  vw_setup(speed);
  this->initialized = true;
}

void Receiver::start() {
  if (!this->initialized)
    this->init();
  vw_rx_start();
}

uint8_t Receiver::message(uint8_t* buffer, uint8_t* buflen) {
  return vw_get_message(buffer, buflen);
}
