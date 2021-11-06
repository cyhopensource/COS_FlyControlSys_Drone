/*
 * math2.h
 *
 *  Created on: 05/04/2019
 *      Author: cyh
 */

#ifndef ALGORITHM_MATH2_H_
#define ALGORITHM_MATH2_H_

#ifndef ALGORITHM_MATH_H_
#define ALGORITHM_MATH_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"



float Constraint_f(float a , float lower , float upper);

float Limits_data(float LimitsData,float LimitsUp,float LimitsDown);

void FloatToUnsignedchar(unsigned char sequence,float Originalvalue,unsigned char *dataPC);

float invSqrt(float x);

float ABS(float data);

float MAX(float data1,float data2);

#endif /* ALGORITHM_MATH_H_ */



#endif /* ALGORITHM_MATH2_H_ */
