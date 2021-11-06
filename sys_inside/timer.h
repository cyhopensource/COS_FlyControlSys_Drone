/*
 * timer.h
 *
 *  Created on: 06/04/2019
 *      Author: cyh
 */

#ifndef SYS_INSIDE_TIMER_H_
#define SYS_INSIDE_TIMER_H_

#include "F28x_Project.h"

void Timer_Init(void);

void Timer_Control(unsigned char sta);

__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);

#endif /* SYS_INSIDE_TIMER_H_ */
