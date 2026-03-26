/*
 * debounce.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */


#include "debounce.h"


void Debounce_Init(Debounce_Handel_t* handle, uint32_t delay_ms){
	if(handle != NULL){
		handle->last_tick = 0;
		handle->debounce_delay = delay_ms;
	}
}

bool Debounce_Check(Debounce_Handel_t* handle, uint32_t current_tick){
	if(handle == NULL) return false;

	if((current_tick - handle->last_tick) >= handle->debounce_delay){
		handle->last_tick = current_tick;
		return true;
	}
	return false;
}
