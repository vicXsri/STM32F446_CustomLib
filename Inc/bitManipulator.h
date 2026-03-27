/*
 * bitManipulator.h
 *
 *  Created on: Mar 26, 2026
 *      Author: Vichu
 */

#ifndef BITMANIPULATOR_H_
#define BITMANIPULATOR_H_

#include "main.h"

#define	SET_BIT(REG, BIT)	((REG) |= (BIT)) //Setting specific bit to 1, without the offset, The offset should be passed inside Directly

#define	RESET_BIT(REG, BIT)	((REG) &=~(BIT)) //Reseting the bit to 0, without the offset,  The offset should be passed inside Directly

#define	READ_BIT(REG, MASK)	((REG) & (MASK)) //Read specific bit value


#define	INVERT_BIT(REG, MASK, OFF)	((REG) ^= (MASK << OFF)) //Read specific bit value

#define	READ_FIELD(REG, MASK, OFF)	((REG) & (MASK << OFF)) //Read specific bit value

#define SET_FIELD(REG, MASK, OFF) ((REG) |= (MASK << OFF)) // Setting the bit to 1, with offset

#define	CLEAR_FIELD(REG, MASK, OFF)	((REG) &= ~(MASK << OFF)) // Setting the bit to 0, with offset


#define	CLEAR_REG(REG)	((REG) = (0x00))

#define	WRITE_REG(REG, VAL)	((REG) = (VAL))

#endif /* BITMANIPULATOR_H_ */
