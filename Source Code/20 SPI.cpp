#include "mbed.h"
#define WHO_AM_I 0x75
#define GYRO_HIGH 0x43
#define GYRO_LOW 0x44
#define MASK 0x80 // MASK & WHO_AM_I OR

class IMU{
    SPI spi;
    DigitalOut ss;
  public:
    IMU(PinName mosi, PinName miso, PinName sck, PinName _ss)
     : spi(mosi, miso, sck), ss(_ss)
    {
        ss=1;
        spi.format(8,3);
        spi.frequency(10000000);
    }
    int read(int addr){
        ss=0;
        spi.write(addr|MASK);
        int value = spi.write(0);
        ss=1;
        return value;
    }
};

SPI imu(SPI_MOSI, SPI_MISO, SPI_SCK);
IMU imu_(SPI_MOSI, SPI_MISO, SPI_SCK, D2);
DigitalOut ss(D2);

int main() {
    // ss=1;
    // imu.format(8, 3);
    // imu.frequency(2000000);

    while(1) {
        // ss=0;
        // imu.write(WHO_AM_I|MASK);
        // int value=imu.write(0);
        // printf("DATA: 0x%x\n", value);

        // imu.write(GYRO_HIGH|MASK);
        // int x_h=imu.write(0);

        // imu.write(GYRO_LOW|MASK);
        // int x_l=imu.write(0);

        // printf("GYRO: %d\n", (x_l|x_h<<8));

        // ss=1;
        // wait(0.1);
        printf("DATA: 0x%x \n", imu_.read(WHO_AM_I));
        wait(0.1);
    }
}