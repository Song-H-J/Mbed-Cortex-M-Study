#include "mbed.h"

AnalogIn an[6]={A0,A1,A2,A3,A4,A5};

int main() {
  while(1) {
      for(int i=0; i<6; i++){
        printf("[%d]=%4.1f\n",i,an[i].read()*3.3);
      }
      printf("\n");
      wait_ms(100);
  }
}
