/*
 * corem4.h
 *
 *  Created on: Jun 1, 2025
 *      Author: Vichu
 */

#ifndef CORE_M4_H_
#define CORE_M4_H_

#include "main.h"

#define NVIC_SETEN_BASE			0xE000E100UL
#define NVIC_CLEAREN_BASE		0xE000E180UL
#define NVIC_SETPEN_BASE		0xE000E200UL
#define NVIC_SETPEN_BASE		0xE000E200UL

#define SYS_CSR_BASE			0xE000E010UL

#define SYS_DEF_CORE_CLOCK		16000000UL
#define SYS_CORE_CLOCK			180000000UL

#define HSI_FREQ				16000000UL
#define HSE_FREQ    			8000000U


typedef struct{
	__IO uint32_t ISER[8U];
	__IO uint32_t RESERVED0[24U];
}NVIC_TypeDef;

typedef struct{
	__IO uint32_t SCR; // SysTick Control and Status Register, SYST_CSR
	__IO uint32_t RVR; // SysTick Reload Value Register, SYST_RVR
	__IO uint32_t CVR; // SysTick Current Value Register, SYST_CVR
	__IO uint32_t CALIB; // SysTick Calibration value Register, SYST_CALIB
}SysTick_TypeDef;


#define NVIC_R					((NVIC_TypeDef*)NVIC_SETEN_BASE)
#define SysTick					((SysTick_TypeDef*)SYS_CSR_BASE)

#define EXTI15_10_IRQ			(0x28U)
#define USART2_IRQ				(0x26U)


void NVIC_Enable(uint32_t IRQn);

#endif /* CORE_M4_H_ */
