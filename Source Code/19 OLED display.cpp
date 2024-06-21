#include "mbed.h"
#include "Adafruit_SSD1306.h"   
                       
I2C i2c(I2C_SDA, I2C_SCL); // SDA, SCL
Adafruit_SSD1306_I2c myOled(i2c,D4,0x78,64,128);
int main(){
    uint16_t q=0;
    i2c.frequency(400000);
    myOled.begin();
    myOled.setTextSize(2);
    myOled.printf("%ux%u \nHellow World\r\n", myOled.width(), myOled.height());
    //myOled.printf("First sample\r\n");
    myOled.setTextSize(1);
    myOled.display();
    while(1) {
        myOled.printf("%u\r",q++);
        myOled.display();
        printf("q = %u \n",q); wait(1.0);
    }
}
