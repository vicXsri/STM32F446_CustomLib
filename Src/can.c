/*
 * can.c
 *
 *  Created on: Mar 26, 2026
 *      Author: Vichu
 */

#include "can.h"



void CAN_Init(CAN_HandleTypeDef* hcan){

	/*Initialise GPIO Pins*/
	CAN1_MspInit(hcan);

	/*Setup Baud Rate register  the baud Rate -> BTR*/
	WRITE_REG(hcan->Instance->BTR, (hcan->Init.Prescaler-1 << 0)  	|
									(hcan->Init.TimeSegment1 << 16)  |
									(hcan->Init.TimeSegment2 << 20)  |
									(hcan->Init.SyncJumpWidth << 24));

}
