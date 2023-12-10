/*
 * TIMER-int.h
 *
 *  Created on: Aug 3, 2023
 *      Author: userH
 */

#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

void MTIMERS_vInit(void);

void MTIMERS_vSetPreloadValue(/* Timer ID ?*/ u16 A_u16Preload);

void MTIMERS_vSetInterval_Asynch(u16 A_u16IntervalCounts, void (*A_fptr)(void));

void MTIMERS_vStartTimer(/* Timer ID ?*/) ;

void MTIMERS_vStopTimer(/* Timer ID ?*/) ;


#endif /* MCAL_TIMER_TIMER_INT_H_ */
