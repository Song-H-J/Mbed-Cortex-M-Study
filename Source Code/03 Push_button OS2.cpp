#include "mbed.h"
DigitalIn mybutton(PC_13); // USER_BUTTON in pin map
DigitalOut myled(D13); // LED1 in pin map

int main() {
  while(1) {
      myled.write(mybutton.read()); // normal
    //   myled = mybutton; // used Operator Overloading twice
    //   myled.write(!mybutton.read());
      printf("%s\n", (mybutton)? "ON":"OFF");
  }
}