/*
 * ADC_prg.c
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "MADC-int.h"
#include "MADC-prv.h"
#include "MADC-cfg.h"



void (*ADC_Callback)(void);

void (*ADC_Callback_2)(u16 A_u16ADC_Data);
u16*  G_pu16ADC_Data;
FlagStatus_t xAdcFlag = ADC_NOT_COMPLETE ;

void MADC_vInit(void)
{
	/* 1- Reference voltage selection */
#if ADC_REF_VOLT==AVCC
	CLR_BIT(ADMUX, REFS1);
	SET_BIT(ADMUX, REFS0);
#elif ADC_REF_VOLT==INTERNAL_REF
	CLR_BIT(ADMUX, REFS1);
	CLR_BIT(ADMUX, REFS0);
#elif ADC_REF_VOLT==AREF
	SET_BIT(ADMUX, REFS1);
	SET_BIT(ADMUX, REFS0);
#else
#error "Please select correct refence voltage"
#endif

	/* 2- Data Adjustment direction  */
	CLR_BIT(ADMUX, ADLAR);
	/* 3- Select Prescaler Bits    */
	ADCSRA = (ADCSRA & 0xF8) | (ADC_PRESCALER) ;
	/* 4- Auto trigger Enable     */
	/*  4a- Select Auto trigger source  */
	CLR_BIT(ADCSRA, ADATE);
	/* 5- Interrupt Enable/disable    */
#if ADC_INTERRUPT_ENABLE==DISABLE
	CLR_BIT(ADCSRA, ADIE);
#elif ADC_INTERRUPT_ENABLE==ENABLE
	SET_BIT(ADCSRA, ADIE);
#endif
	/* 6- Enable ADC peripheral   */
	SET_BIT(ADCSRA, ADEN);
}

u16  MADC_u16AnalogRead(u8 A_u8ChannelNo )
{
	/* 1- Select Channel   */
	ADMUX = (ADMUX & 0xE0) | (A_u8ChannelNo & 0x07) ;
	/* 2- Start Conversion */
	SET_BIT(ADCSRA, ADSC);
	/* 3- Poll on Flag     */
	while( GET_BIT(ADCSRA, ADIF) != 1 ){}
	/* 4- Clear Flag       */
	SET_BIT(ADCSRA, ADIF);
	/* 5- return ADC Data  */
	return ADC;
}


void MADC_vStartConversion(u8 A_u8ChannelNo)
{
	/* 1- Select Channel   */
	ADMUX = (ADMUX & 0xE0) | (A_u8ChannelNo & 0x07) ;
	/* 2- Start Conversion */
	SET_BIT(ADCSRA, ADSC);
}

u16   MADC_u16GetADCData(void)
{
	/* 5- return ADC Data  */
	return ADC;
}

FlagStatus_t    MADC_xGetFlagStatus(void)
{

	if(GET_BIT(ADCSRA, ADIF) == 1)
	{
		xAdcFlag = ADC_COMPLETE ;
	}
	return xAdcFlag ;
}

void MADC_vSetCallback( void (*A_fptr)(void)  )
{
	ADC_Callback = A_fptr;
}

void MADC_vStartADCConversion_Asynch(u8 A_u8ChannelNo   ,
									 u16* A_u16pu16ADCData ,
									 void (*A_fptr)(void) )
{
	/* 1- set Call back function pointer */
	ADC_Callback = A_fptr ;
	/* 2- set ADC data pointer */
	G_pu16ADC_Data = A_u16pu16ADCData ;

	/* 3- Select Channel   */
		ADMUX = (ADMUX & 0xE0) | (A_u8ChannelNo & 0x07) ;
	/* 4- Start Conversion */
	SET_BIT(ADCSRA, ADSC);
}




/* ADC_ISR */
void __vector_16(void)  __attribute__((signal));
void __vector_16(void)
{

	if(G_pu16ADC_Data != NULL)
	{
		*G_pu16ADC_Data = ADC ;
	}

	if(ADC_Callback != NULL)
	{
		ADC_Callback();

	}
}


