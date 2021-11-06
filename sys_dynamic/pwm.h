/*
 * pwm.h
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 */

#ifndef SYS_DYNAMIC_PWM_H_
#define SYS_DYNAMIC_PWM_H_

#include "F28x_Project.h"

void PWM_OUTPUT(unsigned int Motor1,    
                unsigned int Motor2,
                unsigned int Motor3,
                unsigned int Motor4);
void InitEPwm1Example();
void InitEPwm2Example();
void C28x_BSP_Epwm_Init();


#endif /* SYS_DYNAMIC_PWM_H_ */
