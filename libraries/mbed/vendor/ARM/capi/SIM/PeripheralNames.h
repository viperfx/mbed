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
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

 typedef enum {
     UART_0 = (int)MCU_UART
 } UARTName;

// typedef enum {
//     ADC0_0 = 0,
//     ADC0_1,
//     ADC0_2,
//     ADC0_3,
//     ADC0_4,
//     ADC0_5,
//     ADC0_6,
//     ADC0_7
// } ADCName;

// typedef enum {
//     DAC_0 = 0
// } DACName;

 typedef enum {
     SPI_0 = (int)MCU_SPI1,
     SPI_1 = (int)MCU_SPI2
 } SPIName;

 typedef enum {
     I2C_0 = (int)MCU_I2C1,
     I2C_1 = (int)MCU_I2C2
 } I2CName;

 typedef enum {
     PWM_1 = (int)MCU_PWM_BASE,
 } PWMName;

// typedef enum {
//      CAN_1 = (int)LPC_CAN1_BASE,
//      CAN_2 = (int)LPC_CAN2_BASE
// } CANName;

 #define STDIO_UART_TX     USBTX
 #define STDIO_UART_RX     USBRX
 #define STDIO_UART        UART_0

#ifdef __cplusplus
}
#endif

#endif
