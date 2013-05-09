#include "mbed.h"
DigitalOut led1(P0);
DigitalIn led3(P3);
DigitalOut led2(P1);
Serial pc(USBTX, USBRX);
int main() {
    led1 = 1;
    led1 = 0;
    int i = 0;
    while(true){
        led2 = !led2;
        pc.printf("var i is %d\n", i);
        wait(0.1);
    }
}
