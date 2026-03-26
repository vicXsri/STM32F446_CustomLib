/*
 * pwr.h
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#ifndef PWR_H_
#define PWR_H_

#include "main.h"


typedef struct{
	uint32_t CR; // power control register
	uint32_t CSR; //power control/status register
}PWR_TypeDef;

#define PWR			   ((PWR_TypeDef*) PWR_BASE)

#define PWR_VOS_SCALE1 (0x3U << 14)


void __PWR_VOLTAGESCALING_CONFIG(void);

#endif /* PWR_H_ */
