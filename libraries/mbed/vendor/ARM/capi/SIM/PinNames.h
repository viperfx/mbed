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
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PORT_SHIFT  5

typedef enum {
    // LPC Pin Names
    p0 = 0x0,
    p1 = 0x1,
    p2 = 0x2,
    p3 = 0x3,
    p4 = 0x4,
    p5 = 0x5,
    p6 = 0x6,
    p7 = 0x7,
    p8 = 0x8,
    p27=0x27,
    p28=0x28,
    p29=0x29,
    USBTX = p0,
    USBRX = p1,
    STDIO_UART_TX = USBTX,
    STDIO_UART_RX = USBRX,

    LED1 = p5,
    LED4 = p3,
    LED_RED = p4,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
    PullUp = 0,
    PullDown = 3,
    PullNone = 2,
    OpenDrain = 4
} PinMode;

// version of PINCON_TypeDef using register arrays
// typedef struct {
//   __IO uint32_t PINSEL[11];
//        uint32_t RESERVED0[5];
//   __IO uint32_t PINMODE[10];
//   __IO uint32_t PINMODE_OD[5];
// } PINCONARRAY_TypeDef;

// #define PINCONARRAY ((PINCONARRAY_TypeDef *)LPC_PINCON_BASE)

#ifdef __cplusplus
}
#endif

#endif
