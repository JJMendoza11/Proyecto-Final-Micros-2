
#include "MKL25Z4.h"
#include "Reloj_Micros 2.h"
#include "PIT.h"
#include "UART_DriverInt.h"
#include "I2CDRIVE.h"

enClockStates u8StateMachineVal = enClock;
//static uint8_t u8StatusFlag = 0;
uint32_t Segundos=0;
uint8_t  Mode=0;
uint8_t Time[3]={};


int main(void) {
	/*void (*array[]) (void) = {Clock_vfnMasterClock, Chrono_vfnInit};*/
	UART0_vfnCallbackReg(UART0_Callback);
	UART_DriverInt();
	I2C_vfnDriverInit();
	//Clock_vfnInit();
	PIT_vfnCallbackReg(Seconds_vfnPlus);
	PIT_vfnDriverInit();
	Pit_vfnSetTime(Seconds);
	PIT_vfnTimerEnable();


    while(1) {
    }
    return 0 ;
}

void Seconds_vfnPlus(void){
	Segundos++;
}
void UART0_Callback(uint_8 UARTVal){
	if(UARTVal==ModeUart){
		Mode++;
		if(Mode==4){
					Mode=0;
				}
		//PintarDislpay en posicionMod
	}
}

void Decoder(void){
	Time[0]=Segundos%60;
	Time[1]=(Segundos%3600)/60;
	Time[2]=(Segundos%216000)/3600;
	if(Time[2]==24){
		Time[2]=0;
	}
}
