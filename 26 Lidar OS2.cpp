#include "mbed.h"
#include "Lidar.h"
DigitalOut led1(LED1);
Lidar tf(PC_6, PC_7); //TX, RX
Serial pc(USBTX, USBRX, 230400); //high speed

int main() {
    while (true) {
        if (tf.isUpdated()){
            int dist, str, temp;
            tf.getData(dist,str,temp);
            pc.printf("%d, %d, %d\n", dist,str/1000,temp);
        }
    }
}