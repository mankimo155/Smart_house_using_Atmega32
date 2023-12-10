/*
 * DCM-int.h
 *
 *  Created on: Jul 21, 2023
 *      Author: userH
 */

#ifndef HAL_DC_MOTOR_DCM_INT_H_
#define HAL_DC_MOTOR_DCM_INT_H_

void HDCM_vInit2(u8 A_DCM_PORT,u8 A_DCM_PIN_NO);

void HDCM_vInit(void);

void HDCM_vRotateCW(void);

void HDCM_vRotateCCW(void);

void HDCM_vStop(void);



#endif /* HAL_DC_MOTOR_DCM_INT_H_ */
