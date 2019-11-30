/*
 * Clock.h
 *
 *  Created on: 28 nov. 2019
 *      Author: lucky
 */

#ifndef HIL_CLOCK_H_
#define HIL_CLOCK_H_

#include "Reloj_Micros 2.h"


void Clock_vfnInit ( void );
void Clock_vfnMain ( void );
void Clock_vfnSetUp (uint8_t Val);
void Decoder(void);
uint32_t getClockTime ( void );

typedef enum{
	enIdle = 0,
	enConfi,
	enEndConfi,
	enBusy,
	enRefresh
}tenClockStates;

#endif /* HIL_CLOCK_H_ */
