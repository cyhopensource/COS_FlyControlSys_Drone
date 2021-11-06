/*
 * fly_sys.h
 *
 *  Created on: 01/04/2019
 *      Author: cyh
 *
 */

#ifndef SYS_DYNAMIC_FLY_SYS_H_
#define SYS_DYNAMIC_FLY_SYS_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"   

unsigned char Data(void);
unsigned char Fly(void);

unsigned char Data_Handle(void);
unsigned char Start_up(void);
unsigned char Data_Combine(void);
unsigned char Fly_Up(void);
unsigned char SendData(void);
unsigned char ReceiveData(void);
unsigned char Control_Data();

void Test_Mission(void);
void Hardware_Init(void);
void System_all(void);
void End_Mission(void);

void Process_PCData(void);
void Fixed_Mission(void);
void QuadrotorPara_Init(void);

#endif /* SYS_DYNAMIC_FLY_SYS_H_ */
