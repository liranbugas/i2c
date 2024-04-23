/*
 * i2c.c
 *
 *  Created on: Apr 1, 2024
 *      Author: liran
 */
//Standard speed 100KHZ
//use pin scl for clock and sda for data
//use start and stop condition using software
//data from master to start is 1bit to start and then 7 bit address
//data starts with msb and ends with acknoledgment bit
//use registers ccr, cr1, cr2,sr1,sr2

//I2C_CR2  for Program the peripheral input clock
//Configure the clock control registers
// Configure the rise time register in i2c_TRISE
// Program the I2C_CR1 register to enable the peripheral
// Set the START bit in the I2C_CR1 register to generate a Start condition
//2 MHz in Sm mode at least
//The CCR bits are used to generate the high and low level of the SCL clock

//after start bit set the master wait for interupt in ITEVFEN and
//Then the master waits for a read of the SR1 register followed by a write in the DR register
//with the Slave address

//figure 	165 s,sb,addr,a,sr1,sr2,p,dr
#include "i2c.h"

static uint32_t* I2c_Cr1 = (uint32_t*)(I2C);//start , stop, Acknowledge bits
static uint32_t* I2c_Cr2 = (uint32_t*)(I2C+ I2C_CR2);//ITEVTEN,FREQ bits
static uint32_t* I2c_Dr = (uint32_t*)(I2C+ I2C_DR);//data gets
static uint32_t* I2c_Sr1 = (uint32_t*)(I2C+ I2C_SR1);//addr,rxne for read mode, sb for start master,
static uint32_t* I2c_Ccr = (uint32_t*)(I2C+ I2C_CCR);//for clock time high and low
static uint32_t* I2c_Oar_1 = (uint32_t*)(I2C+ I2C_OAR1);

void i2c_ini()
//initialize i2c registers
{
	*I2c_Cr2 |= (0x000010);
	*I2c_Cr2 |=(1<<9);
	*I2c_Cr2 |=(1<<10);//generates
	*I2c_Oar_1 |=(1<<0);//for address of slave
}
void i2c_start()
//start send address as master in i2c
{
	*I2c_Cr1 |=(1<<8);
	while(1)
	{
		uint32_t temp = (*I2c_Sr1)&(0x1);
		if(temp)
		{
			break;
		}
	}
	//sends slave address + read / write bit=0
	*I2c_Dr |= 0x11;





}
uint8_t i2c_recieve()
//Receive data in i2c
{
	uint8_t num = 0;
	//check if slave got the address
	while(!(*I2c_Sr1)&(0x10)){}
	*I2c_Cr1 &=~(1<<10);
	*I2c_Sr1 &=~(1<<1);
	//wait rxne =1
	while(1)
	{
		uint32_t temp = (*I2c_Sr1)&(1<<6);
		if(temp)
		{
			num |= (*I2c_Dr)&(0xFF);
			return num;
		}
	}
}
void i2c_stop()
//stops i2c
{
	//nack
	*I2c_Cr1 &=~(1<<10);
	//stop
	*I2c_Cr1 |=(1<<9);
	//addr =0
	*I2c_Sr1 &=~(1<<1);

}
