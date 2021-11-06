/*
 * ekf.h
 *
 *  Created on: 2019Äê4ÔÂ1ÈÕ
 *      Author: cyh
 */

#ifndef ALGORITHM_FILTER_H_
#define ALGORITHM_FILTER_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"

typedef struct
{
 float Input_Butter[3];
 float Output_Butter[3];
}Butter_BufferData;

typedef struct
{
  float a[3];
  float b[3];
}Butter_Parameter;

float Median_Filter(int FilterData,Uint16 Length,int *FilterArray);
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter);
float Average_Filter(float FilterData,Uint16 Length,float *FilterArray);
void POS_KalmanFilter(KalmanFilter *KalmanFilter_Input,float Position,float Acceleration);
void OpticalFlow_Estimation(float flow_x,float flow_y,float Accx,float Accy);


#endif /* ALGORITHM_FILTER_H_ */
