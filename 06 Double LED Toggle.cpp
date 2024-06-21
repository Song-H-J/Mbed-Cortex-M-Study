#include "mbed.h"
DigitalOut led1(LED1);
DigitalOut led2(D2);
DigitalIn but(D3,PullUp);
int main(){
	while(1){
		if(!but){
			led1 = !led1;
			led2 = !led1;
			wait(0.3);
		}
	}
}
