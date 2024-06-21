#include "mbed.h"
#define M_PI 3.14159265358979323846

Serial pc(SERIAL_TX, SERIAL_RX, 115200);

class Utsensor {
    DigitalOut trigger;
    InterruptIn echo1;   
    InterruptIn echo2;
    float maxRange; // 최대 측정 거리 cm
    float margin1; // 센서 값 보정용 상수 cm
    float margin2;

    Timer timer1;
    Timer timer2;
    Timeout timeout; // for 10us pulse
    Ticker ticker; // to measure every 100ms

    int32_t pulse1_begin;
    int32_t pulse2_begin;
    int32_t pulse1_end;
    int32_t pulse2_end;

    float distance1;
    float distance2;

public:
    Utsensor(PinName trigger_pin, PinName echo1_pin, PinName echo2_pin, float max_range, float marg1, float marg2) : 
        trigger(trigger_pin), echo1(echo1_pin), echo2(echo2_pin), maxRange(max_range), margin1(marg1), margin2(marg2) {
        trigger = 0; distance1 = -1; distance2 = -1;

        echo2.mode(PullDown);

        echo1.rise(callback(this, &Utsensor::echo1_rise)); // rising ISR
        echo1.fall(callback(this, &Utsensor::echo1_fall)); // falling ISR

        echo2.rise(callback(this, &Utsensor::echo2_rise));
        echo2.fall(callback(this, &Utsensor::echo2_fall));
    }

    void start(void) {ticker.attach(callback(this, &Utsensor::periodic_start), 0.1f);}
    void stop(void) {ticker.detach();}

    void periodic_start(void) {trigger = 1; timeout.attach_us(callback(this, &Utsensor::trigger_off), 10);}
    void trigger_off(void) { trigger = 0;}

    void echo1_rise(void) {       
        timer1.reset();
        timer1.start();
        pulse1_begin = timer1.read_us();
    }
    
    void echo2_rise(void) {       
        timer2.reset();
        timer2.start();
        pulse2_begin = timer2.read_us();
    }

    void echo1_fall(void) {
        timer1.stop();
        pulse1_end = timer1.read_us();
        distance1 = pulse1_end - pulse1_begin;
    }

    void echo2_fall(void) {
        timer2.stop();
        pulse2_end = timer2.read_us();
        distance2 = pulse2_end - pulse2_begin;
    }

    // 거리 cm = (초음파 속도 m/s) * (초음파 왕복 시간/1000000 sec) / 2 
    // 거리 cm = 0.017 * (초음파 왕복 시간) ~= (초음파 왕복 시간) / 58.0f
    float read(float &dist1, float &dist2, float &ang){
        dist1 = ((distance1/58.0f)>maxRange) ? maxRange : (distance1/58.0f + margin1);
        dist2 = ((distance2/58.0f)>maxRange) ? maxRange : (distance2/58.0f + margin2);
        // Receiver 간 거리 5.1cm
        ang = (180.0f/M_PI)*(atan2f((dist1-dist2), 5.1f)); // deg
    }
};

Utsensor sonar(D7, D2, D3, 25, -1.3, -0.5);

int main(){
    float d1, d2, ang;
    sonar.start();
    while(1){
        sonar.read(d1, d2, ang);
        pc.printf("d1 = %7.2f , d2 = %7.2f , ang = %7.2f\n", d1,d2,ang);
    }
}