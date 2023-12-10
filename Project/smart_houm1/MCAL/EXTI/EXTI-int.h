/*
 * EXTI-int.h
 *
 *  Created on: Jul 23, 2023
 *      Author: userH
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_



void MEXTI_vEnableInterrupt(u8 A_u8ExtiLineNo);
void MEXTI_vDisableInterrupt(u8 A_u8ExtiLineNo);
void MEXTI_vSetSenseControl(u8 A_u8ExtiLineNo, u8 A_u8SenseCtrl);


#endif /* MCAL_EXTI_EXTI_INT_H_ */
