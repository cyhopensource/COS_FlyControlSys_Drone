/*
 * ekf.c
 *
 *  Created on: 01/04/2019
 *      Author: cyh
 *  2019.4.2 setup the filter.
 */

#include "algorithm/filter.h"
#include "F28x_Project.h"
#include "filter.h"

extern DroneRTInfo RT_Info;    //realtime data

#define w (0.0005f)
#define v (0.06f)

/*
 *
 *  KalmanFilter inti para
 *
 */

//const float KalmanFilter_Unit[3][7] =
//{     //Q_Position      Q_Velocity      Q_Bias         R_Position     AxisC_0     AxisPP        Merge_t
//     {    0.01,           1.0,          0.045,          0.05,           1,         1.0,          0.008    },//xaxis
//     {    0.01,           1.0,          0.045,          0.05,           1,         1.0,          0.008    },//yaxis
//     {    0.04,           0.01,          0.008,          0.01,           1,         1.0,          0.008    },//zaxis
//};

const float KalmanFilter_Unit[3][7] =
{  //Q_Position      Q_Velocity      Q_Bias         R_Position     AxisC_0    AxisPP        Merge_t
     {   0.01,            0.2,         0.045,          0.04,           1,         1.0,         0.005   },//xaxis
     {   0.01,            0.2,         0.045,          0.04,           1,         1.0,         0.005   },//yaxis
     {   0.08,            0.01,         0.01,          0.01,           1,         1.0,         0.005  },//zaxis
};

MAT_3X3_TYPE F;
MAT_3X3_TYPE L;
MAT_3X3_TYPE K;

//  median filter
float Median_Filter(int FilterData,Uint16 Length,int *FilterArray)
{
    Uint16 i = 0,j = 0;
    int temp = 0;
    int sum = 0;
    float AverageValue = 0;
    FilterArray[Length - 1] = FilterData;
    for(i=0;i<Length-1;i++)
    {
        FilterArray[i]=FilterArray[i+1];
    }

    for(i = 0 ; i < Length-1 ; i++)
    {
        for(j = 0 ; j < Length-1-i; j++)
        {
            if(FilterArray[j] > FilterArray[j+1] )
            {
                temp = FilterArray[j];
                FilterArray[j] =  FilterArray[j+1];
                FilterArray[j+1] = temp;
            }
        }
    }
    if(Length%2 == 0){
        for(i = Length/2-2;i < Length/2+2;i++){
            sum += FilterArray[i];
        }
        AverageValue = sum/4;
    }
    else{
        for(i = Length/2-1;i < Length/2+2;i++){
            sum += FilterArray[i];
        }
        AverageValue = sum/3;
    }
    return AverageValue;
}

// 2 order butterworth
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
{

  Buffer->Input_Butter[2]=curr_input;

  Buffer->Output_Butter[2]=
    Parameter->b[0] * Buffer->Input_Butter[2]
      +Parameter->b[1] * Buffer->Input_Butter[1]
        +Parameter->b[2] * Buffer->Input_Butter[0]
          -Parameter->a[1] * Buffer->Output_Butter[1]
            -Parameter->a[2] * Buffer->Output_Butter[0];
  /* x(n)  */
  Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
  Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
  /* y(n)  */
  Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
  Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
  return Buffer->Output_Butter[2];
}

// average filter
float Average_Filter(float FilterData,Uint16 Length,float *FilterArray)
{
    float AverageValue = 0;
    int i;
    for(i=0;i<Length-1;i++)
    {
        FilterArray[i]=FilterArray[i+1];
    }
    FilterArray[Length - 1] = FilterData;
    for(i=0;i<Length;i++)
    {
        AverageValue += FilterArray[i];
    }
    AverageValue /= Length;
    return AverageValue;
}


void KalmanFilter_Init(KalmanFilter *XAXIS,KalmanFilter *YAXIS,KalmanFilter *ZAXIS){

    XAXIS->Q_Position = KalmanFilter_Unit[0][0];
    XAXIS->Q_Velocity = KalmanFilter_Unit[0][1];
    XAXIS->Q_Bias = KalmanFilter_Unit[0][2];
    XAXIS->R_Position = KalmanFilter_Unit[0][3];
    XAXIS->AxisC_0 = KalmanFilter_Unit[0][4];
    XAXIS->AxisPP[0][0] = KalmanFilter_Unit[0][5];
    XAXIS->AxisPP[1][1] = KalmanFilter_Unit[0][5];
    XAXIS->AxisPP[2][2] = KalmanFilter_Unit[0][5];
    XAXIS->Merge_t = KalmanFilter_Unit[0][6];

    YAXIS->Q_Position = KalmanFilter_Unit[1][0];
    YAXIS->Q_Velocity = KalmanFilter_Unit[1][1];
    YAXIS->Q_Bias = KalmanFilter_Unit[1][2];
    YAXIS->R_Position = KalmanFilter_Unit[1][3];
    YAXIS->AxisC_0 = KalmanFilter_Unit[1][4];
    YAXIS->AxisPP[0][0] = KalmanFilter_Unit[1][5];
    YAXIS->AxisPP[1][1] = KalmanFilter_Unit[1][5];
    YAXIS->AxisPP[2][2] = KalmanFilter_Unit[1][5];
    YAXIS->Merge_t = KalmanFilter_Unit[1][6];

    ZAXIS->Q_Position = KalmanFilter_Unit[2][0];
    ZAXIS->Q_Velocity = KalmanFilter_Unit[2][1];
    ZAXIS->Q_Bias = KalmanFilter_Unit[2][2];
    ZAXIS->R_Position = KalmanFilter_Unit[2][3];
    ZAXIS->AxisC_0 = KalmanFilter_Unit[2][4];
    ZAXIS->AxisPP[0][0] = KalmanFilter_Unit[2][5];
    ZAXIS->AxisPP[1][1] = KalmanFilter_Unit[2][5];
    ZAXIS->AxisPP[2][2] = KalmanFilter_Unit[2][5];
    ZAXIS->Merge_t = KalmanFilter_Unit[2][6];
}

// Kalman filter
void POS_KalmanFilter(KalmanFilter *KalmanFilter_Input,float Position,float Acceleration)
{
    //v(k+1) = v(k)+[a(k)-bias(k)]*dt
    KalmanFilter_Input->Axis_Vel +=(Acceleration - KalmanFilter_Input->Axis_Bias)*KalmanFilter_Input->Merge_t;
    //Height(k+1) = Height(k) + 1/2[a(k)-bias(k)]dt^2 + v(k)dt
    KalmanFilter_Input->Axis_Pos +=(Acceleration - KalmanFilter_Input->Axis_Bias)*(KalmanFilter_Input->Merge_t)
                   *(KalmanFilter_Input->Merge_t)/2 + KalmanFilter_Input->Axis_Vel*KalmanFilter_Input->Merge_t;

    KalmanFilter_Input->AxisPdot[0] = KalmanFilter_Input->Q_Position+KalmanFilter_Input->AxisPP[0][1]+KalmanFilter_Input->AxisPP[1][0]+(KalmanFilter_Input->AxisPP[1][1]-KalmanFilter_Input->AxisPP[2][0]/2-KalmanFilter_Input->AxisPP[0][2]/2)*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPdot[1] = KalmanFilter_Input->AxisPP[1][1]-KalmanFilter_Input->AxisPP[0][2]-(KalmanFilter_Input->AxisPP[2][1]/2+KalmanFilter_Input->AxisPP[1][2])*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPdot[2] = KalmanFilter_Input->AxisPP[1][2]-KalmanFilter_Input->AxisPP[2][2]*KalmanFilter_Input->Merge_t/2;
    KalmanFilter_Input->AxisPdot[3] = KalmanFilter_Input->AxisPP[1][1]-KalmanFilter_Input->AxisPP[2][0]-(KalmanFilter_Input->AxisPP[2][1]+KalmanFilter_Input->AxisPP[1][2]/2)*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPdot[4] = KalmanFilter_Input->Q_Velocity-KalmanFilter_Input->AxisPP[2][1]-KalmanFilter_Input->AxisPP[1][2]+KalmanFilter_Input->AxisPP[2][2]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPdot[5] = -KalmanFilter_Input->AxisPP[2][2];
    KalmanFilter_Input->AxisPdot[6] = KalmanFilter_Input->AxisPP[2][1]-KalmanFilter_Input->AxisPP[2][2]*KalmanFilter_Input->Merge_t/2;
    KalmanFilter_Input->AxisPdot[7] = -KalmanFilter_Input->AxisPP[2][2];
    KalmanFilter_Input->AxisPdot[8] = KalmanFilter_Input->Q_Bias;

    KalmanFilter_Input->AxisPP[0][0] += KalmanFilter_Input->AxisPdot[0]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[0][1] += KalmanFilter_Input->AxisPdot[1]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[0][2] += KalmanFilter_Input->AxisPdot[2]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[1][0] += KalmanFilter_Input->AxisPdot[3]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[1][1] += KalmanFilter_Input->AxisPdot[4]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[1][2] += KalmanFilter_Input->AxisPdot[5]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[2][0] += KalmanFilter_Input->AxisPdot[6]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[2][1] += KalmanFilter_Input->AxisPdot[7]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[2][2] += KalmanFilter_Input->AxisPdot[8]*KalmanFilter_Input->Merge_t;

    //   P = C*
    KalmanFilter_Input->AxisPCt_0 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[0][0];
    KalmanFilter_Input->AxisPCt_1 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[1][0];
    KalmanFilter_Input->AxisPCt_2 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[2][0];

    KalmanFilter_Input->AxisE = KalmanFilter_Input->R_Position + KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPCt_0;

    KalmanFilter_Input->AxisK_0 = KalmanFilter_Input->AxisPCt_0/KalmanFilter_Input->AxisE;
    KalmanFilter_Input->AxisK_1 = KalmanFilter_Input->AxisPCt_1/KalmanFilter_Input->AxisE;
    KalmanFilter_Input->AxisK_2 = KalmanFilter_Input->AxisPCt_2/KalmanFilter_Input->AxisE;


    KalmanFilter_Input->Axis_Err = Position - KalmanFilter_Input->Axis_Pos;
    KalmanFilter_Input->Axis_Pos += KalmanFilter_Input->AxisK_0 * KalmanFilter_Input->Axis_Err;
    KalmanFilter_Input->Axis_Vel += KalmanFilter_Input->AxisK_1 * KalmanFilter_Input->Axis_Err;
    KalmanFilter_Input->Axis_Bias += KalmanFilter_Input->AxisK_2 * KalmanFilter_Input->Axis_Err;

    KalmanFilter_Input->Axist_0 = KalmanFilter_Input->AxisPCt_0;
    KalmanFilter_Input->Axist_1 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[0][1];
    KalmanFilter_Input->Axist_2 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[0][2];

    KalmanFilter_Input->AxisPP[0][0] -= KalmanFilter_Input->AxisK_0*KalmanFilter_Input->Axist_0;
    KalmanFilter_Input->AxisPP[0][1] -= KalmanFilter_Input->AxisK_0*KalmanFilter_Input->Axist_1;
    KalmanFilter_Input->AxisPP[0][2] -= KalmanFilter_Input->AxisK_0*KalmanFilter_Input->Axist_2;
    KalmanFilter_Input->AxisPP[1][0] -= KalmanFilter_Input->AxisK_1*KalmanFilter_Input->Axist_0;
    KalmanFilter_Input->AxisPP[1][1] -= KalmanFilter_Input->AxisK_1*KalmanFilter_Input->Axist_1;
    KalmanFilter_Input->AxisPP[1][2] -= KalmanFilter_Input->AxisK_1*KalmanFilter_Input->Axist_2;
    KalmanFilter_Input->AxisPP[2][0] -= KalmanFilter_Input->AxisK_2*KalmanFilter_Input->Axist_0;
    KalmanFilter_Input->AxisPP[2][1] -= KalmanFilter_Input->AxisK_2*KalmanFilter_Input->Axist_1;
    KalmanFilter_Input->AxisPP[2][2] -= KalmanFilter_Input->AxisK_2*KalmanFilter_Input->Axist_2;

}

// light flow filter.
void OpticalFlow_Estimation(float flow_x,float flow_y,float Accx,float Accy)
{

    static float OpticalFlow_dt;
    OpticalFlow_dt = 0.005f;
    static float accel_bias[3] = {0.0f,0.0f,0.0f};  
    float accel_now[3] = {0.0f,0.0f,0.0f};


    accel_now[0] -= accel_bias[0];
    accel_now[1] -= accel_bias[1];

    /* x aix */
    static float OpticalFlowx_Velocity;
    static float Q_OpticalFlowxVelocity = 0.1,Q_xbias = 0.05;
    static float R_OpticalFlowx = 0.05;

    static float OpticalFlowx_Velocityerr,OpticalFlowxbias;
    static float OpticalFlowxPCt_0 = 0,OpticalFlowxPCt_1 = 0,OpticalFlowxE = 0;
    static float OpticalFlowxK_0 = 0,OpticalFlowxK_1 = 0,OpticalFlowxt_0 = 0,OpticalFlowxt_1 = 0;
    static char OpticalFlowxC_0 = 1;
    static float OpticalFlowxPdot[4],OpticalFlowxP[2][2];

    OpticalFlowx_Velocity += (Accx - OpticalFlowxbias) * OpticalFlow_dt;

    OpticalFlowxPdot[0] = Q_OpticalFlowxVelocity - OpticalFlowxP[0][1] - OpticalFlowxP[1][0];
    OpticalFlowxPdot[1] =   -OpticalFlowxP[1][1];
    OpticalFlowxPdot[2] =   -OpticalFlowxP[1][1];
    OpticalFlowxPdot[3] = Q_xbias;

    OpticalFlowxP[0][0] += OpticalFlowxPdot[0] * OpticalFlow_dt;
    OpticalFlowxP[0][1] += OpticalFlowxPdot[1] * OpticalFlow_dt;
    OpticalFlowxP[1][0] += OpticalFlowxPdot[2] * OpticalFlow_dt;
    OpticalFlowxP[1][1] += OpticalFlowxPdot[3] * OpticalFlow_dt;

    OpticalFlowxPCt_0 = OpticalFlowxC_0 * OpticalFlowxP[0][0];
    OpticalFlowxPCt_1 = OpticalFlowxC_0 * OpticalFlowxP[1][0];
    OpticalFlowxE = R_OpticalFlowx + OpticalFlowxC_0 * OpticalFlowxPCt_0;
    OpticalFlowxK_0 = OpticalFlowxPCt_0 / OpticalFlowxE;
    OpticalFlowxK_1 = OpticalFlowxPCt_1 / OpticalFlowxE;

    OpticalFlowx_Velocityerr = flow_x - OpticalFlowx_Velocity;
    OpticalFlowx_Velocity += OpticalFlowxK_0 * OpticalFlowx_Velocityerr;
    OpticalFlowxbias += OpticalFlowxK_1 * OpticalFlowx_Velocityerr;   

    OpticalFlowxt_0 = OpticalFlowxPCt_0;
    OpticalFlowxt_1 = OpticalFlowxC_0 * OpticalFlowxP[0][1];

    OpticalFlowxP[0][0] -= OpticalFlowxK_0 * OpticalFlowxt_0;
    OpticalFlowxP[0][1] -= OpticalFlowxK_0 * OpticalFlowxt_1;
    OpticalFlowxP[1][0] -= OpticalFlowxK_1 * OpticalFlowxt_0;
    OpticalFlowxP[1][1] -= OpticalFlowxK_1 * OpticalFlowxt_1;

    RT_Info.FlowX_V  = OpticalFlowx_Velocity;
    /* y aix */
    static float OpticalFlowy_Velocity;
    static float Q_OpticalFlowyVelocity = 0.1,Q_ybias = 0.05;
    static float R_OpticalFlowy = 0.05;
    static float OpticalFlowy_Velocityerr,OpticalFlowybias;
    static float OpticalFlowyPCt_0 = 0,OpticalFlowyPCt_1 = 0,OpticalFlowyE = 0;
    static float OpticalFlowyK_0 = 0,OpticalFlowyK_1 = 0,OpticalFlowyt_0 = 0,OpticalFlowyt_1 = 0;
    static char OpticalFlowyC_0 = 1;
    static float OpticalFlowyPdot[4],OpticalFlowyP[2][2];

    OpticalFlowy_Velocity += (Accy - OpticalFlowybias) * OpticalFlow_dt;

    OpticalFlowyPdot[0] = Q_OpticalFlowyVelocity - OpticalFlowyP[0][1] - OpticalFlowyP[1][0];
    OpticalFlowyPdot[1] =   -OpticalFlowyP[1][1];
    OpticalFlowyPdot[2] =   -OpticalFlowyP[1][1];
    OpticalFlowyPdot[3] = Q_ybias;

    OpticalFlowyP[0][0] += OpticalFlowyPdot[0] * OpticalFlow_dt;
    OpticalFlowyP[0][1] += OpticalFlowyPdot[1] * OpticalFlow_dt;
    OpticalFlowyP[1][0] += OpticalFlowyPdot[2] * OpticalFlow_dt;
    OpticalFlowyP[1][1] += OpticalFlowyPdot[3] * OpticalFlow_dt;

    OpticalFlowyPCt_0 = OpticalFlowyC_0 * OpticalFlowyP[0][0];
    OpticalFlowyPCt_1 = OpticalFlowyC_0 * OpticalFlowyP[1][0];
    OpticalFlowyE = R_OpticalFlowy + OpticalFlowyC_0 * OpticalFlowyPCt_0;
    OpticalFlowyK_0 = OpticalFlowyPCt_0 / OpticalFlowyE;
    OpticalFlowyK_1 = OpticalFlowyPCt_1 / OpticalFlowyE;

    OpticalFlowy_Velocityerr = flow_y - OpticalFlowy_Velocity;
    OpticalFlowy_Velocity += OpticalFlowyK_0 * OpticalFlowy_Velocityerr;
    OpticalFlowybias += OpticalFlowyK_1 * OpticalFlowy_Velocityerr;

    OpticalFlowyt_0 = OpticalFlowyPCt_0;
    OpticalFlowyt_1 = OpticalFlowyC_0 * OpticalFlowyP[0][1];

    OpticalFlowyP[0][0] -= OpticalFlowyK_0 * OpticalFlowyt_0;
    OpticalFlowyP[0][1] -= OpticalFlowyK_0 * OpticalFlowyt_1;
    OpticalFlowyP[1][0] -= OpticalFlowyK_1 * OpticalFlowyt_0;
    OpticalFlowyP[1][1] -= OpticalFlowyK_1 * OpticalFlowyt_1;

    RT_Info.FlowY_V  = OpticalFlowy_Velocity;

}


/***********************************************
 *    form Mr Ge.*****************************
 ***********************************************
 *
 */

MAT_3X3_TYPE I = { 1, 0, 0, \
  0, 1, 0, \
    0, 0, 1 };

MAT_3X3_TYPE Q = {w,0,0, \
  0,w,0, \
    0,0,w};

MAT_3X3_TYPE R = { v, 0, 0, \
  0, v, 0, \
    0, 0, v};

MAT_3X3_TYPE P = { 100,   0,   0, \
  0, 100,   0, \
    0,   0, 100 };


/* Matrix operation */

/*
************************************************************
*                Mat_copy_3x3()
* brief :
************************************************************
*/
void Mat_copy_3x3(MAT_3X3_TYPE* result, MAT_3X3_TYPE* a)   
{
  result->m11 = a->m11;
  result->m12 = a->m12;
  result->m13 = a->m13;

  result->m21 = a->m21;
  result->m22 = a->m22;
  result->m23 = a->m23;

  result->m31 = a->m31;
  result->m32 = a->m32;
  result->m33 = a->m33;
}


/*
************************************************************
*                Mat_copy_3x1()
* brief :
************************************************************
*/
void Mat_copy_3x1(MAT_3X1_TYPE* result, MAT_3X1_TYPE* a)
{
  result->m11 = a->m11;
  result->m21 = a->m21;
  result->m31 = a->m31;
}


/*
************************************************************
*                Mat_mul_3x3_3x3()
* brief :
************************************************************
*/
void Mat_mul_3x3_3x3(MAT_3X3_TYPE* result, MAT_3X3_TYPE* a, MAT_3X3_TYPE* b)   
{
  MAT_3X3_TYPE tmp;

  tmp.m11 = a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31;
  tmp.m12 = a->m11 * b->m12 + a->m12 * b->m22 + a->m13 * b->m32;
  tmp.m13 = a->m11 * b->m13 + a->m12 * b->m23 + a->m13 * b->m33;

  tmp.m21 = a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31;
  tmp.m22 = a->m21 * b->m12 + a->m22 * b->m22 + a->m23 * b->m32;
  tmp.m23 = a->m21 * b->m13 + a->m22 * b->m23 + a->m23 * b->m33;

  tmp.m31 = a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31;
  tmp.m32 = a->m31 * b->m12 + a->m32 * b->m22 + a->m33 * b->m32;
  tmp.m33 = a->m31 * b->m13 + a->m32 * b->m23 + a->m33 * b->m33;

  Mat_copy_3x3(result, &tmp);
}


/*
************************************************************
*                Mat_mul_3x3_3x1()
* brief :
************************************************************
*/
void Mat_mul_3x3_3x1(MAT_3X1_TYPE* result, MAT_3X3_TYPE* a, MAT_3X1_TYPE* b)
{
  MAT_3X1_TYPE tmp;
  tmp.m11 = a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31;
  tmp.m21 = a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31;
  tmp.m31 = a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31;
  Mat_copy_3x1(result, &tmp);
}


/*
************************************************************
*                Mat_add_3x3()
* brief :
************************************************************
*/
void Mat_add_3x3(MAT_3X3_TYPE* result, MAT_3X3_TYPE* a, MAT_3X3_TYPE* b)  
{
  MAT_3X3_TYPE tmp;

  tmp.m11 = a->m11 + b->m11;
  tmp.m12 = a->m12 + b->m12;
  tmp.m13 = a->m13 + b->m13;

  tmp.m21 = a->m21 + b->m21;
  tmp.m22 = a->m22 + b->m22;
  tmp.m23 = a->m23 + b->m23;

  tmp.m31 = a->m31 + b->m31;
  tmp.m32 = a->m32 + b->m32;
  tmp.m33 = a->m33 + b->m33;

  Mat_copy_3x3(result, &tmp);
}


/*
************************************************************
*                Mat_add_3x1()
* brief :
************************************************************
*/
void Mat_add_3x1(MAT_3X1_TYPE* result, MAT_3X1_TYPE* a, MAT_3X1_TYPE* b)
{
  MAT_3X1_TYPE tmp;
  tmp.m11 = a->m11 + b->m11;
  tmp.m21 = a->m21 + b->m21;
  tmp.m31 = a->m31 + b->m31;
  Mat_copy_3x1(result, &tmp);
}


/*
************************************************************
*                Mat_sub_3x3()
* brief :
************************************************************
*/
void Mat_sub_3x3(MAT_3X3_TYPE* result, MAT_3X3_TYPE* a, MAT_3X3_TYPE* b)  
{
  MAT_3X3_TYPE tmp;
  tmp.m11 = a->m11 - b->m11;
  tmp.m12 = a->m12 - b->m12;
  tmp.m13 = a->m13 - b->m13;

  tmp.m21 = a->m21 - b->m21;
  tmp.m22 = a->m22 - b->m22;
  tmp.m23 = a->m23 - b->m23;

  tmp.m31 = a->m31 - b->m31;
  tmp.m32 = a->m32 - b->m32;
  tmp.m33 = a->m33 - b->m33;
  Mat_copy_3x3(result, &tmp);
}

/*
************************************************************
*                Mat_sub_3x1()
* brief :
************************************************************
*/
void Mat_sub_3x1(MAT_3X1_TYPE* result, MAT_3X1_TYPE* a, MAT_3X1_TYPE* b)
{
  MAT_3X1_TYPE tmp;
  tmp.m11 = a->m11 - b->m11;
  tmp.m21 = a->m21 - b->m21;
  tmp.m31 = a->m31 - b->m31;
  Mat_copy_3x1(result, &tmp);
}

/*
************************************************************
*                Mat_transpose()
* brief :
************************************************************
*/
void Mat_transpose(MAT_3X3_TYPE *result, MAT_3X3_TYPE* a)  
{
  MAT_3X3_TYPE tmp;
  tmp.m11 = a->m11;  tmp.m12 = a->m21;  tmp.m13 = a->m31;
  tmp.m21 = a->m12;  tmp.m22 = a->m22;  tmp.m23 = a->m32;
  tmp.m31 = a->m13;  tmp.m32 = a->m23;  tmp.m33 = a->m33;
  Mat_copy_3x3(result, &tmp);
}

/*
************************************************************
*                Mat_inv_3x3()
* brief :
************************************************************
*/
void Mat_inv_3x3(MAT_3X3_TYPE *result, MAT_3X3_TYPE* a) 
{
  MAT_3X3_TYPE tmp;

  float a_m22_a_m33 = a->m22*a->m33;
  float a_m12_a_m33 = a->m12*a->m33;
  float a_m12_a_m23 = a->m12*a->m23;
  float a_m21_a_m33 = a->m21*a->m33;
  float a_m11_a_m33 = a->m11*a->m33;
  float a_m11_a_m23 = a->m11*a->m23;
  float a_m21_a_m32 = a->m21*a->m32;
  float a_m11_a_m32 = a->m11*a->m32;
  float a_m11_a_m22 = a->m11*a->m22;
  float a_m22_a_m31 = a->m22*a->m31;

  float a_m11_a_m22_a_m33 = a->m11*a_m22_a_m33;
  float a_m11_a_m23_a_m32 = a_m11_a_m23*a->m32;
  float a_m12_a_m21_a_m33 = a->m12*a_m21_a_m33;
  float a_m12_a_m23_a_m31 = a_m12_a_m23*a->m31;
  float a_m13_a_m21_a_m32 = a->m13*a_m21_a_m32;
  float a_m13_a_m22_a_m31 = a->m13*a_m22_a_m31;

  tmp.m11 =  (a_m22_a_m33 - a->m23*a->m32) / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);
  tmp.m12 = -(a_m12_a_m33 - a->m13*a->m32) / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);
  tmp.m13 =  (a_m12_a_m23 - a->m13*a->m22) / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);
  tmp.m21 = -(a_m21_a_m33 - a->m23*a->m31) / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);
  tmp.m22 =  (a_m11_a_m33 - a->m13*a->m31) / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);
  tmp.m23 = -(a_m11_a_m23 - a->m13*a->m21) / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);
  tmp.m31 =  (a_m21_a_m32 - a_m22_a_m31)   / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);
  tmp.m32 = -(a_m11_a_m32 - a->m12*a->m31) / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);
  tmp.m33 =  (a_m11_a_m22 - a->m12*a->m21) / (a_m11_a_m22_a_m33 - a_m11_a_m23_a_m32 - a_m12_a_m21_a_m33 + a_m12_a_m23_a_m31 + a_m13_a_m21_a_m32 - a_m13_a_m22_a_m31);   Mat_copy_3x3(result, &tmp);
}

/*
************************************************************
*                  ekf_att_est()
* brief : extended kalman filter
************************************************************
*/
void ekf_att_est(MAT_3X1_TYPE *x, MAT_3X1_TYPE *u, MAT_3X1_TYPE* y,float dt)   
{
  MAT_3X3_TYPE mat3X3_tmp1;
  MAT_3X3_TYPE mat3X3_tmp2;
  MAT_3X3_TYPE F_trans;
  MAT_3X3_TYPE L_trans;

  MAT_3X1_TYPE mat3X1_tmp1;
  MAT_3X1_TYPE x_tmp;

  float u1 = u->m11;
  float u2 = u->m21;
  float u3 = u->m31;

  Mat_copy_3x1(&x_tmp,x);

  F.m11 = 1;       F.m12 = u3*dt;   F.m13 = -u2*dt;
  F.m21 = -u3*dt;  F.m22 = 1;       F.m23 = u1*dt;
  F.m31 = u2*dt;   F.m32 = -u1*dt;  F.m33 = 1;

  L.m11 =    0;          L.m12 = -(x->m31)*dt;  L.m13 =  (x->m21)*dt;
  L.m21 =  (x->m31)*dt;  L.m22 = 0;             L.m23 = -(x->m11)*dt;
  L.m31 = -(x->m21)*dt;  L.m32 = (x->m11)*dt;   L.m33 = 0;

  Mat_transpose(&F_trans,&F);
  Mat_transpose(&L_trans,&L);

  /* P = F*P*F' + L*Q*L' */
  Mat_mul_3x3_3x3(&mat3X3_tmp1, &F, &P);
  Mat_mul_3x3_3x3(&mat3X3_tmp1, &mat3X3_tmp1, &F_trans);
  Mat_mul_3x3_3x3(&mat3X3_tmp2, &L, &Q);
  Mat_mul_3x3_3x3(&mat3X3_tmp2, &mat3X3_tmp2, &L_trans);
  Mat_add_3x3(&P, &mat3X3_tmp1, &mat3X3_tmp2);

  /* prio estimate */
  x_tmp.m11 =     (x->m11)    + u3*(x->m21)*dt - u2*(x->m31)*dt;
  x_tmp.m21 = -u3*(x->m11)*dt +    (x->m21)    + u1*(x->m31)*dt;
  x_tmp.m31 =  u2*(x->m11)*dt - u1*(x->m21)*dt +    (x->m31);

  /* kalman gain K = P*H'/(H*P*H'+M*R*M') */
  Mat_add_3x3(&mat3X3_tmp1, &P, &R);
  Mat_inv_3x3(&mat3X3_tmp1,&mat3X3_tmp1);
  Mat_mul_3x3_3x3(&K, &P, &mat3X3_tmp1);

  /* x = x + K*(y - H*x) */
  Mat_sub_3x1(&mat3X1_tmp1, y, &x_tmp);
  Mat_mul_3x3_3x1(&mat3X1_tmp1, &K, &mat3X1_tmp1);
  Mat_add_3x1(x,&x_tmp,&mat3X1_tmp1);

  /* P = (I - K*H)*P */
  Mat_sub_3x3(&mat3X3_tmp1, &I, &K);
  Mat_mul_3x3_3x3(&P, &mat3X3_tmp1, &P);
}

