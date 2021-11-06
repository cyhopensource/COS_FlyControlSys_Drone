/*
 * imu.h
 *
 *  Created on: 02/04/2019
 *      Author: cyh
 */

#ifndef ALGORITHM_IMU_H_
#define ALGORITHM_IMU_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"
#include "filter.h"



float safe_asin(float v);
void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void IMU_getValues(float *values); 
void IMU_getInfo();
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
void Set_Cutoff_Frequency(float sample_frequent, float cutoff_frequent,Butter_Parameter *LPF);

void Quadrotor_Control();

#endif /* ALGORITHM_IMU_H_ */
