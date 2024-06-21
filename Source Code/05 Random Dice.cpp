#include "mbed.h"

DigitalIn button(BUTTON1);
// main() runs in its own thread in the OS
int main()
{
    srand(time(NULL));
    while (true) {
        if(!button){
            // printf("%d\n", rand());
            printf("%u \n", rand()%6 + 1); // %u is unsigned int decimal
            wait(0.2);
        }
    }
}
