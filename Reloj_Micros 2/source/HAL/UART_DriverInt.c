/*
 * UART_DriverInt.c
 *
 *  Created on: 11/07/2019
 *      Author: Poncho
 */
#include "MKL25Z4.h"
#include "UART_DriverInt.h"
//#include "core_cm0plus.h"
volatile unsigned char UARTRxData;
void UART_DriverInt(void){
	unsigned char SBR;
	SBR=21000000/((16)*UART_Baudrate);               // {9600=21Mhz/((OSR+1)SBR)}  {SBR=21Mhz/((OSR+1)9600}
	SIM->SOPT2|=SIM_SOPT2_UART0SRC(1);
	SIM->SCGC4|=SIM_SCGC4_UART0_MASK;
	UART0->BDH|=UART_BDH_SBNS_MASK;         //Stop Bit Number Select
	UART0->BDH|=(SBR>>8 & 0X1F);            //Baud Rate Modulo Divisor (Se ingresa el bit 12,11,10,9,8)
	UART0->BDL=(SBR&0xFF);                  //Baud Rate Modulo Divisor(Se ingresan el bit 7,6,5,4,3,2,1,0)
	UART0->C1=0;
	                                        //Loop Mode Select
                                        	//9-Bit or 8-Bit Mode Select
	UART0->C2|=UART_C2_RIE_MASK;
	NVIC->ISER[0]|=(1<<UART0_IRQn);
	UART0->C4|=UART0_C4_OSR(15);

	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[1]=PORT_PCR_MUX(2); //RX
	PORTA->PCR[2]=PORT_PCR_MUX(2); //TX
	/*SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[1]=PORT_PCR_MUX(2); //RX
	PORTA->PCR[2]=PORT_PCR_MUX(2); //TX*/
	UART0->C2|=UART_C2_TE_MASK;
	UART0->C2|=UART_C2_RE_MASK;

	                                       //Receiver Overrun Flag (CHECAR SI NO JALA EL UART) Y LOS SIGUIENTES
}
uint_8 UART_bfnSend (uint_8 bTxData){
	if(UART0->S1&UART_S1_TDRE_MASK){
		UART0->D=bTxData;
		return SUCCESS;
	}
	else{
	return ERROR;
	}
}

void(*fnCallBack)(uint_8 UART0_Val);

void UART0_vfnCallbackReg(void (*fnCall)(uint_8 )){
	fnCallBack=fnCall;
}
void UART0_IRQ(void){
	(*fnCallBack)(UART0->D);
}

