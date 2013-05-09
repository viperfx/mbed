/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "spi_api.h"

#include <math.h>

#include "cmsis.h"
#include "pinmap.h"
#include "error.h"

//static const PinMap PinMap_SPI_SCLK[] = {
//    {PTE2, SPI_1, 2},
//    {PTC5, SPI_0, 2},
//    {NC  , NC   , 0}
//};
//
//static const PinMap PinMap_SPI_MOSI[] = {
//    {PTE1, SPI_1, 2},
//    {PTC6, SPI_0, 2},
//    {NC  , NC   , 0}
//};
//
//static const PinMap PinMap_SPI_MISO[] = {
//    {PTE3, SPI_1, 2},
//    {PTC7, SPI_0, 2},
//    {NC   , NC   , 0}
//};
//
//static const PinMap PinMap_SPI_SSEL[] = {
//    {PTE4, SPI_1, 2},
//    {PTC4, SPI_0, 2},
//    {NC  , NC   , 0}
//};

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel) {
    // determine the SPI to use
//    SPIName spi_mosi = (SPIName)pinmap_peripheral(mosi, PinMap_SPI_MOSI);
//    SPIName spi_miso = (SPIName)pinmap_peripheral(miso, PinMap_SPI_MISO);
//    SPIName spi_sclk = (SPIName)pinmap_peripheral(sclk, PinMap_SPI_SCLK);
//    SPIName spi_ssel = (SPIName)pinmap_peripheral(ssel, PinMap_SPI_SSEL);
//    SPIName spi_data = (SPIName)pinmap_merge(spi_mosi, spi_miso);
//    SPIName spi_cntl = (SPIName)pinmap_merge(spi_sclk, spi_ssel);

    obj->spi = MCU_SPI1;
//    if ((int)obj->spi == NC) {
//        error("SPI pinout mapping failed");
//    }

    // enable power and clocking
//    switch ((int)obj->spi) {
//        case SPI_0: SIM->SCGC5 |= 1 << 11; SIM->SCGC4 |= 1 << 22; break;
//        case SPI_1: SIM->SCGC5 |= 1 << 13; SIM->SCGC4 |= 1 << 23; break;
//    }

    // set default format and frequency
//    if (ssel == NC) {
//        spi_format(obj, 8, 0, 0);  // 8 bits, mode 0, master
//    } else {
//        spi_format(obj, 8, 0, 1);  // 8 bits, mode 0, slave
//    }
//    spi_frequency(obj, 1000000);
    //obj->spi->PRESCALE = 0x100;

    // enable SPI
//    obj->spi->C1 |= SPI_C1_SPE_MASK;

    // pin out the spi pins
//    pinmap_pinout(mosi, PinMap_SPI_MOSI);
//    pinmap_pinout(miso, PinMap_SPI_MISO);
//    pinmap_pinout(sclk, PinMap_SPI_SCLK);
//    if (ssel != NC) {
//        pinmap_pinout(ssel, PinMap_SPI_SSEL);
//    }
}

void spi_free(spi_t *obj) {
    // [TODO]
}

void spi_format(spi_t *obj, int bits, int mode, int slave) {

}

void spi_frequency(spi_t *obj, int hz) {
    uint32_t error = 0;
    uint32_t p_error = 0xffffffff;
    uint32_t ref = 0;
    uint8_t  spr = 0;
    uint8_t  ref_spr = 0;
    uint8_t  ref_prescaler = 0;

    // bus clk
    uint32_t PCLK = 96000000u;
    uint8_t prescaler = 1;
    uint8_t divisor = 2;

    for (prescaler = 1; prescaler <= 8; prescaler++) {
        divisor = 2;
        for (spr = 0; spr <= 8; spr++) {
            ref = PCLK / (prescaler*divisor);
            error = (ref > hz) ? ref - hz : hz - ref;
            if (error < p_error) {
                ref_spr = spr;
                ref_prescaler = prescaler - 1;
                p_error = error;
            }
            divisor *= 2;
        }
    }

    // set SPPR and SPR
    obj->spi->PRESCALE = ((ref_prescaler & 0x7) << 4) | (ref_spr & 0xf);
}


int spi_master_write(spi_t *obj, int value) {
    // wait tx buffer empty
    while((obj->spi->STATUS & (1 << 0)) == 1);
    obj->spi->VALUE = (value & 0xff);

    // wait rx buffer full
//    while ((obj->spi->STATUS & (1 << 0)) == 1);
    return obj->spi->VALUE & 0xff;
}

int spi_busy(spi_t *obj) {
    return -1;
}
