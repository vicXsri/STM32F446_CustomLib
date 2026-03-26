/*
 * gpio.c
 *
 *  Created on: May 30, 2025
 *      Author: Vichu
 */


#include "gpio.h"

void GPIO_Init(GPIO_Typedef* GPIOx, GPIO_InitTypeDef* GPIO_Init){
		/* Set the Mode of the GPIO Pin*/
	GPIOx->MODER  &=  ~(0x3U << (GPIO_Init->Pin * 2));  // 00 -> i/p CLEAR
	GPIOx->MODER  |=   (GPIO_Init->Mode << (GPIO_Init->Pin * 2));  // 00 -> i/p

		/* in case of alternate or output mode*/
	if((GPIO_Init->Mode == GPIO_OUTPUT) || (GPIO_Init->Mode == GPIO_ANALOG)){
		/*Set the speed of the gpio pin*/
		GPIOx->OSPEEDR &= ~(0x3U << (GPIO_Init->Pin * 2)); // clear the bits
		GPIOx->OSPEEDR |=  (GPIO_Init->Speed << (GPIO_Init->Pin * 2)); // set the bits

			/*configure the output mode of gpio pin*/
		(GPIO_Init->OType)?
		(GPIOx->OTYPER |= (0x1U << GPIO_Init->Pin)): // SET
		(GPIOx->OTYPER &= ~(0x1U << GPIO_Init->Pin)); // CLEAR
	}

		/* Except for analog mode, set the pull up/down setup */
	if((GPIO_Init->Mode) != GPIO_ANALOG){
		GPIOx->PUPDR &= ~(0x3U << (GPIO_Init->Pin * 2)); // clear the bits
		GPIOx->PUPDR |=  (GPIO_Init->Pull << (GPIO_Init->Pin * 2)); // set the bits
	}

		/* Set the AFR Register */
	if((GPIO_Init->Mode) == GPIO_ALTERNATE){
		if(GPIO_Init->Pin <= 7){
			GPIOx->AFR[0] &= ~(0xFU <<  (GPIO_Init->Pin * 4)); // clear
			GPIOx->AFR[0] |=  (GPIO_Init->Alternate  <<  (GPIO_Init->Pin * 4)); // set
		}
		else{
			GPIOx->AFR[1] &= ~(0xFU <<  ((GPIO_Init->Pin - 8) * 4)); //clear
			GPIOx->AFR[1] |=  (GPIO_Init->Alternate  <<  ((GPIO_Init->Pin - 8) * 4)); //set
		}
	}
}

void GPIO_DeInit(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN){
	/*Deactivate the Mode Register*/
	GPIOx->MODER  &= ~ (0x3U << (GPIO_PIN * 2));

	/*Deactivate the AFR Register*/
	if(GPIO_PIN <= 7)
	GPIOx->AFR[0] &= ~(0xFU <<  (GPIO_PIN * 4));
	else
	GPIOx->AFR[1] &= ~(0xFU <<  ((GPIO_PIN - 8) * 4));

	/*Deactivate the PULL Register*/
	GPIOx->PUPDR &= ~(0x3U << (GPIO_PIN * 2));

	/*Deactivate the Output mode Register*/
	GPIOx->OTYPER &= ~(0x1U << GPIO_PIN);

	/*Deactivate the Output mode Register*/
	GPIOx->OSPEEDR &= ~(0x3U << (GPIO_PIN * 2)); // clear the bits

}

void GPIO_WritePin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN, uint8_t state){
	(state == 1)?
			/**/
			(GPIOx->ODR |=  (1U << GPIO_PIN)):
			(GPIOx->ODR &= ~(1U << GPIO_PIN));
}

void GPIO_TogglePin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN){
	GPIOx->ODR ^= (1U << GPIO_PIN);
}

bool GPIO_ReadPin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN){
	return	GPIOx->IDR & (1U << GPIO_PIN);
}

bool GPIO_LockPin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN){
	/*We should follow the Lock Key write sequence*/
	/*Sequence Start*/
	/*WR LCKR[16] = ‘1’ + LCKR[15:0]*/
	GPIOx->LCKR = (1U << GPIO_PIN) | (1U << 16);
	/*WR LCKR[16] = ‘0’ + LCKR[15:0]*/
	GPIOx->LCKR = (1U << GPIO_PIN) | (0U << 16);
	/*WR LCKR[16] = ‘1’ + LCKR[15:0]*/
	GPIOx->LCKR = (1U << GPIO_PIN) | (1U << 16);
	/*RD LCKR*/
	(void)GPIOx->LCKR;
	/*Sequence End*/

	return ( GPIOx->LCKR & (1U << 16));
}
