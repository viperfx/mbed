#include "test_env.h"
#include "TMP102.h"
DigitalOut controller(p3);
TMP102 temperature(p28, p27, 0x90);

int main() {
    int target = 30;
    while(1) {
        float t = temperature.read();
        printf("Temperature read: %f\n\r", t);
        if (t > target) {
            controller = 0;
        } else {
            controller = 1;
        }
    }
}
