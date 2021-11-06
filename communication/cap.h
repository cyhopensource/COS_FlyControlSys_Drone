/*
 * cap.h
 *
 *  Created on: 28/03/2019
 *      Author: cyh
 *
 */

#ifndef COMMUNICATION_CAP_H_
#define COMMUNICATION_CAP_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"

void Cap_init(void);

void InitECapture1(void);
void InitECapture2(void);
void InitECapture3(void);
void InitECapture4(void);
void InitECapture5(void);
void InitECapture6(void);
void InitEPwmTimer(void);

__interrupt void ecap1_isr(void);
__interrupt void ecap2_isr(void);
__interrupt void ecap3_isr(void);
__interrupt void ecap4_isr(void);
__interrupt void ecap5_isr(void);
__interrupt void ecap6_isr(void);

#endif /* COMMUNICATION_CAP_H_ */
