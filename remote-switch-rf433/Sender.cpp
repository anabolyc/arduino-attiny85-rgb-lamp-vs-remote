#include "Sender.h"
#include <VirtualWire.h>


Sender::Sender(uint8_t rftPin, uint16_t speed) {
  this->pin = rftPin;
  this->speed = speed;
  this->initialized = false;
}

void Sender::init() {
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(pin);
  vw_setup(speed);
  this->initialized = true;
}

void Sender::start() {
  if (!this->initialized)
    this->init();
}

uint8_t Sender::send(uint8_t* buffer, uint8_t buflen) {
  vw_send(buffer, buflen);
  vw_wait_tx();
}
