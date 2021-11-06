/*
 * ReceivePCData.h
 *
 *  Created on: 13/04/2019
 *      Author: cyh
 */

#ifndef COMMUNICATION_PCDATA_H_
#define COMMUNICATION_PCDATA_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"

#define u8 unsigned char

void Send_Eular(int16_t roll,int16_t pitch,int16_t yaw);
void Send_MOTO(int16_t PWM_MOTO1,int16_t PWM_MOTO2,int16_t PWM_MOTO3,int16_t PWM_MOTO4);
void Send_Acc(int16_t Acc_x,int16_t Axx_y,int16_t Acc_z);

void ANO_DT_Data_Receive_Prepare(u8 data);
static void ANO_DT_Send_Check(u8 head, u8 check_sum);
void ANO_DT_Data_Receive_Anl(u8 *data_buf,u8 num);
void PCData_Control(unsigned char input);

#endif /* COMMUNICATION_PCDATA_H_ */
