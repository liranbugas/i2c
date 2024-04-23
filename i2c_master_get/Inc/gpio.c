/*
 * gpio.c
 *
 *  Created on: Apr 1, 2024
 *      Author: liran
 */

#include "gpio.h"
static uint32_t* pRcc_Ahb_En = (uint32_t*)(RCC + RCC_AHB);
static uint32_t* pGpioB_Cr = (uint32_t*)(GPIO_B);
static uint32_t* pRcc_Apb1_En = (uint32_t*)(RCC +RCC_APB1);
static uint32_t* pGpio_B_Altf_H= (uint32_t*)(GPIO_B + GPIO_ALTFH);
static uint32_t* pGpio_B_Outype= (uint32_t*)(GPIO_B + GPIO_OUTYPE);
static uint32_t* pGpio_B_Pull_UpDown= (uint32_t*)(GPIO_B + GPIO_PULLDOWN);
void gpio_ini()
//Initialize the pin b8, b9 gpio a registers
{
	*pRcc_Ahb_En |= (1<<0);
	*pRcc_Apb1_En |=(1<<21);
	*pGpioB_Cr |= (2<<16);
	*pGpioB_Cr |=(2<<18);

	//set pin 8 and 9 as i2c
	*pGpio_B_Altf_H |= (4<<0);
	*pGpio_B_Altf_H |= (4<<4);
	//set pin 8 and 9 in port b as open drain
	*pGpio_B_Outype |= (0x3<<8);
	//set pin 8 and 9 in port b as pull up
	*pGpio_B_Pull_UpDown &= 0;
	*pGpio_B_Pull_UpDown |=(0x1<<16);
	*pGpio_B_Pull_UpDown |=(0x1<<18);
}
