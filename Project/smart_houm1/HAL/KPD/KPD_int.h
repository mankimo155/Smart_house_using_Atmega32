/*
 * KPD_int.h
 *
 *  Created on: Jul 14, 2023
 *      Author: userH
 */

#ifndef HAL_KPD_KPD_INT_H_
#define HAL_KPD_KPD_INT_H_

#define KPD_PORT   DIO_PORTC


void HKPD_vInit(void);
u8   HKPD_u8GetPressedKey(void);

#endif /* HAL_KPD_KPD_INT_H_ */
