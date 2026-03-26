/*
 * gpio.h
 *
 *  Created on: May 30, 2025
 *      Author: Vichu
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "main.h"

typedef struct{
	__IO uint32_t MODER; // GPIO port mode register
	__IO uint32_t OTYPER; // GPIO port output type register
	__IO uint32_t OSPEEDR; // GPIO port output speed register
	__IO uint32_t PUPDR; // GPIO port pull-up/pull-down register
	__IO uint32_t IDR; // GPIO port input data register
	__IO uint32_t ODR; // GPIO port output data register
	__IO uint32_t BSRR; // GPIO port bit set/reset register
	__IO uint32_t LCKR; // GPIO port configuration lock register
	__IO uint32_t AFR[2]; // GPIO alternate function low -> AFRLP[0] high -> AFRLP[1]
}GPIO_Typedef;

typedef struct{
	uint32_t Pin; // Specify the gpio pin
	uint32_t Mode; // Specify the Mode
	uint32_t Pull; //specifies pull up or down
	uint32_t Speed; // speicifes the speed of the pin
	uint32_t Alternate; // specifies the pin is alternate functin
	uint32_t OType; // specifies the pin with pp / od config
}GPIO_InitTypeDef;

#define GPIOA_BASE		(AHB1_BASE + 0x0000UL)
#define GPIOB_BASE		(AHB1_BASE + 0x0400UL)
#define GPIOC_BASE		(AHB1_BASE + 0x0800UL)
#define GPIOD_BASE		(AHB1_BASE + 0x0C00UL)
#define GPIOE_BASE		(AHB1_BASE + 0x1000UL)
#define GPIOF_BASE		(AHB1_BASE + 0x1400UL)
#define GPIOG_BASE		(AHB1_BASE + 0x1800UL)
#define GPIOH_BASE		(AHB1_BASE + 0x1C00UL)

#define GPIOA			((GPIO_Typedef*) GPIOA_BASE)
#define GPIOB			((GPIO_Typedef*) GPIOB_BASE)
#define GPIOC			((GPIO_Typedef*) GPIOC_BASE)
#define GPIOD			((GPIO_Typedef*) GPIOD_BASE)
#define GPIOE			((GPIO_Typedef*) GPIOE_BASE)
#define GPIOF			((GPIO_Typedef*) GPIOF_BASE)
#define GPIOG			((GPIO_Typedef*) GPIOG_BASE)
#define GPIOH			((GPIO_Typedef*) GPIOH_BASE)

#define GPIO_PIN_0					(0x0000)
#define GPIO_PIN_1					(0x0001)
#define GPIO_PIN_2					(0x0002)
#define GPIO_PIN_3					(0x0003)
#define GPIO_PIN_4					(0x0004)
#define GPIO_PIN_5					(0x0005)
#define GPIO_PIN_6					(0x0006)
#define GPIO_PIN_7					(0x0007)
#define GPIO_PIN_8					(0x0008)
#define GPIO_PIN_9					(0x0009)
#define GPIO_PIN_10					(0x000A)
#define GPIO_PIN_11					(0x000B)
#define GPIO_PIN_12					(0x000C)
#define GPIO_PIN_13					(0x000D)
#define GPIO_PIN_14					(0x000E)
#define GPIO_PIN_15					(0x000F)

#define	GPIO_INPUT					(0x00U)
#define	GPIO_OUTPUT					(0x01U)
#define	GPIO_ALTERNATE				(0x02U)
#define	GPIO_ANALOG					(0x03U)

#define GPIO_MODE_OUTPUT_PP			(0x00U)
#define GPIO_MODE_OUTPUT_OD			(0x01U)

#define GPIO_NOPULL					(0x00U)
#define GPIO_PULLUP					(0x01U)
#define GPIO_PULLDOWN				(0x02U)

#define GPIO_SPEED_FREQ_LOW	 		(0x00U)
#define GPIO_SPEED_FREQ_MEDIUM		(0x01U)
#define GPIO_SPEED_FREQ_FAST		(0x02U)
#define GPIO_SPEED_FREQ_HIGH		(0x03U)

#define GPIO_AF0					(0x00U)
#define GPIO_AF1					(0x01U)
#define GPIO_AF2					(0x02U)
#define GPIO_AF3					(0x03U)
#define GPIO_AF4					(0x04U)
#define GPIO_AF5					(0x05U)
#define GPIO_AF6					(0x06U)
#define GPIO_AF7					(0x07U)
#define GPIO_AF8					(0x08U)
#define GPIO_AF9					(0x09U)
#define GPIO_AF10					(0x0AU)
#define GPIO_AF11					(0x0BU)
#define GPIO_AF12					(0x0CU)
#define GPIO_AF13					(0x0DU)
#define GPIO_AF14					(0x0EU)
#define GPIO_AF15					(0x0FU)

#define	GPIO_SET					1
#define	GPIO_RESET					0


void GPIO_Init(GPIO_Typedef* GPIOx, GPIO_InitTypeDef* GPIO_Init);
void GPIO_DeInit(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN);

void GPIO_WritePin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN, uint8_t state);
void GPIO_TogglePin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN);
bool GPIO_ReadPin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN);
bool GPIO_LockPin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN);

#endif /* GPIO_H_ */
