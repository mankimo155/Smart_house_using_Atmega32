/*
 * main.c
 *
 *  Created on: Aug 4, 2023
 *      Author: userH
 */
#include "../LIB/STD_TYPES.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KPD/KPD_int.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/ADC/MADC-int.h"
#include "../MCAL/ADC/MADC-prv.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../HAL/DC-MOTOR/DCM-int.h"
#include "../MCAL/TIMER/TIMER-int.h"
#include <util/delay.h>

#define Temp         1
#define DC_mot       2
#define LDR          3
#define ON           1
#define OFF          2
#define back_to_min  3
#define Close_DCmot  2
#define Close_LDE    1
#define Close_Buzzer 3


void vSysteOption(void);
void vSysteFrontEnd(void);

volatile u8 G_u8TimerFlag = 0 ;
volatile u16 G_u16Adc_Value = 0 ;


void Timer_Isr(void)
{
	switch(G_u8TimerFlag)
	{
	case Close_LDE  :
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN3,DIO_LOW);
		MTIMERS_vStopTimer();
		break;
	case Close_DCmot :
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN2,DIO_LOW);
		MTIMERS_vStopTimer();
		break;
	case Close_Buzzer :
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN4,DIO_LOW);
			MTIMERS_vStopTimer();
			break;

	}

}


void Adc_Isr(void)
{
	HLCD_vClearDisplay();
	G_u16Adc_Value = MADC_u16GetADCData();
	G_u16Adc_Value = (G_u16Adc_Value * 500)/1024;
	HLCD_vPrintString("Temp =");
	HLCD_vPrintNumber(G_u16Adc_Value);
	if(G_u16Adc_Value > 30)
	{
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN4,DIO_HIGH);
	}

	G_u8TimerFlag = Close_Buzzer ;
	_delay_ms(2000);
	MTIMERS_vSetInterval_Asynch(7000,Timer_Isr);
	HLCD_vClearDisplay();
	vSysteFrontEnd();


}

void Adc_Isr2(void)
{
	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN3,DIO_HIGH);
	G_u16Adc_Value=MADC_u16GetADCData();
	G_u16Adc_Value = (G_u16Adc_Value * 500)/1024;
	HLCD_vClearDisplay();
	HLCD_vPrintString("LDR_Value = ");
	HLCD_vPrintNumber(G_u16Adc_Value);
	_delay_ms(2000);
	G_u8TimerFlag = Close_LDE ;
	MTIMERS_vSetInterval_Asynch(7000,Timer_Isr);
	HLCD_vClearDisplay();
	vSysteFrontEnd();

}




int main(void)
{
	MGIE_vEnableGlobalInterrupt();
	MADC_vInit();
	HLCD_vInit();
	MTIMERS_vInit();
	HKPD_vInit();
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN4,DIO_OUTPUT);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN3,DIO_OUTPUT);
	vSysteFrontEnd();

	while(1)
	{
		vSysteOption();
	}

	return 0;

}


void vSysteOption(void)
{
	u8 L_u8flag =0;
	u8 L_u8Flag1 =0;
	u8 L_u8DO = 0 ;
	switch(HKPD_u8GetPressedKey())
	{
	case Temp:
		MADC_vSetCallback(Adc_Isr);
		MADC_vStartConversion(CHANNEL_00);
		L_u8Flag1= 1;
		break;
	case DC_mot:
		HLCD_vClearDisplay();
		HLCD_vPrintString("1:ON");
		HLCD_vGoToXY(0,7);
		HLCD_vPrintString("2:OFF");
		HLCD_vGoToXY(1,0);
		HLCD_vPrintString("3:back to min");
		while(L_u8flag==0)
		{
			L_u8DO = HKPD_u8GetPressedKey();
			if(L_u8DO==ON)
			{
				MDIO_vSetPinVal(DIO_PORTA,DIO_PIN2,DIO_HIGH);
				HLCD_vClearDisplay();
				vSysteFrontEnd();
				L_u8flag = 1 ;
			}
			else if(L_u8DO==OFF)
			{
				G_u8TimerFlag = Close_DCmot ;
				MTIMERS_vSetInterval_Asynch(100,Timer_Isr);
				HLCD_vClearDisplay();
				vSysteFrontEnd();
				L_u8flag=1;
			}
			else if(L_u8DO== back_to_min)
			{
				HLCD_vClearDisplay();
				vSysteFrontEnd();
				L_u8flag = 1 ;
			}

		}
		break;

	case LDR:
		MADC_vSetCallback(Adc_Isr2);
		MADC_vStartConversion(CHANNEL_01);
		break;
	}

}

void vSysteFrontEnd(void)
{
	HLCD_vClearDisplay();
	HLCD_vPrintString("pleas chose");
	HLCD_vGoToXY(1,5);
	HLCD_vPrintString("option");
	_delay_ms(1000);
	HLCD_vClearDisplay();
	HLCD_vPrintString("1:temp");
	HLCD_vGoToXY(0,7);
	HLCD_vPrintString("2:DC_mot");
	HLCD_vGoToXY(1,0);
	HLCD_vPrintString("3:LDR");
}




