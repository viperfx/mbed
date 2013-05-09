#include "mbed.h"

/*
 * This tests the simple functionality of the master transmitter mode.
 * Should be used with py_I2C_TEST.py
 */

int main() {


    // MCU_I2C1->CONFIG = 0x1; // set configuration STA bit to 1
    // MCU_I2C1->WRITE = 0x28 << 1; // write slave address to bits 7:1 (most significant 7 bits)
    // MCU_I2C1->CONTROL = 0x1; //run
    // printf("0x%X\n", MCU_I2C1->STATUS);
    // while (MCU_I2C1->STATUS & 0x1) {}; // wait until idle
    
    // MCU_I2C1->WRITE = 0x4; 
    // MCU_I2C1->CONTROL = 0x1;
    
    // while (MCU_I2C1->STATUS & 0x1) {}; // wait until idle
    
    // MCU_I2C1->CONFIG = 0x6; 
    // MCU_I2C1->CONTROL = 0x1;
    
    // while (true) {};
    MCU_I2C1->CONFIG = 0x1; // set configuration STA bit to 1
    MCU_I2C1->WRITE = 0x28 << 1; // write slave address to bits 7:1 (most significant 7 bits)
    MCU_I2C1->CONTROL = 0x1; //run
    
    while (MCU_I2C1->STATUS & 0x1) {
    }; // wait until idle
    
    MCU_I2C1->WRITE = 0x4; 
    MCU_I2C1->CONTROL = 0x1;
    
    while (MCU_I2C1->STATUS & 0x1) {}; // wait until idle
    
    MCU_I2C1->CONFIG = 0x6; 
    MCU_I2C1->CONTROL = 0x1;
    
    while (true) {};

}
