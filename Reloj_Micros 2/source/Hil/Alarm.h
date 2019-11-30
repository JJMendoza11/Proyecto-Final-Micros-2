/*
 * Alarm.h
 *
 *  Created on: 29 nov. 2019
 *      Author: lucky
 */

#ifndef HIL_ALARM_H_
#define HIL_ALARM_H_

void Alarm_vfnInit ( void );
void Alarm_vfnMain ( void );
void Alarm_vfnSetUp (uint8_t Val);
void Alarm_vfnHandler (void);

typedef enum{
	enIdleA = 0,
	enConfiA,
	enEndConfiA,
	enSetA,
	enStopA,
	enIHelpA
}tenAlarmStates;

#endif /* HIL_ALARM_H_ */
