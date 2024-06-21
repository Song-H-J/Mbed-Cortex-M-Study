#include "mbed.h"

class Blink{
    DigitalOut led;
    Ticker tic;
    void flip(){ led=!led; }
  public:
    Blink(PinName pin) : led(pin){}
    void begin(float perd){ tic.attach(callback(this, &Blink::flip), perd); }
};