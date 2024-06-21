#include "mbed.h"
#include "blink.h"

Serial pc(USBTX,USBRX,115200);

Blink b1(LED1), b2(D7);
int main() {
    b1.begin(0.1);
    b2.begin(0.02);
    float x=0, y=0;
    Timer tmr;
  while(1) {
    //   tmr.start(); // calc time check
    //   y = atan(sin(x*x)+cos(y*y));
    //   tmr.stop();
    //   printf("time = %d us\n", tmr.read_us());
    //   x+=0.01;
    //   tmr.reset();
    //   wait(1.);

    //   tmr.start(); // serial time check
    //   printf("123456789012345\n");
    //   tmr.stop();
    //   printf("time = %d us\n", tmr.read_us());
    // //   x+=0.01;
    //   tmr.reset();
    //   wait(1.);

      tmr.start();
      pc.printf("123456789012345\n");
      tmr.stop();
      pc.printf("time = %d us\n", tmr.read_us());
      tmr.reset();
      wait(1.);
  }
}