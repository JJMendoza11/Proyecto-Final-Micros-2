
#include "MKL25Z4.h"
#include "Reloj_Micros 2.h"
#include "PIT.h"
#include "UART_DriverInt.h"
#include "I2CDRIVE.h"
#include "Clock.h"
#include "Alarm.h"

enClockStates u8StateMachineVal = enClock;
//static uint8_t u8StatusFlag = 0;
uint32_t Segundos=0;
uint32_t DeadlineAlarm = 0;
_Bool Alarm = 0;
uint8_t NewTime = 0;
uint8_t  Mode=0;


	void (*aSetUp[])(uint8_t) = {Clock_vfnSetUp, Alarm_vfnSetUp};
	void (*array[]) (void) = {Clock_vfnMain,Alarm_vfnMain};

int main(void) {

	UART0_vfnCallbackReg(UART0_Callback);
	I2C_vfnDriverInit();
	Clock_vfnInit();
	PIT_vfnCallbackReg(Seconds_vfnPlus);
	PIT_vfnDriverInit();
	Pit_vfnSetTime(Seconds);
	UART_DriverInt();
	PIT_vfnTimerEnable();


    while(1) {
    		array[Mode]();
    		if(Alarm && DeadlineAlarm == Segundos)
    		{
    			Mode = 1;
    			Alarm_vfnHandler();
    		}
    }
    return 0 ;
}

void Seconds_vfnPlus(void){
	Segundos++;
}
void UART0_Callback(uint_8 UARTVal){

		aSetUp[Mode](UARTVal);
}

void Reloj_ChangeScreen (void)
{
	Mode++;
	if(Mode == 2)
	{
		Mode = 0;
	}
	array[Mode]();
}

void Reloj_SetAlarm (uint32_t u32SnapAlarm)
{
	Alarm = 1;
	DeadlineAlarm = u32SnapAlarm;
}

void Reloj_StopAlarm (void)
{
	Alarm = 0;
}



