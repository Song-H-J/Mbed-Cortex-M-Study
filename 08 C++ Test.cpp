#include "mbed.h"
#define pi (4.*atan(1.))

// void circle(float r, float& area, float& peri){
//     // return을 참조자를 사용하여 수행
//     // 포인터를 쓰지 않고도 원본 변수의 값을 편집 가능
//     area = r*r*pi;
//     peri = 2*pi*r;
// }

class Number{
    int v; // 멤버 변수
    
    public: // 접근 가능
        Number(int value): v(value){ // 생성자 & 멤버 초기화 목록
        }

        Number& operator = (int value){
            // = overiding으로 객체 우변에 int 값이 오는 경우
            v=value;
            return *this; // <- 클래스에서 자기 자신을 반환할 때
        }

        operator int(){ // int 형변환 연산자 overriding
            return v;
        }

        int operator + (Number x){ // + overriding의 우변이 객체일때
            return v+x.v;
        }

};

class Complex{
    float r,i;

    public:
    Complex(float real=0, float img=0): r(real), i(img){
    }

    Complex& operator = (Complex c){
        r = c.r;
        i = c.i;
        return *this;
    }

    Complex operator + (Complex d){
        Complex c(r+d.r,i+d.i);
        return c;
    }

    Complex operator - (Complex d){
        Complex c(r-d.r,i-d.i);
        return c;
    }

    Complex operator * (Complex d){
        Complex c((r*d.r-i*d.i),(r*d.i+i*d.r));
        return c;
    }

    void print(){
        printf("%.2f, %.2f\n", r, i);
    }
};

enum MODE {ONOFF, TOGGLE};

class CombinePeri{
    DigitalOut led;
    DigitalIn sw;
    MODE mode;

    public:
    CombinePeri(MODE m = ONOFF,PinName ln=LED1, PinName sn=USER_BUTTON): mode(m), led(ln), sw(sn){
        led = 0;
    }

    void update(){
        if(mode==TOGGLE){
            if(!sw){
                led = !led;
                wait(0.3);
            }
        }
        
        else{
            led = !sw;
        }
    }
};


int main() {
    // float radius= 10, a, p; // 원본 변수
    // Number n(20), m(50);
    // Complex a(1,2), b(4, 3), c;
    // CombinePeri peri(TOGGLE);
    CombinePeri peri;
    while(1) {
        // circle(radius,a,p);
        // printf("area=%.2f, perimater=%.2f\n",a,p);
        // wait(1.0);

        // n=100;
        // printf("n=%d\n", (int)n); 
        // wait(1.0);

        // printf("n+m=%d\n", n+m);
        // wait(1.0);

        // Number z = n+m;
        // // n+m은 + 연산자 overriding으로 int 형으로 반환,
        // // z는 = 연산자 overriding으로 멤버 변수 값 수정 후 자기 자신 반환
        // printf("z=%d\n", (int)z);
        // wait(1.0);

        // a.print();
        // b.print();
        // c = (a+b)*(a-b);
        // c.print();
        // wait(1.0);

        peri.update();
        // wait(0.2);
    }
}