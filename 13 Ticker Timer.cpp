#include "mbed.h"

DigitalOut led1(LED1), led2(D7);
Ticker tic,tic2,tic3;

void flip(){ led2=!led2; }
void flip2(){ led1=!led1; }

bool ready=false;
void flip3(){ ready=true; }

int main() {
    tic.attach_us(&flip,100000);
    tic2.attach(&flip2,1);
    tic3.attach(&flip3,2);
    while(1) {
        if(ready){
            printf("2 sec\n");
            ready=false;
        }
  }
}
