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
    P0 = 0x0,
    P1 = 0x1,
    P2 = 0x2,
    P3 = 0x3,
    P4 = 0x4,
    P5 = 0x5,

    LED1 = P5,
    LED_RED = P4,

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
