#include "mbed.h"

DigitalOut led1(LED1), led2(D7);
// DigitalIn but(USER_BUTTON);
// InterruptIn but(USER_BUTTON);

void toggle(){led2=!led2;}
////////////////////////////////////////
enum MODE{UP,DOWN};
class Counter{
    InterruptIn sw;
    // volatile uint16_t count;
    volatile bool updated;

    MODE mode;
    public:
    static int16_t count;
    Counter(PinName _pin, MODE _mode) :sw(_pin), mode(_mode) {
        sw.mode(PullUp);
        if(mode == UP) sw.fall(callback(this, &Counter::countUp));
        else sw.fall(callback(this, &Counter::countDn));
    }// _ = temporary use, init

    void countUp(){count++; updated=true;}
    void countDn(){count--; updated=true;}
    int16_t read(){updated=false; return count;}
    bool isUpdated(){return updated;}
};

int16_t Counter::count = 0;
Counter cntDn(USER_BUTTON , DOWN);
Counter cntUp(D2, UP);
///////////////////////////////////////
int main() {
    //but.fall(&toggle);
  while(1) {
    //   led1 = !led1; wrong example
    //   if(!but){
    //       led2 = !led2;
    //   }
    //   wait_ms(1000);

    // led1=!led1; Interrupt example
    // wait_ms(1000);

    if(cntDn.isUpdated()) printf("count = %d\n", cntDn.read());
    if(cntUp.isUpdated()) printf("count = %d\n", cntUp.read());
    wait_ms(100);
  }
}
