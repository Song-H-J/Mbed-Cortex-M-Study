#include "mbed.h"

DigitalIn button(BUTTON1);
DigitalOut led(LED1);

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        led = !button;
    }
}
