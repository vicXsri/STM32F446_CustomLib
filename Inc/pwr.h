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

#define PWR_VOS_SCALE1  (0x03UL << 14U)
#define PWR_ODEN		(0x01UL << 16U)
#define PWR_ODSWEN		(0x01UL << 17U)

#define PWR_TIMEOUT		1000U

void __PWR_VOLTAGESCALING_CONFIG(void);
Status_TypeDef __PWR_OVERDRIVE_ENABLE(void);

#endif /* PWR_H_ */
