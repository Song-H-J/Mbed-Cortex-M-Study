#include "mbed.h"

DigitalOut led(LED1);
DigitalIn button(BUTTON1); // 눌리면 0
// main() runs in its own thread in the OS
int main()
{
    while (true) {
        if(!button){
            led = !led;
            wait(0.3); // 스위치 디바운싱을 위함.
        }
    }
}