#include "mbed.h"

DigitalOut led(D13); // LED2가 D13

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        led = 1;
        ThisThread::sleep_for(2s); // in Mbed OS 6+ wait(), wait_ms()는 사라짐 
        led = 0;
        ThisThread::sleep_for(1s); // wait_us(), wait_ns(), ThisThread::sleep_for()을 사용함. 
    }
}
