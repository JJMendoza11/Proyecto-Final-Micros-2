/*
 * UART_DriverInt.h
 *
 *  Created on: 11/07/2019
 *      Author: Poncho
*/
#ifndef UART_DRIVERINT_H_
#define UART_DRIVERINT_H_

typedef unsigned char uint_8;
#define UART_Baudrate     9600
#define ERROR             0
#define SUCCESS           1
#define UART0_IRQ     UART0_IRQHandler

	void UART0_Callback(uint_8 UARTVal);
	void UART_DriverInt(void);
	uint_8 UART_bfnSend (uint_8 bTxData);
	uint_8 UART_bfnRead (uint_8 *bpRxData);
	void UART0_IRQ(void);
	void UART0_vfnCallbackReg(void (*fnCall)(uint_8 UART0_Val));

#endif /* UART_DRIVERINT_H_ */
