#include "Sender.h"
#include "Sensor.h"

//#define __SERIAL__
#define SERIAL_SPEED 115200

#ifdef __AVR_ATmega328P__
#define PIN_LED 13
#define PIN_RFT 3
#endif
#ifdef __AVR_ATtiny85__
#define PIN_LED 1
#define PIN_RFT 0
#endif

#define CAP_PIN_SRC   3
#define CAP_PIN_DRAIN 4
#define CAP_THRESHLD  200
#define CAP_CLICK_MS  100

#define RF_SPEED_BPS 984

#define MESSAGE_LEN 4
uint8_t CMD_ON [MESSAGE_LEN] = {"sa5"};
uint8_t CMD_OFF[MESSAGE_LEN] = {"xHM"};

Sender sender(PIN_RFT, RF_SPEED_BPS);
Sensor sensor(CAP_PIN_SRC, CAP_PIN_DRAIN, CAP_THRESHLD, CAP_CLICK_MS);

bool led_state = 1;

void setup() {
#ifdef __SERIAL__
  Serial.begin(SERIAL_SPEED);
  Serial.println("");
#endif
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED,  led_state);

  // start RF module
  sender.start();
}

void loop() {
  int res = sensor.loop();

  if (res == 2) {
    if (led_state == 0) {
      led_state  = 1;
      sender.send((uint8_t *)CMD_ON, MESSAGE_LEN);
    } else if (led_state == 1) {
      led_state  = 0;
      sender.send((uint8_t *)CMD_OFF, MESSAGE_LEN);
    }
  } else if (res == 3) {
    if (led_state == 0) {
      sender.send((uint8_t *)CMD_OFF, MESSAGE_LEN);
    } else if (led_state == 1) {
      sender.send((uint8_t *)CMD_ON, MESSAGE_LEN);
    }
  }

  digitalWrite(PIN_LED,  led_state);
#ifdef __SERIAL__
  Serial.println(sensor.capacity);
#endif
}
