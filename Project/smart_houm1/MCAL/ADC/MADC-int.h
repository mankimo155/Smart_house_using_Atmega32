/*
 * MADC-int.h
 *
 *  Created on: Jul 24, 2023
 *      Author: userH
 */

#ifndef MCAL_ADC_MADC_INT_H_
#define MCAL_ADC_MADC_INT_H_



typedef enum
{
	ADC_COMPLETE,
	ADC_NOT_COMPLETE
}FlagStatus_t;


void MADC_vInit(void);
u16  MADC_u16AnalogRead(u8 A_u8ChannelNo );

/* Interrupt based APIs */
void MADC_vStartConversion(u8 A_u8ChannelNo);
u16   MADC_u16GetADCData(void);
void MADC_vSetCallback( void (*A_fptr)(void)  );

void MADC_vSelectChannel(u8 A_u8ChannelNo) ;

/* Alternative method :   */
void MADC_vStartADCConversion_Asynch(u8 A_u8ChannelNo   ,
									 u16* A_pu16ADCData ,
									 void (*A_fptr)(void) );


FlagStatus_t    MADC_xGetFlagStatus(void);


#endif /* MCAL_ADC_MADC_INT_H_ */
