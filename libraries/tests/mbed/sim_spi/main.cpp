#include "mbed.h"
Serial pc(USBTX, USBRX);
SPI spi(p1,p2,p3);
int main() {

	// int spi.write(0x6);

	int readit = spi.write(0x06);
    printf("readit = 0x%X\n", readit);
    // for (unsigned long long i = 0; i < 184460000U; i++) { };
    // MCU_SPI1->VALUE;
    // MCU_SPI1->VALUE = 0x8;
    // MCU_SPI1->VALUE = 0x6;
    while (true) {};

}
