/*
 * can.h
 *
 *  Created on: Mar 26, 2026
 *      Author: Vichu
 */

#ifndef CAN_H_
#define CAN_H_

#include "main.h"

typedef struct{
	__IO	uint32_t TIR;
	__IO	uint32_t TDTR;
	__IO	uint32_t TDLR;
	__IO	uint32_t TDHR;
}CAN_TxMailbox_TypeDef;

typedef struct{
	__IO	uint32_t RIR;
	__IO	uint32_t RDTR;
	__IO	uint32_t RDLR;
	__IO	uint32_t RDHR;
}CAN_FIFOMailbox_TypeDef;

typedef struct{
	__IO	uint32_t FR1;
	__IO	uint32_t FR2;
}CAN_FilterRegister_TypeDef;

typedef struct{
	__IO	uint32_t 	  		MCR;  			// CAN Master Control register
	__IO	uint32_t 	  		MSR;  			// CAN Master Status Register
	__IO	uint32_t 	  		TSR;  			// CAN Transmit Status Register
	__IO	uint32_t 	  		RF0R; 			// CAN Recieve FIFO0 Register
	__IO	uint32_t 	  		RF1R; 			// CAN Recieve FIFO1 Register
	__IO	uint32_t 	  		IER;
	__IO	uint32_t 	  		ESR;
	__IO	uint32_t 	  		BTR;
	uint32_t 		 	  		Reserved0[88];
	CAN_TxMailbox_TypeDef 		sTxMailBox[3];
	CAN_FIFOMailbox_TypeDef		sFIFOMailBox[2];
			uint32_t 			Reserved1[12];
	__IO	uint32_t 			FMR;
	__IO	uint32_t 			FM1R;
			uint32_t 			Reserved2;
	__IO	uint32_t 			FS1R;
			uint32_t 			Reserved3;
	__IO	uint32_t 			FFA1R;
			uint32_t 			Reserved4;
	__IO	uint32_t 			FA1R;
			uint32_t 			Reserved5[8];
	CAN_FilterRegister_TypeDef	sFilterRegister[28];
}CAN_TypeDef;

typedef struct{
	uint8_t Mode;
	uint16_t Prescaler; // Max num 1 - 1024
	uint8_t	 TimeSegment1; // max 16
	uint8_t	 TimeSegment2; // max 8
	uint8_t  SyncJumpWidth; // max 1-4
}CAN_IntitTypeDef;


typedef struct{
	CAN_TypeDef 		*Instance;
	CAN_IntitTypeDef	Init;
}CAN_HandleTypeDef;

#define CAN1	((CAN_TypeDef*) CAN1_BASE)
#define CAN2	((CAN_TypeDef*) CAN2_BASE)

#define CAN_Prescaler

void CAN_Init(CAN_HandleTypeDef* hcan);
void CAN1_MspInit(CAN_HandleTypeDef* hcan);

#endif /* CAN_H_ */
