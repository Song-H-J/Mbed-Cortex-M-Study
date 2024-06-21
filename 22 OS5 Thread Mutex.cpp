#include "mbed.h"

Thread t,q;
Mutex mu;

int cnt = 0;

DigitalOut led1(LED1), led2(D2);

void blink(DigitalOut *led){
    while(1){
        *led = !*led;
        wait_us(20000);
    }
}

void plus_(){
    while(1){
        mu.lock();
        cnt++;
        printf("plus = %d\n", cnt);
        mu.unlock();
        wait_us(200000);
    }
}

void minus_(){
    while(1){
        mu.lock();
        cnt--;
        printf("minus = %d\n", cnt);
        mu.unlock();
        wait_us(1000000);
    }
} 

typedef struct {float pos, vel; uint32_t cnt;} msg_t;
MemoryPool<msg_t,16>mpool;
Queue<msg_t, 16> que;

void generator(){
    int count = 0;
    while(1){
        msg_t* msg = mpool.alloc();

        msg->pos = count*1.45;
        msg->vel = count*2.27;
        msg->cnt = count;
        count++;

        que.put(msg);
        wait_us(1000000);
    }
}

int main()
{
    q.start(&generator);
    while(1){
        osEvent evt = que.get();
        if(evt.status == osEventMessage){
            msg_t* msg =(msg_t*) evt.value.p;
            printf("===== %d\n", msg->cnt);
            printf("pos = %f\n", msg->pos);
            printf("vel = %f\n\n", msg->vel);
            mpool.free(msg);
        }
        wait_us(200000);
    }    

    // t.start(&plus_);
    // q.start(&plus_);
    // minus_();

    // t.start(callback(&blink, &led1));
    // q.start(callback(&blink, &led2));


    // led2 = 1;
    // t.start(callback(&blink, &led1));

    // wait_us(5000000);
    // t.terminate();
    // led2 = 0;

    // while (true) {
    //     led2 = !led2;
    //     wait_us(500000);
    // }
}
