/*
 * imu.c
 *
 *  Created on: 02/04/2019
 *      Author: cyh
 *
 */

#include "F28x_Project.h"
#include "imu.h"
#include "math.h"
#include "sensor/mpu9250.h"
#include "math2.h"
#include "sys_inside/delay.h"
#include "filter.h"
//#include "FLASH_API/FlashAPI.h"


extern DroneTargetInfo Target_Info;
extern Remote_Command Command_Uint,*Command;
extern Thrust UAVThrust;

MPU6000_TYPE *MPU_data;
extern DroneRTInfo RT_Info;
extern OffsetInfo OffsetData;    
extern Info_Test RT_Test;

extern Butter_Parameter Accel_Parameter;      
extern Butter_Parameter Flow_Parameter;
extern Error Error_Fix;
Butter_BufferData  accel_filter_buf[3];
Butter_BufferData  flow_filter_buf[3];
/*
static float GyroOffsetX = 0;
static float GyroOffsetY = 0;
static float GyroOffsetZ = 0;

static float AccOffsetX = -0.01475f;
static float AccOffsetY =  0.00700f;
static float AccOffsetZ =  0.03195f;
*/
#define G_VALUE (9.8f)

#define GRAVITY_MSS     9.7944f      //  value g.

#define ACC_X_GAIN 0.99824f
#define ACC_Y_GAIN 1.00082f
#define ACC_Z_GAIN 0.97271f

#define ACC_SCALE_X  (G_VALUE / ACC_SENSITIVITY)
#define ACC_SCALE_Y  (G_VALUE / ACC_SENSITIVITY)
#define ACC_SCALE_Z  (G_VALUE / ACC_SENSITIVITY)

#define GYRO_SCALE_X (DEG2RAD / GYRO_SENSITIVITY)
#define GYRO_SCALE_Y (DEG2RAD / GYRO_SENSITIVITY)
#define GYRO_SCALE_Z (DEG2RAD / GYRO_SENSITIVITY)

#define DEG2RAD        (PI/180.0f)
#define GYRO_SENSITIVITY 16.4f    /* +- 2000 degree/s */
#define ACC_SENSITIVITY  8192.0f

#define sampleFreq  500.0f          // sample frequency in Hz
#define twoKpDef    (12.0f * 0.2f)   // 2 * proportional gain 
#define twoKiDef    (0.1f * 0.2f)   // 2 * integral gain
#define PI 3.1415926

//extern OffsetInfo OffsetData;

volatile float RDrone_R[3][3];
float Accel_Src[3];
volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;   
volatile float twoKp = twoKpDef;                                                                        // 2 * proportional gain (Kp)
volatile float twoKi = twoKiDef;
volatile float integralFBx = 0.0f,  integralFBy = 0.0f, integralFBz = 0.0f;

float g_BaseThrrote = 0;   

int16_t accgyroval[9];

float test[20] = {};

void Set_Cutoff_Frequency(float sample_frequent, float cutoff_frequent,Butter_Parameter *LPF)  // init butterworth
{
  float fr = sample_frequent / cutoff_frequent;
  float ohm = tanf(3.141592653589793f / fr);
  float c = 1.0f + 2.0f * cosf(3.141592653589793f / 4.0f) * ohm + ohm * ohm;
  if (cutoff_frequent <= 0.0f)
  {
    // no filtering
    return;
  }
  LPF->b[0] = ohm * ohm / c;
  LPF->b[1] = 2.0f * LPF->b[0];
  LPF->b[2] = LPF->b[0];
  LPF->a[0]=1.0f;
  LPF->a[1] = 2.0f * (ohm * ohm - 1.0f) / c;
  LPF->a[2] = (1.0f - 2.0f * cosf(3.141592653589793f / 4.0f) * ohm + ohm * ohm) / c;
}


void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az)
{
    float recipNorm;
    float halfvx, halfvy, halfvz;
    float halfex, halfey, halfez;
    float qa, qb, qc;

    // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

        // Normalise accelerometer measurement
        recipNorm = invSqrt(ax * ax + ay * ay + az * az);
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        // Estimated direction of gravity and vector perpendicular to magnetic flux
        halfvx = q1 * q3 - q0 * q2;
        halfvy = q0 * q1 + q2 * q3;
        halfvz = q0 * q0 - 0.5f + q3 * q3;

        // Error is sum of cross product between estimated and measured direction of gravity
        halfex = (ay * halfvz - az * halfvy);
        halfey = (az * halfvx - ax * halfvz);
        halfez = (ax * halfvy - ay * halfvx);

        // Compute and apply integral feedback if enabled   
        if(twoKi > 0.0f) {  
            integralFBx += twoKi * halfex * (1.0f / sampleFreq);    // integral error scaled by Ki
            integralFBy += twoKi * halfey * (1.0f / sampleFreq);
            integralFBz += twoKi * halfez * (1.0f / sampleFreq);
            gx += integralFBx;  // apply integral feedback
            gy += integralFBy;
            gz += integralFBz;
        }
        else {
            integralFBx = 0.0f; // prevent integral windup
            integralFBy = 0.0f;
            integralFBz = 0.0f;
        }

        // Apply proportional feedback
        gx += twoKp * halfex;
        gy += twoKp * halfey;
        gz += twoKp * halfez;
    }

    // Integrate rate of change of quaternion
    gx *= (0.5f * (1.0f / sampleFreq));     // pre-multiply common factors
    gy *= (0.5f * (1.0f / sampleFreq));
    gz *= (0.5f * (1.0f / sampleFreq));
    qa = q0;
    qb = q1;
    qc = q2;
    q0 += (-qb * gx - qc * gy - q3 * gz);      
    q1 += (qa * gx + qc * gz - q3 * gy);
    q2 += (qa * gy - qb * gz + q3 * gx);
    q3 += (qa * gz + qb * gy - qc * gx);

    // Normalise quaternion
    recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3); 
    q0 *= recipNorm;
    q1 *= recipNorm;
    q2 *= recipNorm;
    q3 *= recipNorm;
}



float safe_asin(float v)
{
    if (isnan(v))
    {
        return 0.0f;
    }
    if (v >= 1.0f)
    {
        return PI/2;
    }
    if (v <= -1.0f)
    {
        return -PI/2;
    }
    return asin(v);
}

/****************** AHRS refresh*************/
void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
    float recipNorm;
    float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
    float hx, hy, bx, bz;
    float halfvx, halfvy, halfvz, halfwx, halfwy, halfwz;
    float halfex, halfey, halfez;
    float qa, qb, qc;

    // Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
    if((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))
    {
        MahonyAHRSupdateIMU(gx, gy, gz, ax, ay, az);
        return;
    }

    // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

        // Normalise accelerometer measurement
        recipNorm = invSqrt(ax * ax + ay * ay + az * az);  
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        // Normalise magnetometer measurement
        recipNorm = invSqrt(mx * mx + my * my + mz * mz);
        mx *= recipNorm;
        my *= recipNorm;
        mz *= recipNorm;

        // Auxiliary variables to avoid repeated arithmetic
        q0q0 = q0 * q0;
        q0q1 = q0 * q1;
        q0q2 = q0 * q2;
        q0q3 = q0 * q3;
        q1q1 = q1 * q1;
        q1q2 = q1 * q2;
        q1q3 = q1 * q3;
        q2q2 = q2 * q2;
        q2q3 = q2 * q3;
        q3q3 = q3 * q3;

        // Reference direction of Earth's magnetic field
        hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
        hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
        bx = sqrt(hx * hx + hy * hy);
        bz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));

        // Estimated direction of gravity and magnetic field
        halfvx = q1q3 - q0q2;
        halfvy = q0q1 + q2q3;
        halfvz = q0q0 - 0.5f + q3q3;
        halfwx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
        halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
        halfwz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);

        // Error is sum of cross product between estimated direction and measured direction of field vectors
        halfex = (ay * halfvz - az * halfvy) + (my * halfwz - mz * halfwy);   
        halfey = (az * halfvx - ax * halfvz) + (mz * halfwx - mx * halfwz);
        halfez = (ax * halfvy - ay * halfvx) + (mx * halfwy - my * halfwx);

        // Compute and apply integral feedback if enabled
        if(twoKi > 0.0f)
        {
            integralFBx += twoKi * halfex * (1.0f / sampleFreq);    // integral error scaled by Ki
            integralFBy += twoKi * halfey * (1.0f / sampleFreq);
            integralFBz += twoKi * halfez * (1.0f / sampleFreq);
            gx += integralFBx;  // apply integral feedback
            gy += integralFBy;
            gz += integralFBz;
        }
        else
        {
            integralFBx = 0.0f; // prevent integral windup
            integralFBy = 0.0f;
            integralFBz = 0.0f;
        }

        // Apply proportional feedback
        gx += twoKp * halfex;
        gy += twoKp * halfey;
        gz += twoKp * halfez;
    }

    // Integrate rate of change of quaternion
    gx *= (0.5f * (1.0f / sampleFreq));     // pre-multiply common factors
    gy *= (0.5f * (1.0f / sampleFreq));
    gz *= (0.5f * (1.0f / sampleFreq));
    qa = q0;
    qb = q1;
    qc = q2;
    q0 += (-qb * gx - qc * gy - q3 * gz);     
    q1 += (qa * gx + qc * gz - q3 * gy);
    q2 += (qa * gy - qb * gz + q3 * gx);
    q3 += (qa * gz + qb * gy - qc * gx);

    // Normalise quaternion
    recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 *= recipNorm;
    q1 *= recipNorm;
    q2 *= recipNorm;
    q3 *= recipNorm;

}

/************姿态数据获取并融合*************/

// 读取MPU姿态函数.
/*
void IMU_getValues(float *values)  // 姿态数据融合.
{
    int16_t accgyroval[9];
    int i;
    //LSM303_readMag(&accgyroval[6]);
    MPU6500_readGyro_Acc(&accgyroval[3],&accgyroval[0]);  // 读入加速度与滚转角数据.
    for(i = 0; i<6; i++)
    {
        //转化为m/s^2
        if(i < 3)
        {
            values[i] = ((float) accgyroval[i]) / 16384;//(量程/分辨率): 4/65536 = 1/16384 转化为m/s^2
        }
        //转化为rad/s
        else
        {
            values[i] = ((float) accgyroval[i]) / 16.384;//(量程/分辨率): 4000/65536 = 1/16.384 转化为°/s
        }
    }
    values[6] = (float)accgyroval[6] /32768 *4 ;
    values[7] = (float)accgyroval[7] /32768 *4 ;
    values[8] = (float)accgyroval[8] /32768 *4 ;
}
*/
void IMU_getValues(float * values)   
{
    //int i;


    float AccData[3];
    //LSM303_readMag(&accgyroval[6]);
    MPU6000_Read(&accgyroval[3],&accgyroval[0]);

    values[3] = ((float) accgyroval[3]) / 16.384f;//4000/65536 = 1/16.384 °/s
    values[4] = ((float) accgyroval[4]) / 16.384f;//4000/65536 = 1/16.384 °/s
    values[5] = ((float) accgyroval[5]) / 16.384f;//(4000/65536 = 1/16.384 °/s

    //4/65536 = 1/16384 g  convert to m/s^2
    //AccData[0] = (((float) accgyroval[0]) / 32768.0f * 2 );
    //AccData[1] = (((float) accgyroval[1]) / 32768.0f * 2 );
    //AccData[2] = (((float) accgyroval[2]) / 32768.0f * 2 );
     // 4096.0f
    AccData[0] = (((float) accgyroval[0]) / 16384.0f * GRAVITY_MSS );//OffsetData.AccXScale - OffsetData.AccX;
    AccData[1] = (((float) accgyroval[1]) / 16384.0f * GRAVITY_MSS );//OffsetData.AccYScale - OffsetData.AccY;
    RT_Info.CpuTick = AccData[2] = ((float) accgyroval[2]/ 16384.0f* GRAVITY_MSS - 1.7);//OffsetData.AccZScale - OffsetData.AccZ;

    RT_Test.Acc_Uesr1 = AccData[0];

    values[0] = AccData[0];
    values[1] = AccData[1];
    values[2] = AccData[2];

    values[0]=  LPButterworth(AccData[0],&accel_filter_buf[0],&Accel_Parameter);  
    values[1]=  LPButterworth(AccData[1],&accel_filter_buf[1],&Accel_Parameter);
    values[2]=  LPButterworth(AccData[2],&accel_filter_buf[2],&Accel_Parameter);

    RT_Test.Acc_User2 = values[0];

    values[6] = (float)accgyroval[6] /32768 *4;
    values[7] = (float)accgyroval[7] /32768 *4;
    values[8] = (float)accgyroval[8] /32768 *4;

    test[0] = values[0];
    test[1] = values[1];
    test[2] = values[2];

}


void IMU_getInfo()      // IMU data
{
    static float q[4];
    static float getValue[9];
    static float q0q0,q0q1,q0q2,q0q3,q1q1,q1q2,q1q3,q2q2,q2q3,q3q3;
    IMU_getValues(getValue);
    MahonyAHRSupdate(getValue[3]* PI/180, getValue[4]* PI/180, getValue[5]* PI/180,
                               getValue[0], getValue[1], getValue[2],0,0,0);

    q[0] = q0;
    q[1] = q1;
    q[2] = q2;
    q[3] = q3;

    q0q0 = q[0]*q[0];
    q0q1 = q[0]*q[1];
    q0q2 = q[0]*q[2];
    q0q3 = q[0]*q[3];
    q1q1 = q[1]*q[1];
    q1q2 = q[1]*q[2];
    q1q3 = q[1]*q[3];
    q2q2 = q[2]*q[2];
    q2q3 = q[2]*q[3];
    q3q3 = q[3]*q[3];

    RDrone_R[0][0] = q0q0 + q1q1 - q2q2 - q3q3;
    RDrone_R[0][1] = 2.0 * (q1q2 + q0q3);
    RDrone_R[0][2] = 2.0 * (q1q3 - q0q2);
    RDrone_R[1][0] = 2.0 * (q1q2 - q0q3);
    RDrone_R[1][1] = q0q0 - q1q1 + q2q2 - q3q3;
    RDrone_R[1][2] = 2.0 * (q2q3 + q0q1);
    RDrone_R[2][0] = 2.0 * (q1q3 + q0q2);
    RDrone_R[2][1] = 2.0 * (q2q3 - q0q1);
    RDrone_R[2][2] = q0q0 - q1q1 - q2q2 + q3q3;

    Accel_Src[0] = getValue[0];
    Accel_Src[1] = getValue[1];
    Accel_Src[2] = getValue[2];

    RT_Info.rateRoll=getValue[3];
    RT_Info.ratePitch=getValue[4];
    RT_Info.rateYaw=getValue[5];

    RT_Info.GyroX = getValue[3] - OffsetData.GyroX ;
    RT_Info.GyroY = getValue[4] - OffsetData.GyroY ;
    RT_Info.GyroZ = getValue[5] - OffsetData.GyroZ ;    

    
    /*
      RT_Info.MagX = getValue[6]  ;
      RT_Info.MagY = getValue[7]  ;
      RT_Info.MagZ = getValue[8]  ;
     */
    RT_Info.accXaxis = ((q0q0 + q1q1 - q2q2 - q3q3)*getValue[0] + (2.f * (q1q2 - q0q3))*getValue[1]  +   (2.f * (q1q3 + q0q2))*getValue[2])  ;
    RT_Info.accYaxis = ((2.f * (q1q2 + q0q3))*getValue[0]  + (q0q0 - q1q1 + q2q2 - q3q3)*getValue[1] +   (2.f * (q2q3 - q0q1))*getValue[2]);
    RT_Info.accZaxis =  ((2.f * (q1q3 - q0q2))*getValue[0]   + (2.f * (q2q3 + q0q1))*getValue[1]    +   (q0q0 - q1q1 - q2q2 + q3q3)*getValue[2] - GRAVITY_MSS);

    RT_Info.AccX = (q0q0 + q1q1 - q2q2 - q3q3)* RT_Info.accXaxis + (2.f * (q1q2 + q0q3))* RT_Info.accYaxis  +   (2.f * (q1q3 - q0q2))*RT_Info.accZaxis  ;
    RT_Info.AccY = 2.f * (q1q2 - q0q3)* RT_Info.accXaxis + (q0q0 - q1q1 + q2q2 - q3q3)* RT_Info.accYaxis  +   (2.f * (q2q3 + q0q1))*RT_Info.accZaxis ;
    RT_Info.AccZ = 2.f * (q1q3 + q0q2)* RT_Info.accXaxis + (2.f * (q2q3 - q0q1))* RT_Info.accYaxis  +   (q0q0 - q1q1 - q2q2 + q3q3)*RT_Info.accZaxis  ;
    // calcule Pitch、Roll、Yaw.

    RT_Info.Roll = (atan2(2.0*(q0q1 + q2q3),
                          1 - 2.0*(q1q1 + q2q2)))* 180/PI - Error_Fix.Roll;   
    RT_Info.Pitch = -safe_asin(2.0*(q0q2 - q1q3))* 180/PI - Error_Fix.Pitch;

    RT_Info.Yaw = -atan2(2.0*q1q2 + 2.0*q0q3, -2.0*q2q2 - 2.0*q3q3 + 1) * 180/PI; // yaw

    //Write_Box();      

}

void Quadrotor_Control()
{
//    GpioDataRegs.GPBSET.bit.GPIO40=1;

    //Matrix_EstimateEuler(*acc,*gyro,control_dt);

    Target_Info.Pitch = 50*Command->Pitch;
    Target_Info.Roll = 50*Command->Roll;
    UAVThrust.BasicThrust = 600*Command->Throttle;


    //Eular_Control(targeteuler,g_Eular,gyro,acc,control_dt,&Control_Data,g_BaseThrrote);
    //Moto_SetPwm(&Control_Data);

//    GpioDataRegs.GPBCLEAR.bit.GPIO40=1;
}


// 互补滤波算法初步
/*
 * para_in:MPU角度、MPU加速度、积分时间、角度权重.
 *
 *
 */
/*
float ComplementaryFilter(float angle_m,float gyro_m,float dt，float K1)
{
    float angle_out;
    float angle_out_last;

    gyro_m -= 0.55;
    angle_out = K1*angle_m + (1 - K1)*(angle_out_last + gyro_m * dt);
    angle_out_last = angle_out;

    return angle_out;
}

// 二阶互补滤波算法初步.
float erjiehubu(float angle_m, float gyro_m,float dt)
{

    float K = 0.05;
    float y1;
    float x1 = (angle_m - angle_P)*K*K;
    y1 = y1 + x1 * dt;
    float x2 = y1 + 2*K*(angle_m - angle_P) + gyro_m;
    angle_P = angle_P + x2*dt;
    return angle_P;


}
*/
