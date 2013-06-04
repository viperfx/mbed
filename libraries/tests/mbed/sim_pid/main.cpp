#include "test_env.h"
#include "TMP102.h"
#include "PID.h"
#define RATE 0.1
PwmOut co(p3);
TMP102 temp(p28, p27, 0x90);
PID controller(1.0, 0.0, 0.0, RATE);
// PID lib adapted from https://github.com/br3ttb/Arduino-PID-Library/
// unsigned long lastTime;
// float Input, Setpoint, Output, OutputScale, OutMin, OutMax, OutSpan;
// float errSum, lastErr, lastInput;
// float kp, ki, kd;

// float Compute() 
// {
//     // dT - How long since we last Compute()
//     unsigned long now = t.read_ms();
//     float dT = (float)(now - lastTime);
//     // Compute all the working error variables
//     float error = Setpoint - Input; // e(t)
//     errSum += (error * ki); // sum e(t)
//     if (errSum > OutMax) errSum = OutMax;
//     else if(errSum < OutMin) errSum = OutMin;
//     float dErr = (Input - lastInput); // d e(t) 
//     //printf("%f, %f, %f, %f, %f\n", kp, error, errSum, kd, dErr);
//     // Compute output
//     Output = kp * error + errSum - kd * dErr;
//     float tmpOut = Output;
    
//     if(Output > OutMax) Output = OutMax;
//     else if(Output < OutMin) Output = OutMin;
//     printf("%f, %f, %f, %d\n", Output, tmpOut, Input, now);
//     // Assign last* vars
//     lastInput = Input;
//     lastErr = error;
//     lastTime = now;
    
//     return Output;
// }
// void setTunings (float Kp, float Ki, float Kd)
// {
//     kp = Kp;
//     ki = Ki;
//     kd = Kd;
// }
// void setOutputLimits(float outMin, float outMax)
// {
//     OutMin = outMin;
//     OutMax = outMax;
//     OutSpan = OutMax - OutMin;
// }
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
        co = controller.compute();
        printf("Temperature read: %f, co %f\n", controller.getPV(), co.read());
        wait(RATE);

    }
}
