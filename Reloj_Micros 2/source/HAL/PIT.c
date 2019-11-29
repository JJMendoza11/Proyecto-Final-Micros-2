/*
 * PIT.c
 *
 *  Created on: 28/11/2019
 *      Author: Poncho
 */
#include "PIT.h"
#include "MKL25Z4.h"

void(*fnCallBack1)(void);

void PIT_vfnCallbackReg(void(*fnCall1)(void)){
	fnCallBack1=fnCall1;
}
void PIT_vfnDriverInit(void){
	NVIC->ISER[0]|=(1<<PIT_IRQn);
	SIM->SCGC6|=SIM_SCGC6_PIT_MASK;
	PIT->MCR&=~(PIT_MCR_FRZ_MASK);
	PIT->MCR&=~(PIT_MCR_MDIS_MASK);
	PIT->CHANNEL[0].TCTRL|=PIT_TCTRL_TIE_MASK;
}

void PIT_vfnTimerEnable(void){
	PIT->CHANNEL[0].TCTRL|=PIT_TCTRL_TEN_MASK;
}
void PIT_vfnTimerDisable(void){
	PIT->CHANNEL[0].TCTRL&=~(PIT_TCTRL_TEN_MASK);
}

void PIT_IRQ(void){
	(*fnCallBack1)();
	PIT->CHANNEL[0].TFLG|=(1<<31);

}

void Pit_vfnSetTime(uint16_t Time_in_ms)
{
	uint32_t u32LDVal = 10500 * Time_in_ms;
	PIT->CHANNEL[0].LDVAL = u32LDVal;
}

