#include "mbed.h"

PwmOut rc(D6);
AnalogIn pot(A0);

template<class T>
T map(T x, T i_min, T i_max, T o_min, T o_max){
    return (x-i_min) * (o_max-o_min) / (i_max-i_min)+ o_min;
}

void turn(int angle){
    int duty = map<float>(angle,0,180,600,2400);
    rc.pulsewidth_us(duty);
}

float deadZone(float val, float cent, float eps){
    if (fabs(val-cent)<=eps) return cent;
    return val;
}

DigitalIn sw(USER_BUTTON);

int main() {
    rc.period_ms(10);
    int angle=0;
    int inc=1;
    turn(angle);

    while(1) {
        float v=deadZone(pot.read(),0.5,0.1);
        inc=map<float>(v,0.,1.,-3,3);
        printf("Voltage = %5.2f u16 = %5d\n", pot*3.3, pot.read_u16());
        // int duty=map<float>(pot,0.,1.,600,2400);
        // rc.pulsewidth_us(duty);
        // turn(angle);
        angle+=inc;
        wait_ms(10);
        // if ((angle>=180) || (angle<=0)) inc = -inc; // 양 극단
        if(angle>=180) angle=180;
        if(angle<=0) angle =0;
        turn(angle);
    }
}