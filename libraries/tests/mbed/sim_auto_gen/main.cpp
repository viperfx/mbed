#include "test_env.h"
#include "TMP102.h"
#include "PID.h"
#define RATE 0.1
PwmOut co(p3);
TMP102 temp(p28, p27, 0x90);
PID controller(1.0, 0.0, 0.0, RATE);
int main() {
    
    //Temp input from 10 to 50 degrees
    controller.setInputLimits(10, 50);
    //Pwm output from 0.0 to 1.0
    controller.setOutputLimits(0.0, 1.0);
    //If there's a bias.
    //controller.setBias(0.3);
    controller.setMode(AUTO_MODE);
    //We want the process variable to be 1.7V
    controller.setSetPoint(40);
    co.period(0.020);
    while(1) {
        controller.setProcessValue(temp.read());
        
        if (controller.getPV() == 40){
            co = 0.5;
        }else {
        co = controller.compute();
        }
        printf("Temperature read: %f, co %f\n", controller.getPV(), co.read());
        wait(RATE);

    }
}

