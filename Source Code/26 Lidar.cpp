#include "Lidar.h"

extern DigitalOut led1;
Lidar::Lidar(PinName serialTX, PinName serialRX) :
    Serial(serialTX, serialRX, DEFAULT_BAUD), // Father Class, make Serial object
    distance(0), index(0), checkSum(0) {
        data = new uint8_t[6]; //create array
        Serial::attach(callback(this, &Lidar::recieveData)); // default RxIrq
        decodeTicker.attach_us(callback(this, &Lidar::decode), SENSOR_FREQ/20);
        state=HEADER1; // data decode step, enum
        updated=false;
}

void Lidar::recieveData() { //whenever data arrived
    if (readable()){
        uint8_t b=getc();
        if (!buff.full()) buff.push(b); // to the circular buffer
    }
}

void Lidar::decode() {
    uint8_t b;
    if (!buff.empty()){
        buff.pop(b);

        switch (state){
            case HEADER1: // check 1st header
                if (b==HEADER_FIRST_BYTE) state=HEADER2;
                break;
            case HEADER2: // check 2nd header
                if (b==HEADER_SECOND_BYTE) { // header double check
                state=DATA; index=0;
                checkSum = HEADER_FIRST_BYTE + HEADER_SECOND_BYTE;
                }else state=HEADER1; // if fail, back to 1st header
                break;
            case DATA: // check data size
                data[index++]=b; checkSum += b; // data & checksum
                if (index==6) state=BCC; // distance 2byte, signal strength 2bytes, temperature 2bytes
                break;
            case BCC: // check BCC
                // compare Lidar's checksum with checksum calculated by MCU
                if (b==checkSum){ // if checksum is ok
                    distance = ((data[1]<<8)|data[0]); //make 16bit
                    strength = ((data[3]<<8)|data[2]);
                    temperature= ((data[5]<<8)|data[4]);
                    temperature= ( temperature/8) -256; // refer datasheet
                    updated=true;
                    led1=!led1;
                }
                state=HEADER1; // back to starting state
        }
    }
}

void Lidar:: getData(int& dist, int & str, int & temp)
    {dist=distance;str=strength; temp=temperature; updated=false;}

int Lidar::getDistance() { return distance;}
int Lidar::getStrength(){ return strength;}
bool Lidar::isUpdated(){ return updated;}