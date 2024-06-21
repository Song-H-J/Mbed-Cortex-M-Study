#include "mbed.h"

DigitalOut myled(LED1), spk(D5);
DigitalIn spkBut(USER_BUTTON), but(D2, PullUp);

void play(){
    spk=!spk;
    wait_us(500);
}

int main() {
  while(1) {
      if(!but){
          myled=!myled;
          wait(0.3);
      }

      if(!spkBut){
          play();
      }
  }
}
