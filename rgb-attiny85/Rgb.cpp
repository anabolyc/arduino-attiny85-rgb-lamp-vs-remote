#include "Rgb.h"

RGB::RGB(uint16_t duration) {
  this->transition_frames = duration / frame_duration_ms;
}

void RGB::init() {
  // Setup 2 PWMs on Timer0 on OC0A/PB0 and OC0B/PB1
  TCCR0A = B10<<COM0A0 | B10<<COM0B0 | 1<<WGM01 | 1<<WGM00;
  TCCR0B = 0<<WGM02  | B10<<CS00; // CLK/8
  
  // Configure third PWM on Timer1 OC1B/PB4
  GTCCR = 1<<PWM1B | B10<<COM1B0;
  TCCR1 = B0100<<CS10; // CLK/8

  this->initialized = true;
}

void RGB::start() {
  if (!this->initialized)
    this->init();
}

void RGB::on() {
  ledState = true;
}

void RGB::off() {
  ledState = false;
}

bool RGB::isOn() {
  return ledOn;
}

void RGB::loop() {
  if (ledState) {
    if (frame_index >= transition_frames || !ledOn) {
      frame_index = 0;
      copyColor(nextColor, lastColor);
      getRandomColor(nextColor);
      ledOn = true;
    }

    // TODO: can freeze here on millis() overflow / 49 days
    if (millis() >= next_frame_ms) {
      getCurrentColor(lastColor, nextColor, currColor, frame_index, transition_frames);
      setColor(currColor);
      frame_index++;
      next_frame_ms = millis() + frame_duration_ms;
    }
  } else {
    if (ledOn) {
      copyColor(COL_BLACK, nextColor);
      setColor(COL_BLACK);
      ledOn = false;
    }
  }
}

void RGB::copyColor(uint8_t from[], uint8_t to[]) {
  for (int i = 0; i < 3; i++)
    to[i] = from[i];
}


void RGB::setColor(uint8_t color[]) {
  *Port[0] = color[0];
  *Port[1] = color[1];
  *Port[2] = color[2];
}

void RGB::getCurrentColor(uint8_t prev[], uint8_t next[], uint8_t dest[], long frameIndex, long frameCount) {
  for ( int i = 0; i < 3; i++) {
    unsigned int prev0 = prev[i];
    unsigned int next0 = next[i];
    unsigned int curr0 = 0;
    if (next0 >= prev0)
      curr0 = prev0 + (next0 - prev0) * frameIndex / frameCount;
    else
      curr0 = prev0 - (prev0 - next0) * frameIndex / frameCount;
    dest[i] = curr0;
  }
}

#ifdef RGB_COLOR_DEBUG
#pragma message "RGB_COLOR_DEBUG mode"
// TEST COLORS RENDER CORRECTLY
void RGB::getRandomColor(uint8_t dest[]) {
  if (seq % 2 == 1) {
    dest[0] = 0;
    dest[1] = 0;
    dest[2] = 0;
  } else {
    dest[0] = (seq / 2) % 3 == 0 ? COL_MAX[0] : 0;
    dest[1] = (seq / 2) % 3 == 1 ? COL_MAX[1] : 0;
    dest[2] = (seq / 2) % 3 == 2 ? COL_MAX[2] : 0;
    /*
        dest[0] = 0;
        dest[1] = 0;
        dest[2] = COL_MAX[0]; */
  }
  seq++;
}
#else

void RGB::getRandomColor(uint8_t dest[]) {
  while (true) {
    unsigned int r = random(COL_MAX[0]);
    unsigned int g = random(COL_MAX[1]);
    unsigned int b = random(COL_MAX[2]);
    long total = r + g + b;
    if (total > COL_MAX[1] && total <= COL_MAX[1] * 2) {
      unsigned int avg = total / 3;
      if (abs(avg - r) > COL_MAX[0] / 2 || abs(avg - g) > COL_MAX[1] / 2 || abs(avg - b) > COL_MAX[2] / 2) {
        dest[0] = r;
        dest[1] = g;
        dest[2] = b;
        break;
      }
    }
  }
}
#endif


