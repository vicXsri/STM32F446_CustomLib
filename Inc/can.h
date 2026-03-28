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
	uint32_t 	Mode;
	uint16_t 	Prescaler; // Max num 1 - 1024
	uint8_t	 	TimeSegment1; // max 16
	uint8_t	 	TimeSegment2; // max 8
	uint8_t  	SyncJumpWidth; // max 1-4
	uint8_t     TimeTriggeredMode;
	uint8_t     AutoBusOff;
	uint8_t     AutoWakeUp;
	uint8_t     AutoRetranmission;
	uint8_t     RecieveFIFOLocked;
	uint8_t     TransmitFIFOPriority;
}CAN_IntitTypeDef;

typedef enum{
	CAN_STATE_RESET			= 0x00U,
	CAN_STATE_READY			= 0x01U,
	CAN_STATE_LISTENING		= 0x02U,
	CAN_STATE_SLEEP_PENDING	= 0x03U,
	CAN_STATE_SLEEP_ACTIVE  = 0x04U,
	CAN_STATE_ERROR			= 0x05U

}CAN_StateTypeDef;

//typedef enum{
//
//};

typedef struct{
	CAN_TypeDef 			*Instance;
	CAN_IntitTypeDef		Init;
	__IO CAN_StateTypeDef	state;
	__IO uint32_t			ErrorCode;
}CAN_HandleTypeDef;


#define CAN_TIMEOUT			10U

#define CAN1	((CAN_TypeDef*) CAN1_BASE)
#define CAN2	((CAN_TypeDef*) CAN2_BASE)

/*CAN BUS MODES*/
#define CAN_NORMAL_MODE				0x00000000U
#define CAN_LOOPBACK_MODE			0x40000000U
#define CAN_SILENT_MODE				0x80000000U
#define CAN_SILENT_LOOPBACK_MODE	CAN_LOOPBACK_MODE | CAN_SILENT_MODE


/*CAN BUS ERRORS*/
#define CAN_ERROR_NONE			0x00000000U
#define CAN_ERROR_TIMEOUT		0x00000001U

Status_TypeDef CAN_Init(CAN_HandleTypeDef* hcan);
uint32_t CAN_Compute_Baud(CAN_HandleTypeDef* hcan);
void CAN_MspInit(CAN_HandleTypeDef* hcan);

#endif /* CAN_H_ */
