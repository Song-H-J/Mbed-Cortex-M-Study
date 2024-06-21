#include "mbed.h"

I2C dev(I2C_SDA, I2C_SCL);

int main() {
    uint16_t adr = 0;
    while(1) {
        int cnt =0;
        for (adr=0; adr<256; adr++){
            if(dev.read(adr,0,0)==0){
                printf("===========found at: %d, %x ===========\n",adr,adr);
                cnt++;
            }

            else{
                printf("not found at: %d\n",adr);
            }

        }
        
        printf("Total %d device found\n", cnt);
        break;
    }
}
