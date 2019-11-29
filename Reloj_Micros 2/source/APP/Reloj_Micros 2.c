
#include "MKL25Z4.h"
#include "Reloj_Micros 2.h"
#include "PIT.h"
#include "UART_DriverInt.h"
#include "I2CDRIVE.h"
#include "Clock.h"

enClockStates u8StateMachineVal = enClock;
//static uint8_t u8StatusFlag = 0;
uint32_t Segundos=0;
uint8_t NewTime = 0;
uint8_t  Mode=0;


	void (*aSetUp[])(uint8_t) = {Clock_vfnSetUp};

int main(void) {

	void (*array[]) (void) = {Clock_vfnMain};
	UART0_vfnCallbackReg(UART0_Callback);
	I2C_vfnDriverInit();
	Clock_vfnInit();
	PIT_vfnCallbackReg(Seconds_vfnPlus);
	PIT_vfnDriverInit();
	Pit_vfnSetTime(Seconds);
	UART_DriverInt();
	PIT_vfnTimerEnable();


    while(1) {
    	for (uint8_t i = 0; i < 1; i++)
    		array[i]();
    }
    return 0 ;
}

void Seconds_vfnPlus(void){
	Segundos++;
}
void UART0_Callback(uint_8 UARTVal){
	if(UARTVal=='W'){
		Mode++;
		if(Mode==4){
			Mode=0;
		}
		//PintarDislpay en posicionMod
	}
	else
	{
		aSetUp[Mode](UARTVal);
	}
}



