#include "mbed.h"

DigitalOut led1(P2);
Serial ser(USBTX, USBRX);

int main() {
	if (ser.getc() == 0x10) {
 		led1 = 1;
	};
	if (ser.getc() == 0x16) {
		led1 = 0;
	};
	printf("Hello World\n");
	// if (ser.getc() == 0x3) {
    	// led1 = 1;
	// };
	// if (ser.getc() == 0x4) {
		// led1 = 0;
	// };
}
