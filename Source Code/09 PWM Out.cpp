

#include "mbed.h"

// PwmOut spk(D3);
// PwmOut led(LED1);
// DigitalIn sw(USER_BUTTON);

// int main() {
//     spk.period_us(1000); //  주기
//     led.period_us(1000);
//   while(1) {
//       spk=(!sw)?0.8:1.; // 주파수 셋
//       wait(0.2);

//     //   led=(!sw)?0.4:1.;
//     //   wait(0.2);
//   }
// }

AnalogIn a[6] = {A0, A1, A2, A3, A4, A5};

int main(){
    while(1){
        for(int i =0; i<6; i++){
            printf("%lf\n", a[i]);
            wait(0.5);
        }
        printf("\n");
        wait(2);
    }
}