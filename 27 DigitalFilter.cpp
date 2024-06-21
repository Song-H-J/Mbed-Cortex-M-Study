#include "mbed.h"
#define PI (4.*atan(1.))
#include "LPfilter.h"
#define dt 0.001f
#define cutoff_f 1.0f
#define freq_s1 0.5f
#define amp_s1 100.0f
#define freq_s2 10.0f
#define amp_s2 10.0f
Serial pc(USBTX,USBRX,115200);
LPFilter<float> lpf(cutoff_f,dt);
float genSignal(uint32_t cnt){
float t= 2*PI*cnt*dt;
float s1= amp_s1*sin(freq_s1*t);
float s2= amp_s2*sin(freq_s2*t);
return s1+s2;
}

int main() {
uint32_t count=0,intval=dt*1000000;
Timer tmr;
tmr.start();
    while(1) {
        if (tmr.read_us()>intval){
            tmr.reset();
            float raw=genSignal(count);
            float filtered=lpf.apply(raw);
            if (count%10==0)
                pc.printf("-110.,%7.3f, %7.3f,110\n", raw,filtered);
            count++;
        }
    }
}