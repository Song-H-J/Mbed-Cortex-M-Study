#include "mbed.h"

Serial pc(USBTX, USBRX,9600);
InterruptIn but(USER_BUTTON);
DigitalOut led(LED1);

// void response(){
//     if(pc.readable())
//         pc.putc(pc.getc());
// }

void response(){
    if(pc.readable())
        led = (pc.getc()=="1")?1:0;
}

void send(){
    pc.putc('b');
    pc.putc('\n');
}

//////////////////////////////////
char buffer[200]={0};
float data[4]={0};
uint16_t b_cnt=0, d_cnt;
bool f_complete = false;

void onRX(){
    if(pc.readable()){
        char c=pc.getc();
        if(c==','){
            buffer[b_cnt]='\0';
            data[d_cnt]=atof(buffer);
            d_cnt++;
            b_cnt=0;
        }
        else if (c=='\n'){
            buffer[b_cnt]='\0';
            data[d_cnt]=atof(buffer);
            d_cnt=0;
            b_cnt=0;
            f_complete=true;
        }
        else{
            buffer[b_cnt]=c; b_cnt++;
        }
    }
}

void onRX2(){
    if(pc.readable()){
        char c=pc.getc();
        if (c=='\n'){
            buffer[b_cnt]='\0'; // string으로 간주하기 위해 추가
            sscanf(buffer,"%f,%f,%f",data,data+1,data+2);
            b_cnt=0;
            f_complete=true;
        }
        else{
            buffer[b_cnt]=c; b_cnt++;
        }
    }  
}


int main() {
    // pc.attach(&response, SerialBase::RxIrq);
    // but.fall(&send);

    pc.attach(&onRX, SerialBase::RxIrq);
    // pc.attach(&onRX2, SerialBase::RxIrq);

    while(1) {
        // if(pc.readable()){
        //     if(pc.writeable())
        //         pc.putc(pc.getc());
        // }
        // led=!led;
        // wait_ms(1000); // buffer overwrite

        // led=!led;
        // wait_ms(1000); // callback

        if(f_complete){
            pc.printf("Data = %f, %f, %f \n", data[0], data[1], data[2]);
            f_complete=false;
        }
    }
}
