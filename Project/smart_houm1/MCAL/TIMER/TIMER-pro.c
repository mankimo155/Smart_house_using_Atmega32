/*

 * TIMER-pro.c
 *
 *  Created on: Aug 3, 2023
 *      Author: userH
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER-int.h"
#include "TIMER-prv.h"
#include "TIMER-cfg.h"


void (*G_TIM0_OVF_Callback)(void);
u32  G_u32IntervalCount;


void MTIMERS_vInit(void)
{
	/**
	 * Mode: Normal Overflow
	 * Interrupt: enable OVerflow intterupt
	 * Prescaler: No CLOCK -> timer stopped
	 */

	TCCR0 = 0b00000000 ;
	SET_BIT(TIMSK, 0) ; //TOIE0



}

void MTIMERS_vSetPreloadValue(/* Timer ID ?*/ u16 A_u16Preload)
{
	TCNT0 = A_u16Preload ;
}

void MTIMERS_vSetInterval_Asynch(u16 A_u16IntervalCounts, void (*A_fptr)(void))
{
	G_u32IntervalCount = A_u16IntervalCounts ;
	G_TIM0_OVF_Callback = A_fptr ;
	/*  start timer */
	MTIMERS_vStartTimer();

}

void MTIMERS_vStartTimer(/* Timer ID ?*/ )
{
	TCCR0 = (TCCR0 & 0xF8) | (0b010) ;
}

void MTIMERS_vStopTimer(/* Timer ID ?*/)
{
	TCCR0 = (TCCR0 & 0xF8) | (0b000) ;
}


void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{
	static u32 LS_u32Counter = 0;

	LS_u32Counter++ ;

	if(LS_u32Counter == G_u32IntervalCount)
	{
		if(G_TIM0_OVF_Callback != NULL)
		{
			G_TIM0_OVF_Callback();
			LS_u32Counter = 0;
		}
	}
}











