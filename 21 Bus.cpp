#include "mbed.h"
#define red 6
#define blue 9
#define green 5
#define white 8
#define black 7

int scenario[8]={red, white, blue, white, green, white, black, white};
// BusIn bus(D2,D3,D4,D5,D6,D7,D8,D9);
BusOut buso(D4,D5,D6);

int main() {
    while(1) {
        for(int i =0; i<8; i++){
            // printf("%c ", (bus[i])?'X':'O');
            // buso=i;
            buso = scenario[i];
            wait(1);
        }
        // printf("\n");
        // printf("%d\n",bus.read());
        // wait(0.2);
    }
}