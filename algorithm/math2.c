/*
 * math.c
 *
 *  Created on: 03/04/2019
 *      Author: cyh
 *
 *
 */

#include "F28x_Project.h"
#include "math.h"
#include "math2.h"


float_union FloatToHex;

float Constraint_f(float a , float lower , float upper)   
{
  if (a >= upper)
    a = upper;
  else if (a <= lower)
    a = lower;
  return (a);
}


float Limits_data(float LimitsData,float LimitsUp,float LimitsDown)
{
    if(LimitsData > LimitsUp)
    {
        LimitsData = LimitsUp;
    }
    if(LimitsData < LimitsDown)
    {
        LimitsData = LimitsDown;
    }
    return LimitsData;
}

void FloatToUnsignedchar(unsigned char sequence,float Originalvalue,unsigned char *dataPC)
{
    FloatToHex.fv = Originalvalue;
    dataPC[sequence] = (FloatToHex.sv[0] & 0x00ff);
    dataPC[sequence+1] = ((FloatToHex.sv[0]>> 8) & 0x00ff);
    dataPC[sequence+2] = (FloatToHex.sv[1] & 0x00ff);
    dataPC[sequence+3] = ((FloatToHex.sv[1] >> 8) & 0x00ff);
}

float ABS(float data)
{
    if(data<0)
        data = -data;
    else
        data = data;
    return data;
}

float MAX(float data1,float data2)
{
    float Max =0 ;
    if(data1>=data2)
        Max =data1;
    else
        Max =data2;
    return Max;
}

float invSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i>>1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

