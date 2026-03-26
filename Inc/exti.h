/*
 * exti.h
 *
 *  Created on: May 31, 2025
 *      Author: Vichu
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "main.h"


typedef struct{
	__IO uint32_t IMR; //Interrupt mask register
	__IO uint32_t EMR; //Event mask register
	__IO uint32_t RTSR; //Rising trigger selection register
	__IO uint32_t FTSR; //Falling trigger selection register
	__IO uint32_t SWIER; //Software interrupt event register
	__IO uint32_t PR; //Pending register
}EXTI_typedef;

#define EXTI			((EXTI_typedef*) EXTI_BASE)


#endif /* EXTI_H_ */
