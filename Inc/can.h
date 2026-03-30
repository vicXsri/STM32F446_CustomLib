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
	__IO	uint32_t 	  		IER;			// CAN Interrupt Enable Register
	__IO	uint32_t 	  		ESR;			// CAN Error Status Register
	__IO	uint32_t 	  		BTR;			// CAN Bit Timing Register
	uint32_t 		 	  		Reserved0[88];
	CAN_TxMailbox_TypeDef 		sTxMailBox[3];	// CAN MailBox For Transmit
	CAN_FIFOMailbox_TypeDef		sFIFOMailBox[2];// CAN FIFO For Recieve
			uint32_t 			Reserved1[12];
	__IO	uint32_t 			FMR; 			// CAN Filter Master Status Register
	__IO	uint32_t 			FM1R; 			// CAN Filter Mode Register
			uint32_t 			Reserved2;
	__IO	uint32_t 			FS1R;			// CAN Filter Scale Register
			uint32_t 			Reserved3;
	__IO	uint32_t 			FFA1R;			// CAN Filter FIFO Assignment Register
			uint32_t 			Reserved4;
	__IO	uint32_t 			FA1R;			// CAN Filter Activation  Register
			uint32_t 			Reserved5[8];
	CAN_FilterRegister_TypeDef	sFilterRegister[28]; // CAN Filter Bank Register
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

typedef struct{
	uint32_t StdId; // Standard ID
	uint32_t ExtId; // Extended ID
	uint32_t IDE;   // Select the Identifier Type, if IDE = 0 (STD), if IDE = 1 (EXT)
	uint32_t RTR;   // Remote Transmission Mode, Data mode / Remote
	uint32_t DLC;   // Data Length
	uint32_t TimeStamp; // Time Stamp
}CAN_TxTypeDef;

typedef struct{
	uint32_t StdId; // Standard ID
	uint32_t ExtId; // Extended ID
	uint32_t IDE;   // Select the Identifier Type, if IDE = 0 (STD), if IDE = 1 (EXT)
	uint32_t RTR;   // Remote Transmission Mode
	uint32_t DLC;   // Data Length
	uint32_t TimeStamp; // Time Stamp
	uint32_t FilterMatchIndex; // Specifies the Index of matching acceptance filter
}CAN_RxTypeDef;

typedef struct{
	uint32_t FilterIdHigh; 			/* Specifies Filter Identification Number
	 	 	 	 	 	 	  	  	  	  (MSB for 32 bit config and first part for 16 bit configuration)*/
	uint32_t FilterIdLow; 			/* Specifies Filter Identification Number
	 	 	 	 	 	 	  	  	  	  (LSB for 32 bit config and second part for 16 bit configuration)*/
	uint32_t FilterMaskIdHigh;		/*	*/
	uint32_t FilterMaskIdLow;
	uint32_t FilterFIFOAssignment;
	uint32_t FilterBank;
	uint32_t FilterMode;
	uint32_t FilterScale;
	uint32_t FilterActivation;
	uint32_t SlaveStartFilterBank;

}CAN_FilterTypeDef;

typedef enum{
	CAN_STATE_RESET			= 0x00U,
	CAN_STATE_READY			= 0x01U,
	CAN_STATE_LISTENING		= 0x02U,
	CAN_STATE_SLEEP_PENDING	= 0x03U,
	CAN_STATE_SLEEP_ACTIVE  = 0x04U,
	CAN_STATE_ERROR			= 0x05U

}CAN_StateTypeDef;


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
#define CAN_ERROR_NONE					0x00000000U
#define CAN_ERROR_TIMEOUT				0x00000001U
#define CAN_ERROR_NOT_INTIALIZED		0x00000002U
#define CAN_ERROR_NOT_READY				0x00000003U
#define CAN_ERROR_PARAM					0x00000004U


/*CAN Id*/
#define CAN_STD_ID						0x00000000U
#define CAN_EXT_ID						0x00000004U


/*Recieve FIFOs*/
#define RX_FIFO0						0x00000000U
#define RX_FIFO1						0x00000001U

/*Filter Banks*/
#define FILTER_BANK0				0x00000000U
#define FILTER_BANK1				0x00000001U
#define FILTER_BANK2				0x00000002U
#define FILTER_BANK3				0x00000003U
#define FILTER_BANK4				0x00000004U
#define FILTER_BANK5				0x00000005U
#define FILTER_BANK6				0x00000006U
#define FILTER_BANK7				0x00000007U
#define FILTER_BANK8				0x00000008U
#define FILTER_BANK9				0x00000009U
#define FILTER_BANK10				0x0000000AU
#define FILTER_BANK11				0x0000000BU
#define FILTER_BANK12				0x0000000CU
#define FILTER_BANK13				0x0000000DU
#define FILTER_BANK14				0x0000000EU
#define FILTER_BANK15				0x0000000FU
#define FILTER_BANK16				0x00000010U
#define FILTER_BANK17				0x00000011U
#define FILTER_BANK18				0x00000012U
#define FILTER_BANK19				0x00000013U
#define FILTER_BANK20				0x00000014U
#define FILTER_BANK21				0x00000015U
#define FILTER_BANK22				0x00000016U
#define FILTER_BANK23				0x00000017U
#define FILTER_BANK24				0x00000018U
#define FILTER_BANK25				0x00000019U
#define FILTER_BANK26				0x0000001AU
#define FILTER_BANK27				0x0000001BU

/*Filter Modes*/
#define CAN_FILTERMODE_IDMASK		0x00000000U
#define CAN_FILTERMODE_IDLIST		0x00000001U

/*Filter Scale Modes*/
#define CAN_FILTERSCALE_16BIT		0x00000000U
#define CAN_FILTERSCALE_32BIT		0x00000001U

/*CAN RTR Modes*/
#define CAN_RTR_DATA				0x00000000U
#define CAN_RTR_REMOTE				0x00000002U

Status_TypeDef CAN_Init(CAN_HandleTypeDef* hcan);
Status_TypeDef CAN_ConfigFilter(CAN_HandleTypeDef* hcan, CAN_FilterTypeDef* canFilter);
Status_TypeDef CAN_Start(CAN_HandleTypeDef* hcan);
Status_TypeDef CAN_TransmitMessage(CAN_HandleTypeDef* hcan, const CAN_TxTypeDef* pTxHeader, const uint8_t txData[], uint32_t* mailbox);
Status_TypeDef CAN_Compute_Baud(CAN_HandleTypeDef* hcan, uint32_t* BaudRate);
void CAN_MspInit(CAN_HandleTypeDef* hcan);

#endif /* CAN_H_ */
