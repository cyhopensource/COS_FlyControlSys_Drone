/*
 * PID_control.h
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 */

#ifndef ALGORITHM_PID_CONTROL_H_
#define ALGORITHM_PID_CONTROL_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"


#define lowpass_filter  7.9577e-3    

float PID_Control(PID *PIDpara, PIDOut *PIDstatus, float expect_PID, float feedback_PID
                                , float PIDtime, float Integrallimiter,float LowpassFilter);

void Attitude_control(float PitchCalibration,float RollCalibration,float YawCalibration);
void Height_control(float HeightCalibration);
void Calculate_Thrust();
void Position_control(unsigned char Data_flag,float Climb,float Decline);
void Safety_Protection(void);
void Throttle_Angle_Compensate(void);

#endif /* ALGORITHM_PID_CONTROL_H_ */
