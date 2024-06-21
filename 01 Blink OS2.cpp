#include "mbed.h"

DigitalOut myled(LED1);

void flash(){
    myled = 1;
    wait(0.02);
    myled = 0;
    wait(0.02);
}

int main() {
    int cnt = 0;
  while(1) {
    //   for (int i=0; i<3; i++){ //  blink led
    //         flash();
    //   }     
    //   wait(3.);

    printf("I'm mbed! - %u \n", cnt); // serial
    wait(1.);
    cnt++;
  }
}