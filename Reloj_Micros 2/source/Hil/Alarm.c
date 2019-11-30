/*
 * Alarm.c
 *
 *  Created on: 29 nov. 2019
 *      Author: lucky
 */

#include "MKL25Z4.h"
#include "OLED_Screen_DRiver.h"
#include "Reloj_Micros 2.h"
#include "Alarm.h"
#include "Clock.h"

extern uint32_t Segundos;
uint32_t ClockTime = 0;
_Bool OnScreen = 0;
_Bool SumarA = 0;
_Bool xA = 0;


tenAlarmStates AlarmStates = enIdleA;


char u8TimeAlarm[] = {"00:00"};


uint32_t u32SnapAlarm = 0;
uint8_t u8MinAlarm = 0;
uint8_t u8HrsAlarm = 0;


void Alarm_vfnDisplayMenu ( void );

void Alarm_vfnInit ( void )
{

	SSD1306_ClearDisplay();

	Alarm_vfnDisplayMenu();

	SSD1306_DrawText(35, 16, u8TimeAlarm, 2);

	SSD1306_DrawText(0, 2, "Alarm", 1);

	SSD1306_DrawText(60, 2, "JOJE", 1);

	SSD1306_Display();

}

void Alarm_vfnMain ( void )
{
	if(!OnScreen)
	{
		OnScreen = 1;
		Alarm_vfnInit();
	}
	switch (AlarmStates)
	{
	case enConfiA:
		SSD1306_DrawText(60, 2, "Confi", 1);
			if ( SumarA )
			{
				if ( !xA )
				{
					u8MinAlarm++;
					SSD1306_DrawFastHLine(68, 31, 25, 1);
					SSD1306_DrawFastHLine(33, 31, 25, 0);
				}
				else
				{
					u8HrsAlarm++;
					SSD1306_DrawFastHLine(33, 31, 25, 1);
					SSD1306_DrawFastHLine(68, 31, 25, 0);
				}

				if ( u8MinAlarm == 60)
				{
					u8MinAlarm = 0;
				}

				if( u8HrsAlarm == 24)
				{
					u8HrsAlarm = 0;
				}

				u8TimeAlarm [4] = u8MinAlarm % 10 + 48;
				u8TimeAlarm [3] = u8MinAlarm / 10 + 48;
				u8TimeAlarm [1] = u8HrsAlarm % 10 + 48;
				u8TimeAlarm [0] = u8HrsAlarm / 10 + 48;

				SSD1306_DrawText(35, 16, u8TimeAlarm, 2);

				SSD1306_Display();

				SumarA = 0;
			}
		break;
	case enEndConfiA:
		SSD1306_DrawText(60, 2, "Joje", 1);
			u32SnapAlarm = Segundos;
			SSD1306_DrawFastHLine(68, 31, 25, 0);
			SSD1306_DrawFastHLine(33, 31, 25, 0);
			ClockTime = getClockTime();
			u32SnapAlarm = u8MinAlarm * 60 + u8HrsAlarm * 3600 + Segundos - ClockTime;
			SSD1306_Display();
			AlarmStates = enIdleA;
		break;
	case enSetA:
		SSD1306_DrawText(60, 2, "Enable", 1);
		Reloj_SetAlarm (u32SnapAlarm);
		SSD1306_Display();
		AlarmStates = enIdleA;
		break;

	case enStopA:
		Reloj_StopAlarm();
		SSD1306_DrawText(60, 2, "Disable", 1);
		u32SnapAlarm = 0;
		u8MinAlarm = 0;
		u8HrsAlarm = 0;
		u8TimeAlarm [4] = u8MinAlarm % 10 + 48;
		u8TimeAlarm [3] = u8MinAlarm / 10 + 48;
		u8TimeAlarm [1] = u8HrsAlarm % 10 + 48;
		u8TimeAlarm [0] = u8HrsAlarm / 10 + 48;

		SSD1306_DrawText(35, 16, u8TimeAlarm, 2);

		SSD1306_Display();

		AlarmStates = enIdleA;
		break;

	case enIHelpA:
			SSD1306_ClearDisplay();
			SSD1306_DrawText(35, 16, "Joje", 2);
			SSD1306_Display();
		while(enIHelpA)
		{
			if(AlarmStates ==  enStopA)
				break;
		}
		break;
	default:
		break;
	}
}

void Alarm_vfnHandler (void)
{
	AlarmStates = enIHelpA;
}

void Alarm_vfnDisplayMenu(void)
{
	SSD1306_DrawRect( 56, 0, 72, 11);

	SSD1306_DrawFastHLine(0,12,128, 1);
}

void Alarm_vfnSetUp (uint8_t Val)
{
	if ( Val == 'W')
	{
		Reloj_ChangeScreen();
		OnScreen = 0;
	}
	if (AlarmStates == enConfiA)
	{
		if ( Val == 'S')
		{
			AlarmStates = enEndConfiA;
		}
		else
		{
			if(Val == 'D')
			{
				SumarA = 1;
			}
			else if (Val == 'A')
			{
				xA ^= 1;
			}
		}
	}
	else
	{
		if ( Val == 'S')
		{
			AlarmStates = enConfiA;
		}
		else
		{

			if ( Val == 'D')
			{
				AlarmStates = enSetA;
			}

			if ( Val == 'A')
			{
				AlarmStates = enStopA;
			}
		}
	}
}

