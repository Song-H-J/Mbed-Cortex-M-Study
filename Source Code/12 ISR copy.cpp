#include "mbed.h"

class UDcounter{
    InterruptIn upSw;
    InterruptIn dnSw;
    volatile uint16_t count;
    volatile bool updated;

    public:
    UDcounter(PinName _pinUp, PinName _pinDn) :upSw(_pinUp), dnSw(_pinDn), count(0), updated(false)  {
        upSw.mode(PullUp);
        dnSw.mode(PullUp);
        upSw.fall(callback(this, &UDcounter::countUp));
        dnSw.fall(callback(this, &UDcounter::countDn));
    }// _ = temporary use, init

    void countUp(){count++; updated=true;}
    void countDn(){count--; updated=true;}
    int16_t read(){updated=false; return count;}
    bool isUpdated(){return updated;}
    
};

UDcounter cnt(USER_BUTTON , D2);
int main() {
  while(1) {
    if(cnt.isUpdated()) printf("count=%d\n", cnt.read());
    wait_ms(100);
  }
}
