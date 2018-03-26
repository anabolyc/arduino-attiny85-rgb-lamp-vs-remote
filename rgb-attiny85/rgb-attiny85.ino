#include "Rgb.h"

#define PIN_COL0B       _BV(PINB0)
#define PIN_COL1B       _BV(PINB1)
#define PIN_COL2B       _BV(PINB4)

#define RGB_COL_DUR    9000

RGB rgb(RGB_COL_DUR);

void setup() {
  // Pin mode - output
  DDRB |= PIN_COL0B | PIN_COL1B | PIN_COL2B;

  // init all rgb logic
  rgb.start();
}

void loop() {
  // possible to control fro outside
  int8_t state = 0;

  if (state == 1)
    rgb.on();
  else if (state == -1)
    rgb.off();

  rgb.loop();
}
