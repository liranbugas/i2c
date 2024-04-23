/*
 * i2c.h
 *
 *  Created on: Apr 1, 2024
 *      Author: liran
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C 0x40005400
#define I2C_CR2 0x04
#define I2C_DR 0x10
#define I2C_SR1 0x14
#define I2C_CCR 0x1C
#define I2C_OAR1 0x08
#include <stdint.h>

void i2c_ini();
void i2c_start();
uint8_t i2c_recieve();
void i2c_stop();
#endif /* I2C_H_ */
