#include "mbed.h"
#include "Qencoder.h"
DigitalOut led1(LED1);
QEncoder enco(D2,D3);
int main() {
    enco.init();
    enco.setCount(0);
    while(1) {
        printf("count= %d , %d\n", enco.getCount(),
        enco.getErrorCount());
        wait(0.01);
    }
}