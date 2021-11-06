/*
 * sci.h
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 */

#ifndef COMMUNICATION_SCI_H_
#define COMMUNICATION_SCI_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"

void Sci_Init();
void Scib_Init();
void Scic_Init();
void scic_msg(unsigned char * msg);
void scib_msg(unsigned char * msg);

void Uart_Put_Buf(unsigned char *data_to_send,unsigned char _cnt);
void UARTCharPut(unsigned char ch);

__interrupt void scicRxFifoIsr(void);
__interrupt void scibRxFifoIsr(void);



#endif /* COMMUNICATION_SCI_H_ */
