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
#include "pwmout_api.h"

#include "cmsis.h"
#include "pinmap.h"
#include "error.h"

#define PWM_CLOCK_MHZ       (100) // (48)MHz / 64 = (0.75)MHz

void pwmout_init(pwmout_t* obj, PinName pin) {
    // default to 20ms: standard for servos, and fine for e.g. brightness control
	obj->pwm = MCU_PWM;
    pwmout_period_ms(obj, 20);
    pwmout_write    (obj, 0);

}

void pwmout_free(pwmout_t* obj) {}

void pwmout_write(pwmout_t* obj, float value) {
    if (value < 0.0) {
        value = 0.0;
    } else if (value > 1.0) {
        value = 1.0;
    }

    obj->pwm->PULSEWIDTH = (uint32_t)((float)(obj->pwm->PERIOD) * value);
    obj->pwm->COUNTER = 0;
    obj->pwm->CONTROL = 1;

}

float pwmout_read(pwmout_t* obj) {
    float v = (float)(obj->pwm->PULSEWIDTH) / (float)(obj->pwm->PERIOD);
    return (v > 1.0) ? (1.0) : (v);
}

void pwmout_period(pwmout_t* obj, float seconds) {
    pwmout_period_us(obj, seconds * 1000000.0f);
}

void pwmout_period_ms(pwmout_t* obj, int ms) {
    pwmout_period_us(obj, ms * 1000);
}

// Set the PWM period, keeping the duty cycle the same.
void pwmout_period_us(pwmout_t* obj, int us) {
    float dc = pwmout_read(obj);
    obj->pwm->PERIOD = PWM_CLOCK_MHZ * us;
    pwmout_write(obj, dc);
}

void pwmout_pulsewidth(pwmout_t* obj, float seconds) {
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t* obj, int ms) {
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t* obj, int us) {
    obj->pwm->PULSEWIDTH = PWM_CLOCK_MHZ * us;
}
