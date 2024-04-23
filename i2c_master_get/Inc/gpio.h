/*
 * gpio.h
 *
 *  Created on: Apr 1, 2024
 *      Author: liran
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <stdint.h>
//pb8 i2c_scl AF04
//pb9 i2c_sda AF04

#define RCC 0x40023800
#define GPIO_B 0x40020400
#define RCC_AHB 0x30
#define RCC_APB1 0x40
#define GPIO_ALTFH 0x24
#define GPIO_PULLDOWN 0x0C
#define GPIO_OUTYPE 0x04
void gpio_ini();
#endif /* GPIO_H_ */
