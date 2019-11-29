/*
 * PIT.h
 *
 *  Created on: 28/11/2019
 *      Author: Poncho
 */

#ifndef PIT_H_
#define PIT_H_

#define PIT_IRQ   PIT_DriverIRQHandler


   void PIT_vfnCallbackReg(void(*fnCall)(void));
   void PIT_vfnDriverInit(void);
   void PIT_vfnTimerEnable(void);
   void PIT_vfnTimerDisable(void);
   void PIT_IRQ(void);
   void Pit_vfnSetTime(unsigned short Time_in_ms);
   void Seconds_vfnPlus(void);


#endif /* PIT_H_ */
