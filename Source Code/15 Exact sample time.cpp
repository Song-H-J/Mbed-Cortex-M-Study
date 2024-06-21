#include "mbed.h"

// DigitalOut led(D7);
DigitalOut led1(LED1), led2(D7,1);
void off(){led2=0;}
int main() {
    Timeout tmo;
    tmo.attach(&off,10);
    // Timer tmr;
    // tmr.start();
  while(1) {
    // if(tmr.read_us()>20000){
    //     tmr.reset();
    //     led=!led;
    // }
    led1=!led1;
    wait_ms(100);
  }
}