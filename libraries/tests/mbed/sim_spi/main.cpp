#include "mbed.h"
SPI spi(p1,p2,p3);
int main() {
	// while(MCU_SPI1->STATUS & (1 << 0));
    // MCU_SPI1->VALUE = (0x8F & 0xff);

    // wait rx buffer full
    // while (MCU_SPI1->STATUS & (1 << 0));
   	// char readit = MCU_SPI1->VALUE & 0xff;

    // for (unsigned long long i = 0; i < 184460000U; i++) { };
    // MCU_SPI1->VALUE;
    // MCU_SPI1->VALUE = 0x8;
    // MCU_SPI1->VALUE = 0x6;
    while (true) {
            spi.write(0x00);
            // int readit = spi.write(0x00);
    };

}
