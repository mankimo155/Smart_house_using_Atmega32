/*
 * DCM-pro.c
 *
 *  Created on: Jul 21, 2023
 *      Author: userH
 */
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "DCM-int.h"
#include "DCM-con.h"

void HDCM_vInit2(u8 A_DCM_PORT,u8 A_DCM_PIN_NO)
{
	switch(A_DCM_PORT)
	{
	case DIO_PORTA:
		MDIO_vSetPinDir(DIO_PORTA,A_DCM_PIN_NO,DIO_OUTPUT);
		break;
	case DIO_PORTB:
		MDIO_vSetPinDir(DIO_PORTB,A_DCM_PIN_NO,DIO_OUTPUT);
			break;
	case DIO_PORTC:
		MDIO_vSetPinDir(DIO_PORTC,A_DCM_PIN_NO,DIO_OUTPUT);
			break;
	case DIO_PORTD:
		MDIO_vSetPinDir(DIO_PORTD,A_DCM_PIN_NO,DIO_OUTPUT);
			break;
	}
}
void HDCM_vInit(void)
{
	MDIO_vSetPinDir(DCM_PORT,DCM_PIN0,DIO_OUTPUT);
	MDIO_vSetPinDir(DCM_PORT,DCM_PIN1,DIO_OUTPUT);
}

void HDCM_vRotateCW(void)
{
	MDIO_vSetPinVal(DCM_PORT,DCM_PIN0,DIO_HIGH);
	MDIO_vSetPinVal(DCM_PORT,DCM_PIN1,DIO_LOW);
}

void HDCM_vRotateCCW(void)
{
	MDIO_vSetPinVal(DCM_PORT,DCM_PIN0,DIO_LOW);
	MDIO_vSetPinVal(DCM_PORT,DCM_PIN1,DIO_HIGH);

}

void HDCM_vStop(void)
{
	MDIO_vSetPinVal(DCM_PORT,DCM_PIN0,DIO_LOW);
	MDIO_vSetPinVal(DCM_PORT,DCM_PIN1,DIO_LOW);
}
