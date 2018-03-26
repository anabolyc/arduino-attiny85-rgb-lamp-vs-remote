#include "Receiver.h"
#include "Rgb.h"

#define PIN_COL0B       _BV(PINB2)
#define PIN_COL1B       _BV(PINB1)
#define PIN_COL2B       _BV(PINB4)

#define RGB_COL_DUR    9000

#define RF_SPEED_BPS    984
#define RF_PIN_R          3

//#define PIN_SENSOR      _BV(PINB0)
//#define PIN_RELAY       _BV(PINB5)

#define MESSAGE_LEN 4
uint8_t CMD_ON [MESSAGE_LEN] = {"sa5"};
uint8_t CMD_OFF[MESSAGE_LEN] = {"xHM"};

Receiver receiver(RF_PIN_R, RF_SPEED_BPS);
RGB rgb(RGB_COL_DUR);

void setup() {
  // Pin mode - rgb outputs, relay - output, sensor input
  DDRB |= PIN_COL0B | PIN_COL1B | PIN_COL2B /*| PIN_RELAY & ~PIN_SENSOR*/;

  // start listening RF module
  receiver.start();

  // init all rgb logic
  rgb.start();
}

ISR(TIM0_COMPB_vect) {
  if (rgb.isOn())
    PORTB |= PIN_COL0B;
}

ISR(TIM0_OVF_vect) {
  PORTB &= ~PIN_COL0B;
}

void loop() {
  // check if radio command available
  int8_t rf_state = check_rf();

  if (rf_state == 1)
    rgb.on();
  else if (rf_state == -1)
    rgb.off();

/*
  // check sensor - relay pair
  if (PINB & PIN_SENSOR)
    PORTB |= PIN_RELAY;
  else
    PORTB &= ~PIN_RELAY;
*/
  // loop rgb cycle
  rgb.loop();
}

int8_t check_rf() {
  uint8_t buf[MESSAGE_LEN];
  uint8_t buflen = MESSAGE_LEN;

  if (receiver.message(buf, &buflen)) {
    if (str_cmp(buf, CMD_ON))
      return 1;
    if (str_cmp(buf, CMD_OFF))
      return -1;
  }
  return 0;
}

bool str_cmp(uint8_t* a, uint8_t* b) {
  for (int i = 0; i < MESSAGE_LEN; i++)
    if (a[i] != b[i])
      return false;
  return true;
}
