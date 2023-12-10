/*
 * MADC-prv.h
 *
 *  Created on: Jul 28, 2023
 *      Author: userH
 */

#ifndef MCAL_ADC_MADC_PRV_H_
#define MCAL_ADC_MADC_PRV_H_


#define ENABLE		1
#define DISABLE		0


#define AVCC			1
#define INTERNAL_REF	2
#define AREF			3

#define ADC_PS_2		0b001
#define ADC_PS_4		0b010
#define ADC_PS_8		0b011



#define REFS1     7
#define REFS0	  6
#define ADLAR	  5
#define ADATE	  5
#define ADIE	  3
#define ADIF	  4
#define ADEN	  7
#define ADSC	  6

#define CHANNEL_00		0
#define CHANNEL_01		1
#define CHANNEL_02		2
#define CHANNEL_03		3
#define CHANNEL_04		4
#define CHANNEL_05		5
#define CHANNEL_06		6
#define CHANNEL_07		7


#define ADMUX		*((volatile u8*)(0x27))
#define ADCSRA		*((volatile u8*)(0x26))
#define ADCL		*((volatile u8*)(0x24))
#define ADCH		*((volatile u8*)(0x25))

#define ADC			*((volatile u16*)(0x24))

#define SFIOR		*((volatile u8*)(0x50))

#endif /* MCAL_ADC_MADC_PRV_H_ */
