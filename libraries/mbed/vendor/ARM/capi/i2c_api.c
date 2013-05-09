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
#include "i2c_api.h"

#include "cmsis.h"
#include "pinmap.h"
#include "error.h"
//#if DEVICE_I2C
/** I2C
 * CONTROL - Transaction control register for I2C
 *  [0] - When set to 1, I2C will start transmitting data depending on CONFIG Reigster
 *        When BYS becomes 1, this should be auto reset to 0
 *
 * CONFIG - Configuration register for I2C
 *  [0]STA - I2C Start Condition. When set to 1, the controller will start the transaction with START BIT
 *  [1]STO - I2C Stop Condition. When set to 1, the controller will end the transaction with STOP BIT
 *  [2]ACK - I2C Acknowledge. When TRUE, Controller will send ACK after receiving byte else will send NACK
 *  [3]RW  - I2C Read/Write. When set to 1, the controller will read a byte and send ACK according to [2]. When 0, the controller will send a byte present in data register. The ACK received will go to STATUS[1]
 *
 * STATUS - Status of I2C Master
 *  [0]BSY - When TRUE, I2C is busy in a transaction
 *  [1]RCK - Copy of the recieved ACK after write
 *
 * WRITE DATA - 8 Bit write value to be sent during write operation
 *
 * READ DATA - 8 Bit Read Value after read operation
 *
 * A Write or read when BSY = 1 will give unpredictable result
 */

void i2c_init(i2c_t *obj, PinName sda, PinName scl) {
    obj->i2c = MCU_I2C1;

    // set default frequency at 100k
    //i2c_frequency(obj, 100000);

    // enable I2C interface

}

int i2c_start(i2c_t *obj) {
	obj->i2c->CONFIG |= (1 << 0);
	printf("set start bit %X\n", MCU_I2C1->CONFIG);
    return 0;
}

void i2c_stop(i2c_t *obj) {
    obj->i2c->CONFIG |= (1 << 1);
}

// this function waits the end of a tx transfer and return the status of the transaction:
//    0: OK
//    1: failure
static int i2c_wait_end_tx_transfer(i2c_t *obj) {
    // wait for the end of the tx transfer
//	printf("wait for the end of the tx transfer\n");
    while(obj->i2c->STATUS & (1<<0));
//    printf("end of the tx transfer STATUS is %i\n", obj->i2c->STATUS);
    // check if we received the ACK or NACK
    return obj->i2c->CONFIG & (1<<2) ? 1 : 0;
}

// this function waits the end of a rx transfer and return the status of the transaction:
//    0: OK
//    1: failure
static int i2c_wait_end_rx_transfer(i2c_t *obj) {
    // wait for the end of the rx transfer
//	printf("wait for the end of the rx transfer\n");
    while(obj->i2c->STATUS & (1<<0));
//    printf("end of the rx transfer STATUS is %i\n", obj->i2c->STATUS);
    return 0;
}

static void i2c_send_nack(i2c_t *obj) {
	printf("before nack 0x%X\n", MCU_I2C1->CONFIG);
    obj->i2c->CONFIG &= 0xB; // NACK
    printf("after nack 0x%X\n", MCU_I2C1->CONFIG);
}

static void i2c_send_ack(i2c_t *obj) {
	printf("before ack 0x%X\n", MCU_I2C1->CONFIG);
    obj->i2c->CONFIG |= (1<<2); // ACK
    obj->i2c->CONFIG |= (1<<3);
    printf("after ack 0x%X\n", MCU_I2C1->CONFIG);
}

static int i2c_do_write(i2c_t *obj, int value) {
    // write the data
    obj->i2c->WRITE = value;
    printf("WRITE now %i\n", MCU_I2C1->WRITE);
    obj->i2c->CONTROL |= 0x1;
    // init and wait the end of the transfer
    return i2c_wait_end_tx_transfer(obj);
}

static int i2c_do_read(i2c_t *obj, char * data, int last) {
    if (last)
        i2c_send_nack(obj);
    else
        i2c_send_ack(obj);

    *data = (obj->i2c->VALUE & 0xFF);
    printf("reading value %i\n", obj->i2c->VALUE);
    obj->i2c->CONTROL |= 0x1;
    // start rx transfer and wait the end of the transfer
    return i2c_wait_end_rx_transfer(obj);
}

void i2c_frequency(i2c_t *obj, int hz) {
}

int i2c_read(i2c_t *obj, int address, char *data, int length, int stop) {
    int count;
    char * ptr;
    char dummy_read;
    if (i2c_start(obj)) {
        i2c_stop(obj);
        return 1;
    }
    printf("setting slave addr config is 0x%X\n", MCU_I2C1->CONFIG);
    // write slave addr 7:1 bits
    obj->i2c->CONFIG = 0x9;
    if (i2c_do_write(obj, (address | 0x01))) {
        i2c_stop(obj);
        return 1;
    }
    // set rx mode
    obj->i2c->CONFIG = 0xC;
    // Read in all except last byte
    for (count = 0; count < (length - 1); count++) {
        ptr = &data[count];
        printf("reading byte %i\n", count);
        if (i2c_do_read(obj, ptr, 0)) {
            i2c_stop(obj);
            return 1;
        }
    }

    // read in last byte
    ptr = (count == 0) ? &dummy_read : &data[count - 1];
    if (i2c_do_read(obj, ptr, 1)) {
        i2c_stop(obj);
        return 1;
    }

    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj);
    }

    // last read
    data[count] = obj->i2c->VALUE;

    return 0;
}

int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop) {
    int i;

    if (i2c_start(obj)) {
        i2c_stop(obj);
        return 1;
    }

    if (i2c_do_write(obj, (address & 0xFE) )) {
        i2c_stop(obj);
        return 1;
    }
    // set tx mode
    //obj->i2c->CONFIG = 0x0;
    for (i=0; i<length-1; i++) {
        if(i2c_do_write(obj, data[i])) {
            i2c_stop(obj);
            return 1;
        }
    }

    if (stop) {
        i2c_stop(obj);
    }

    return 0;
}

void i2c_reset(i2c_t *obj) {
    i2c_stop(obj);
}

int i2c_byte_read(i2c_t *obj, int last) {
    char data;
    i2c_do_read(obj, &data, last);
    return data;
}

int i2c_byte_write(i2c_t *obj, int data) {
    return !i2c_do_write(obj, (data & 0xFF));
}
//#endif
