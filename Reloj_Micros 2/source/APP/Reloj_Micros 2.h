/*
 * Reloj_Micros 2.h
 *
 *  Created on: 28/11/2019
 *      Author: Poncho
 */

#ifndef RELOJ_MICROS_2_H_
#define RELOJ_MICROS_2_H_

#define ClockSet		(1<<0)
#define ChronoSet		(1<<1)
#define AlarmSet		(1<<2)
#define TimerSet		(1<<3)
#define Seconds			 1000
#define Mod				(1<<Mode)
#define ModeUart		'M'


typedef enum{
	enClock = 0,
	enChronometer,
	enAlarm,
	enTimer
}enClockStates;

typedef struct{
	uint8_t  Seg;
	uint8_t  Min;
	uint8_t  Hrs;
	uint8_t  Day;
	uint8_t  Mon;
	uint8_t  Year;
}sSetThings;

void Decoder(void);


#endif /* RELOJ_MICROS_2_H_ */
