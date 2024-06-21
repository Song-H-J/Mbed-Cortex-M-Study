
#include "mbed.h"

CircularBuffer<char, 10> buff;
RawSerial pc(USBTX, USBRX, 9600);
Ticker tic;
void ticman(){
    if(!buff.full()){
        buff.push('!');
    }
}

void pcman(){
    if(pc.readable()){
        char c2 = pc.getc();
        if(!buff.full()){
          buff.push(c2);
        }
    }
}

int main() {
    tic.attach(&ticman, 0.2f);
    pc.attach(&pcman);
  while(1) {
      if(!buff.empty()){
          char c;
          buff.pop(c);
          pc.printf("%c\n", c);
      }
  }
}
