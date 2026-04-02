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
//	SET_BIT(hcan->Instance->MCR, (0x1UL << 1U));
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
									((hcan->Init.TimeSegment1 - 1) <<  16U)  	  |
									((hcan->Init.TimeSegment2 - 1) <<  20U)  	  |
									((hcan->Init.SyncJumpWidth - 1) << 24U)       |
									(hcan->Init.Mode)
			 );

	/*Set the Error Code*/
	hcan->ErrorCode = CAN_ERROR_NONE;

	/*Change the CAN State*/
	hcan->state = CAN_STATE_READY;

	return VIC_OK;
}

Status_TypeDef CAN_ConfigFilter(CAN_HandleTypeDef* hcan, CAN_FilterTypeDef* canFilter){

	uint32_t filternbrbitpos;
	CAN_TypeDef *can_fb;
	CAN_StateTypeDef state = hcan->state;

	if((state == CAN_STATE_READY) || (state == CAN_STATE_LISTENING)){

#if defined(CAN3)
		/*Check the CAN Instance*/
		if(hcan->Instance == CAN3){
			/*CAN3 is a single Instance with 14 dedicated filter Banks*/
			can_fb = hcan->Instance;
		}
		else{
			/*CAN1 & CAN2 are Dual Instance with 28 common filter Banks*/
			/*Selecting the Master Instance*/
			can_fb = CAN1;
		}
#elif defined(CAN2)
		/*CAN1 & CAN2 are Dual Instance with 28 common filter Banks*/
		/*Selecting the Master Instance*/
		can_fb = CAN1;
#else
		/*CAN1 is a single Instance with 14 dedicated filter Banks*/
		can_fb = hcan->Instance;
#endif
		/*SET the Intialziation mode for Filter*/
		SET_FIELD(can_fb->FMR, 0x01U, 0U);

#if defined(CAN3)
		if(can_ip == CAN1){
			/*Set the start Filter Number of CAN2 Slave Instance*/
			CLEAR_FIELD(can_fb->FMR, 0x3FUL, 0x08U);
			SET_FIELD(can_fb->FMR, canFilter->SlaveStartFilterBank, 0x08U );
		}
#elif defined(CAN2)
		/*Select the Start Filter Number of CAN2 Slave Instance*/
		CLEAR_FIELD(can_fb->FMR, 0x3FUL, 0x08U);
		SET_FIELD(can_fb->FMR, canFilter->SlaveStartFilterBank, 0x08U );
#endif
		/*Convert Filter Number into Bit Position*/
		filternbrbitpos = (uint32_t)1 << (canFilter->FilterBank & 0x1F);

		/*Filter Deactivation*/
		RESET_BIT(can_fb->FA1R,filternbrbitpos);

		/*Filter Scale*/
		if(canFilter->FilterScale == CAN_FILTERSCALE_16BIT){
			/*16 bit scale for Filter*/
			RESET_BIT(can_fb->FS1R, filternbrbitpos);

			/*First 16-bit identifier and First 16-bit Mask*/
			can_fb->sFilterRegister[canFilter->FilterBank].FR1=
					((0X0000FFFFU & (uint32_t)canFilter->FilterMaskIdLow) << 16U) |
					(0X0000FFFFU & (uint32_t)canFilter->FilterMaskIdLow);

			/*First 16-bit identifier and First 16-bit Mask*/
			can_fb->sFilterRegister[canFilter->FilterBank].FR2=
					((0X0000FFFFU & (uint32_t)canFilter->FilterMaskIdHigh) << 16U) |
					(0X0000FFFFU & (uint32_t)canFilter->FilterMaskIdHigh);


		}
		if(canFilter->FilterScale == CAN_FILTERSCALE_32BIT){

			/*32 bit scale for Filter*/
			SET_BIT(can_fb->FS1R, filternbrbitpos);

			/*32-bit identifier and First 32-bit identifier*/
			can_fb->sFilterRegister[canFilter->FilterBank].FR1=
					((0X0000FFFFU & (uint32_t)canFilter->FilterIdHigh) << 16U) |
					(0X0000FFFFU & (uint32_t)canFilter->FilterIdLow);

			/*32-bit mask or Second 32-bit identifier*/
			can_fb->sFilterRegister[canFilter->FilterBank].FR2=
					((0X0000FFFFU & (uint32_t)canFilter->FilterMaskIdHigh) << 16U) |
					(0X0000FFFFU & (uint32_t)canFilter->FilterMaskIdLow);
		}

		/*Filter Mode*/
		if(canFilter->FilterMode == CAN_FILTERMODE_IDMASK){
			RESET_BIT(can_fb->FM1R, filternbrbitpos);
		}else{
			SET_BIT(can_fb->FM1R, filternbrbitpos);
		}

		/*Filter FIFO Assignment*/
		if(canFilter->FilterFIFOAssignment == RX_FIFO0){
			RESET_BIT(can_fb->FFA1R, filternbrbitpos);
		}else{
			SET_BIT(can_fb->FFA1R, filternbrbitpos);
		}

		/*Filter Activation*/
		if(canFilter->FilterActivation == ENABLE){
			SET_BIT(can_fb->FA1R, filternbrbitpos);
		}

		/*Leave the Intiazlization Mode to Active Filter Mode*/
		CLEAR_FIELD(can_fb->FMR, 0x01U, 0U);

		/*Return Status*/
		return VIC_OK;
	}
	else{
		/*Update Error Code*/
		hcan->ErrorCode |= CAN_ERROR_NOT_INTIALIZED;

		/*Return Status*/
		return VIC_ERROR;
	}



}

Status_TypeDef CAN_Start(CAN_HandleTypeDef* hcan){
	uint32_t tickstart=0;

	if(hcan->state == CAN_STATE_READY){
		/*Chnage CAN Pheripheral State*/
		hcan->state = CAN_STATE_LISTENING;

		/*Request Leave Intialization - this is for additional Saftey !!*/
		CLEAR_FIELD(hcan->Instance->MCR, 0x01U, 0U);

		/*Get Tick*/
		tickstart = Get_Tick();

		/*Wait for the ack From MSR reg for Initialization*/
		while((hcan->Instance->MSR & (0x1UL << 0U)) != 0x00U){
			/*Verify Timeout*/
			if((Get_Tick() - tickstart) > CAN_TIMEOUT){
				/*Update Error Code*/
				hcan->ErrorCode |= CAN_ERROR_TIMEOUT;
				/*Change Can State*/
				hcan->state = CAN_STATE_ERROR;

				/*Return Function Status*/
				return VIC_ERROR;
			}
		}
		/*Reset CAN Error Code*/
		hcan->ErrorCode = CAN_ERROR_NONE;

		/*Return Function Status*/
		return VIC_OK;
	}
	else{

		/*Update CAN Error Code*/
		hcan->ErrorCode |= CAN_ERROR_NOT_READY;

		/*Return Function Status*/
		return VIC_ERROR;
	}
}

Status_TypeDef CAN_TransmitMessage(CAN_HandleTypeDef* hcan, const CAN_TxTypeDef* pTxHeader, const uint8_t txData[], uint32_t* mailbox){

	uint32_t transmitmailbox = 0, tsr = READ_REG(hcan->Instance->TSR); //Transmit Status Register
	CAN_StateTypeDef state = hcan->state;

	if((state == CAN_STATE_READY) || (state == CAN_STATE_LISTENING)){

		if(((tsr & (1UL << 26U)) != 0U) ||
		   ((tsr & (1UL << 27U)) != 0U) ||
		   ((tsr & (1UL << 28U)) != 0U)){

			/*Select an Empty transmit mailbox*/
			transmitmailbox = (tsr & (0x3UL << 24U) >> (24U));

			/*Store the Tx mailbox*/
			*mailbox = (uint32_t)1 << transmitmailbox;

			/*Set up the Id*/
			if(pTxHeader->IDE == CAN_STD_ID){
				hcan->Instance->sTxMailBox[transmitmailbox].TIR =
						((pTxHeader->StdId << 21U)| pTxHeader->RTR);
			}else{
				hcan->Instance->sTxMailBox[transmitmailbox].TIR =
						((pTxHeader->ExtId << 3U) | pTxHeader->RTR | pTxHeader->IDE);
			}
			/*Set the DLC*/
			hcan->Instance->sTxMailBox[transmitmailbox].TDTR = (pTxHeader->DLC);

			if( pTxHeader->TimeStamp == ENABLE ){
				SET_FIELD(hcan->Instance->sTxMailBox[transmitmailbox].TDTR, 0x01UL,8U);
			}
			/*Write data into the Registers*/
			WRITE_REG(hcan->Instance->sTxMailBox[transmitmailbox].TDHR,
						((uint32_t)txData[7] << 24U) |
						((uint32_t)txData[6] << 16U) |
						((uint32_t)txData[5] << 8U ) |
						((uint32_t)txData[4] << 0U ));

			WRITE_REG(hcan->Instance->sTxMailBox[transmitmailbox].TDLR,
						((uint32_t)txData[3] << 24U) |
						((uint32_t)txData[2] << 16U) |
						((uint32_t)txData[1] << 8U ) |
						((uint32_t)txData[0] << 0U ));

			/*Set Reqquest Transmission*/
			SET_FIELD(hcan->Instance->sTxMailBox[transmitmailbox].TIR, 0x01UL, 0U);

			/*Return Function Status*/
			return VIC_OK;
		}
		else{

			/*Update Error Code*/
			hcan->ErrorCode |= CAN_ERROR_PARAM;

			/*Return Function Status*/
			return VIC_ERROR;
		}
	}
	else{

		/*Update Error Code*/
		hcan->ErrorCode |= CAN_ERROR_NOT_INTIALIZED;

		/*Return Function Status*/
		return VIC_ERROR;
	}
}

Status_TypeDef CAN_Compute_Baud(CAN_HandleTypeDef* hcan, uint32_t* BaudRate){

	if(	(hcan->state == CAN_STATE_READY) || (hcan->state == CAN_STATE_LISTENING) ){
		float apb1clk = (float) (RCC_GetP1CLK_Freq()/1000000);

		float tpclk = (1.0/apb1clk) * 1000 ;

		uint16_t prescaler = READ_FIELD(hcan->Instance->BTR, 0, 0x3FF) + 1;

		float tq =  tpclk * prescaler;

		uint16_t bs1   	= READ_FIELD(hcan->Instance->BTR, 16,0x0F) + 1,
				 bs2    = READ_FIELD(hcan->Instance->BTR, 20,0x07) + 1,
				 sync   = READ_FIELD(hcan->Instance->BTR, 24,0x03) + 1;

		float N = sync + bs1 + bs2;

		float NBT = (N * tq) / 1000;

		 *BaudRate = 1/(NBT / 1000000);

		return VIC_OK;

	}
	return VIC_ERROR;
}
