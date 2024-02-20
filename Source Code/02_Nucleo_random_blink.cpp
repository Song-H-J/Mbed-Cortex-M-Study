#include "mbed.h"
#include <cstdlib>

DigitalOut led(LED1);

// main() runs in its own thread in the OS
int main()
{
    srand(time(NULL)); // time 함수로 얻은 현재 시간을 srand의 seed로 사용해 난수 발생기를 초기화
    while (true) {
        float v = (float)rand()/RAND_MAX; // RAND_MAX로 float형 rand()를 나누면 0.0~1.0 사이의 균등분포 난수를 얻는다.
        led = (v<0.1f) ? 1:0 ; // 0.0 ~ 1.0의 균등분포에서 0.0 ~ 0.1 사이의 값이 나올 확률은 10%
        wait(0.01); // 10ms 주기로 10% 확률로 LED가 켜진다.
    }
}
