#include "mbed.h"

Serial pc(SERIAL_TX, SERIAL_RX, 115200);

class Sonar{
    Timer tmr;
    Ticker tic;

    DigitalOut trig, led;
    InterruptIn echo;

    int32_t start, stop;
    float distance;
    bool updated;

  public:
    Sonar(PinName _trig, PinName _echo) : trig(_trig), echo(_echo),led(D13){
        trig=0;
        updated = false;

        echo.rise(callback(this, &Sonar::echo_up));
        echo.fall(callback(this, &Sonar::echo_dn));
    }

    void starting(){tic.attach(callback(this, &Sonar::trigger),0.1f);}
    void trigger(){ trig = 1; wait_us(10); trig = 0; }
    void echo_up(){
        tmr.reset();
        tmr.start();
        start = tmr.read_us();
    }
    void echo_dn(){
        tmr.stop();
        stop = tmr.read_us();
        distance = (stop-start)/58.0f;
        updated = true;
        led=!led;
    }

    bool isUpdated(){ return updated; }
    float read(){ updated = false; return distance; }
};



int main() {
    Sonar sonar(D7, D2);
    sonar.starting();
    printf("Program Started!\n");
  while(1) {
      if(sonar.isUpdated()){
          pc.printf("%f\n", sonar.read());
      }
  }
}
