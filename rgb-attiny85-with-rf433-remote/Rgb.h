#ifndef __RGB_h__
#define __RGB_h__

#include "Arduino.h"

//#define RGB_COLOR_DEBUG
#define RGB_COL_FPS  30

class RGB
{

  public:
    RGB(uint16_t duration);

    volatile uint8_t* Port[3] = { &OCR0B, &OCR1A, &OCR1B };

    void start();
    void loop();
    void on();
    void off();
    bool isOn();

  protected:
    void init();
    bool initialized = false;
    bool ledOn = true;
    bool ledState = true;

  private:

    #ifdef RGB_COLOR_DEBUG
    long seq = 0;
    #endif

    uint8_t lastColor[3] = {0, 0, 0};
    uint8_t nextColor[3] = {0, 0, 0};
    uint8_t currColor[3] = {0, 0, 0};
    uint8_t COL_BLACK[3] = {0, 0, 0};

    unsigned long frame_duration_ms = 1000 / RGB_COL_FPS;
    unsigned long frame_index = -1;
    unsigned long next_frame_ms = 0;
    unsigned long transition_frames;

    const uint8_t COL_MAX[3] = {0xFE, 0x80, 0x80};

    void copyColor(uint8_t from[], uint8_t to[]);
    void setColor(uint8_t color[]);
    void getCurrentColor(uint8_t prev[], uint8_t next[], uint8_t dest[], long frameIndex, long frameCount);
    void getRandomColor(uint8_t dest[]);

};

#endif

