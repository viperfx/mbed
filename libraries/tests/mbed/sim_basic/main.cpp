#include "mbed.h"

DigitalOut led1(P0);

DigitalOut led3(P3);
DigitalOut led2(P1);
// #define GPIO_1_MASK    0x1
// #define GPIO_2_MASK    0x2

int main() {
	/**** LED SEQ ***********/
	// Turn on and off led at pin 1 and 2
	
	// MCU_GPIO->DIR = 0x0;
	// MCU_GPIO->VAL = 0xF;
	// MCU_GPIO->VAL = 0x0;
	


	/****** LED SEQ SDK **********/
	
	led1 = 1;
	led1 = 0;
	led2 = 1;
	led2 = 0;
	

    /************ Repeater ***********/
    // Set all pins as input, apart GPIO 2
    // MCU_GPIO->DIR = GPIO_2_MASK;
    
    // Read the initial value of GPIO 1
    // int last_gpio_1 = (MCU_GPIO->VAL & GPIO_1_MASK);
    // Each time the value of GPIO 1 change, mirror it on GPIO2
    // while(true) {
        // int current_gpio_1 = (MCU_GPIO->VAL & GPIO_1_MASK);
        // if (current_gpio_1 != last_gpio_1) {
            // MCU_GPIO->VAL = (current_gpio_1) ? GPIO_2_MASK : (0);
            // last_gpio_1 = current_gpio_1;
        // }

        
    // }
}

