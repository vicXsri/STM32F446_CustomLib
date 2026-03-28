/*
 * can.c
 *
 *  Created on: Mar 26, 2026
 *      Author: Vichu
 */

#include "can.h"

Status_TypeDef CAN_Init(CAN_HandleTypeDef* hcan){

	if(hcan == NULL) return VIC_ERROR;

	uint32_t tickstart;

	/*Initialise GPIO Pins*/
	if(hcan->state == CAN_STATE_RESET){
		CAN_MspInit(hcan);
	}


	/*Request Initialization Mode*/
	SET_BIT(hcan->Instance->MCR, (0x1UL << 0U));

	tickstart = Get_Tick();

	while((hcan->Instance->MSR & ((0x1UL << 0U))) == 0U){
		if((Get_Tick() - tickstart) > CAN_TIMEOUT){
			/*Error Code Updation*/
			hcan->ErrorCode |= CAN_ERROR_TIMEOUT;

			/*Current CAN State*/
			hcan->state = CAN_STATE_ERROR;

			return VIC_ERROR;
		}
	}

	/*SET the Sleep bit to '0', SO WE CAN EXIT FROM SLEEP MODE */
	CLEAR_FIELD(hcan->Instance->MCR, 0x01UL, 1U);

	tickstart = Get_Tick();

	while((hcan->Instance->MSR & ((0x1UL << 1U))) != 0U){
		if((Get_Tick() - tickstart) > CAN_TIMEOUT){
			/*Error Code Updation*/
			hcan->ErrorCode |= CAN_ERROR_TIMEOUT;

			/*Current CAN State*/
			hcan->state = CAN_STATE_ERROR;

			return VIC_ERROR;
		}
	}

	/*Set the Time Triggered Mode*/
	(hcan->Init.TimeTriggeredMode == ENABLE)?
											SET_BIT(hcan->Instance->MCR, (1U << 0x07)):
											RESET_BIT(hcan->Instance->MCR, (1U << 0x07));

	/*Set the Automatic Bus-off Management */
	(hcan->Init.AutoBusOff == ENABLE)?
											SET_BIT(hcan->Instance->MCR, (1U << 0x06)):
											RESET_BIT(hcan->Instance->MCR, (1U << 0x06));

	/*Set the AutoWakeUp wake-up mode*/
	(hcan->Init.AutoWakeUp == ENABLE)?
											SET_BIT(hcan->Instance->MCR, (1U << 0x05)):
											RESET_BIT(hcan->Instance->MCR, (1U << 0x05));

	/*Set the AutoRetransmission */
	(hcan->Init.AutoRetranmission == ENABLE)?
											RESET_BIT(hcan->Instance->MCR, (1U << 0x04)):
											SET_BIT(hcan->Instance->MCR, (1U << 0x04));

	/*Set the recieve FIFO lock mode */
	(hcan->Init.RecieveFIFOLocked == ENABLE)?
											SET_BIT(hcan->Instance->MCR, (1U << 0x03)):
											RESET_BIT(hcan->Instance->MCR, (1U << 0x03));

	/*Set the transmit FIFO Priority */
	(hcan->Init.TransmitFIFOPriority == ENABLE)?
											SET_BIT(hcan->Instance->MCR, (1U << 0x02)):
											RESET_BIT(hcan->Instance->MCR, (1U << 0x02));

	/*Setup Baud Rate register  the baud Rate -> BTR*/
	WRITE_REG(hcan->Instance->BTR,
									(uint32_t)((hcan->Init.Prescaler - 1U) << 0)  |
									(hcan->Init.TimeSegment1 << 16)  |
									(hcan->Init.TimeSegment2 << 20)  |
									(hcan->Init.SyncJumpWidth << 24) |
									(hcan->Init.Mode)
			 );



	return VIC_OK;
}

uint32_t CAN_Compute_Baud(CAN_HandleTypeDef* hcan){

    float apb1clk = (float) (RCC_GetP1CLK_Freq()/1000000);

    float tpclk = (1.0/apb1clk) * 1000 ;

    uint16_t prescaler = READ_FIELD(hcan->Instance->BTR, 0, 0x3FF) + 1;

    float tq =  tpclk * prescaler;

    uint16_t bs1   	= READ_FIELD(hcan->Instance->BTR, 16,0x0F),
    		 bs2    = READ_FIELD(hcan->Instance->BTR, 20,0x07),
			 sync   = READ_FIELD(hcan->Instance->BTR, 24,0x03);

    float N = sync + bs1 + bs2;

    float NBT = (N * tq) / 1000;

    uint32_t BaudRate = 1/(NBT / 1000000);

    return BaudRate;
}
