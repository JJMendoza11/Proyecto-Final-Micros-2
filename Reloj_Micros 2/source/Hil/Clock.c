/*
 * Clock.c
 *
 *  Created on: 28 nov. 2019
 *      Author: lucky
 */

#include "MKL25Z4.h"
#include "Clock.h"
#include "OLED_Screen_DRiver.h"
#include "Reloj_Micros 2.h"

extern uint32_t Segundos;
_Bool Sumar = 0;
_Bool x = 0;


tenClockStates ClockStates = enConfi;


char u8Time[] = {"00:00"};
char u8Date [] = {"01/Jan/00"};

uint32_t u32Min2Sec = 0;
uint32_t u32Hrs2Sec = 0;
uint8_t Time[enTotalTime]={};
uint32_t u32Snap = 0;
uint8_t u8Min = 0;
uint8_t u8Hrs = 0;
uint8_t u8Day = 1;
uint8_t u8Month = 0;
uint8_t u8Year = 0;

uint8_t u8LastDayMonth[13] ={29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 , 31};

void Clock_vfnDisplayMenu ( void );

void Clock_vfnInit ( void )
{
	SSD1306_Begin();

	SSD1306_ClearDisplay();

	Clock_vfnDisplayMenu();

	SSD1306_DrawText(35, 16, u8Time, 2);

	SSD1306_DrawText(0, 2, u8Date, 1);

	SSD1306_DrawText(60, 2, "M Tu W Th F", 1);

	SSD1306_Display();

}

void Clock_vfnMain ( void )
{
	switch (ClockStates)
	{
	case enConfi:
			if ( Sumar )
			{
				if ( !x )
				{
					u8Min++;
					SSD1306_DrawFastHLine(68, 31, 25, 1);
					SSD1306_DrawFastHLine(33, 31, 25, 0);
				}
				else
				{
					u8Hrs++;
					SSD1306_DrawFastHLine(33, 31, 25, 1);
					SSD1306_DrawFastHLine(68, 31, 25, 0);
				}

				if ( u8Min == 60)
				{
					u8Min = 0;
				}

				if( u8Hrs == 24)
				{
					u8Hrs = 0;
				}

				u8Time [4] = u8Min % 10 + 48;
				u8Time [3] = u8Min / 10 + 48;
				u8Time [1] = u8Hrs % 10 + 48;
				u8Time [0] = u8Hrs / 10 + 48;

				SSD1306_DrawText(35, 16, u8Time, 2);

				SSD1306_Display();

				Sumar = 0;
			}
		break;
	case enEndConfi:
			u32Snap = Segundos;
			SSD1306_DrawFastHLine(68, 31, 25, 0);
			SSD1306_DrawFastHLine(33, 31, 25, 0);
			u32Min2Sec = u8Min * 60;
			u32Hrs2Sec = u8Hrs * 3600;
			ClockStates = enBusy;
		break;
	case enBusy:
			Decoder();

			u8Time [4] = Time[enMin] % 10 + 48;
			u8Time [3] = Time[enMin] / 10 + 48;
			u8Time [1] = Time[enHrs] % 10 + 48;
			u8Time [0] = Time[enHrs] / 10 + 48;

			SSD1306_DrawText(35, 16, u8Time, 2);
			ClockStates = enIdle;
		break;
	case enRefresh:
		SSD1306_Display();
		ClockStates = enBusy;
		break;
	default:

			if((Segundos - u32Snap)%60 == 0)
				ClockStates = enRefresh;

		break;
	}
}

void Clock_vfnDisplayMenu(void)
{
	SSD1306_DrawRect( 56, 0, 72, 11);

	SSD1306_DrawFastHLine(0,12,128, 1);
}

void Clock_vfnSetUp (uint8_t Val)
{
	if (ClockStates == enConfi)
	{
		if ( Val == 'S')
		{
			ClockStates = enEndConfi;
		}
		else
		{
			if(Val == 'D')
			{
				Sumar = 1;
			}
			else if (Val == 'A')
			{
				x ^= 1;
			}
		}
	}
	else
	{
		if ( Val == 'S')
		{
			ClockStates = enConfi;
		}
	}
}

void Decoder(void){
	Time[enMin]=(((Segundos - u32Snap + u32Min2Sec + u32Hrs2Sec ) %3600)/60);

	Time[enHrs]=((((Segundos - u32Snap + u32Min2Sec + u32Hrs2Sec)) %216000)/3600);

	if(Time[enHrs]==24){
		Time[enHrs]=0;
	}


}
