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
#include "serial_api.h"

// math.h required for floating point operations for baud rate calculation
#include <math.h>

#include <string.h>

#include "cmsis.h"
#include "pinmap.h"
#include "error.h"
int stdio_uart_inited = 0;
serial_t stdio_uart;


void serial_init(serial_t *obj, PinName tx, PinName rx) {
	obj->uart = MCU_UART;
	obj->index = 0;
	serial_baud  (obj, 19200);
	stdio_uart_inited = 1;
	memcpy(&stdio_uart, obj, sizeof(serial_t));
}

void serial_free(serial_t *obj) {

}

// serial_baud
//
// set the baud rate, taking in to account the current SystemFrequency
//
// The LPC2300 and LPC1700 have a divider and a fractional divider to control the
// baud rate. The formula is:
//
// Baudrate = (1 / PCLK) * 16 * DL * (1 + DivAddVal / MulVal)
//   where:
//     1 < MulVal <= 15
//     0 <= DivAddVal < 14
//     DivAddVal < MulVal
//
void serial_baud(serial_t *obj, int baudrate) {

}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/
static inline void uart_irq(uint8_t status, uint32_t index) {

}

void uart0_irq() {
}
void uart1_irq() {}
void uart2_irq() {}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {

}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {

}

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/
int serial_getc(serial_t *obj) {
    while (!serial_readable(obj));
    return MCU_UART->VALUE;
}

void serial_putc(serial_t *obj, int c) {
    while (!serial_writable(obj));
    MCU_UART->VALUE = c;
}

int serial_readable(serial_t *obj) {
    // check overrun
    return (MCU_UART->CONTROL & (1 << 0));
}

int serial_writable(serial_t *obj) {
    // check overrun
    return (MCU_UART->CONTROL & (1 << 1));
}

void serial_clear(serial_t *obj) {
}

void serial_pinout_tx(PinName tx) {

}
