/*
 * stm32_f446xx.h
 *
 *  Created on: May 31, 2025
 *      Author: Vichu
 */

#ifndef STM32_F446XX_H_
#define STM32_F446XX_H_

#include "main.h"


#define PERIPH_BASE            (0x40000000UL) /*!< Base address of : AHB/ABP Peripherals                                                   */
#define APB1_BASE        	   (PERIPH_BASE + 0x00000UL) // Starting Address of APB1                                                 */
#define APB2_BASE        	   (PERIPH_BASE + 0x10000UL) // Starting Address of APB2                                                 */
#define AHB1_BASE        	   (PERIPH_BASE + 0x20000UL) // Starting Address of AHB1                                                 */

#define EXTI_BASE			   (PERIPH_BASE + 0x13C00UL)

#define SYSCFG_BASE			   (APB2_BASE + 0x3800UL)

#define RCC_BASE			   (AHB1_BASE + 0x3800UL)

#define PWR_BASE			   (PERIPH_BASE + 0x7000UL)

#define FLASH_BASE			   (AHB1_BASE + 0x3C00UL )


#define USART1_BASE			   (APB2_BASE + 0x1000UL )
#define USART2_BASE			   (APB1_BASE + 0x4400UL )
#define USART3_BASE			   (APB1_BASE + 0x4800UL )
#define UART4_BASE			   (APB1_BASE + 0x4C00UL )
#define UART5_BASE			   (APB1_BASE + 0x5000UL )
#define USART6_BASE			   (APB2_BASE + 0x1400UL )



#endif /* STM32_F446XX_H_ */
