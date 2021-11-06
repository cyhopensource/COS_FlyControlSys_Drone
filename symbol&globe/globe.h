/*
 * globe.h
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 *
 *      contents��
 *      1、System operation mark quantity
 *      2、communication module
 *      3、sensor module
 *      4、filter and PID para module
 *      5、real time data
 *      6、motor
 *      7、mission control system
 *      8、math data.
 *      9、FLASH.
 *
 *
 *
 */

#ifndef SYMBOL_GLOBE_GLOBE_H_
#define SYMBOL_GLOBE_GLOBE_H_

#include "F28x_Project.h"
/*******************System operation mark quantity***********/
typedef enum
{
    Null = 0x00,
    WFY_Test = 0x01,
    Buletooth_Test = 0x02,

}Func;

typedef struct
{
    Func Test1;
    Func Test2;
    Func Test3;

}Test_Mode;

typedef enum
{

    Bluetooth = 0x00,
    WFY = 0x01,

}Mode;

typedef struct
{

    Mode Mode_1;


}Control_mode;

/****************************communication module ********************/




typedef struct     
{
    float Throttle;
    uint16_t Extra;
    float Roll;
    float Pitch;
    float Yaw;
    float meter;
}Remote_Command;

typedef struct   
{
    uint32_t Ch1;
    uint32_t Ch2;
    uint32_t Ch3;
    uint32_t Ch4;
    uint32_t Ch5;
    uint32_t Ch6;
    uint32_t Ch7;
    uint32_t Ch8;

}Chx_Width;

typedef struct{
    float XaxisPos;
    float YaxisPos;
    float ZaxisPos;
    float Navigation;
}RemoteControl;





/*
typedef struct{
    Uint32 Ch1;
    Uint32 Ch2;
    Uint32 Ch3;
    Uint32 Ch4;
    Uint32 Ch5;
    Uint32 Ch6;
}Chx;


*/
/****************************sensor***************************/

typedef struct
{
    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;
    int16_t gyro_x;  //rad/s
    int16_t gyro_y;
    int16_t gyro_z;
    int16_t temperature;
}
MPU6000_TYPE;

typedef struct
{
  float yaw;
  float pitch;
  float roll;
}Eular;

typedef struct
{
    _Bool MagOffseting;
    Uint16 MagX;
    Uint16 MagY;
    Uint16 MagZ;
    float GyroX;
    float GyroY;
    float GyroZ;
    float AccX;
    float AccY;
    float AccZ;
    float AccXScale;
    float AccYScale;
    float AccZScale;
}OffsetInfo;

/********* filter and PID para ********/
/*
typedef struct
{
    Uint16 acc_x;
    Uint16 acc_y;
    Uint16 acc_z;

    Uint16 gryo_x;
    Uint16 gryo_y;
    Uint16 gryo_z;



}LPF;
*/

typedef struct{

    float Merge_t;

    float Q_Position;
    float Q_Velocity;
    float Q_Bias;
    float R_Position;

    float Axis_Pos;
    float Axis_Vel;
    float Axis_Bias;
    float Axis_Err;
    float AxisPCt_0;
    float AxisPCt_1;
    float AxisPCt_2;
    float AxisE;
    char AxisC_0;
    float AxisK_0;
    float AxisK_1;
    float AxisK_2;
    float Axist_0;
    float Axist_1;
    float Axist_2;
    float AxisPdot[9];
    float AxisPP[3][3];
}KalmanFilter;       

typedef struct {
    float m11;
    float m12;
    float m13;
    float m21;
    float m22;
    float m23;
    float m31;
    float m32;
    float m33;
}MAT_3X3_TYPE;

typedef struct {
    float m11;
    float m21;
    float m31;
}MAT_3X1_TYPE;

/******* PID para *******/

typedef struct{

    float Kp;
    float Ki;
    float Kd;
}PID;

typedef struct{

    float error;
    float lasterror;
    float differential;
    float differentialFliter;
    float pOut;
    float iOut;
    float dOut;
    float value;
}PIDOut;

typedef struct
{
    PID Pitch;  
    PID Roll;   
    PID Yaw;    
    PID Height;

    PID PitchRate;
    PID RollRate;
    PID YawRate;
    PID HeightRate;

    PID PosX;
    PID PosY;
    PID PosZ;

    PID VelX;
    PID VelY;
    PID VelZ;

    PID FlowX;
    PID FlowY;
    PID FlowVelX;
    PID FlowVelY;

    PID AccZ;

}PIDPara;   



/******* RT_Info **************/

typedef struct
{
    float Pitch;
    float Roll;
    float Yaw;

}Error;

typedef struct{
    float US100_Zaxis;
    float Raspberry_Xaxis;
    float Raspberry_Yaxis;
    float FlowVelX;
    float FlowVelY;
    float VIO_Xaxis;
    float VIO_Yaxis;
    float VIO_Zaxis;
}SensorData;

typedef enum{
    Data_Headmode = 0,
    Data_Headfree = 1,
    Data_Point = 2,
    Data_Flow = 3,
    Data_Follow = 4,
}FlyMode;

/*Real time info of Drone*/
typedef struct
{
    float Pitch;
    float Roll;
    float Yaw;
    float HomeYaw;
    float ratePitch;
    float rateRoll;
    float rateYaw;
    float rateHeight;    
    float accXaxis;
    float accYaxis;
    float accZaxis;
    float Height;
    float Height_V;
    float FlowX;
    float FlowY;
    float FlowX_V;
    float FlowY_V;
    float PointX;
    float PointY;
    float PointX_V;
    float PointY_V;
    float batteryVoltage;
    float AccX;
    float AccY;
    float AccZ;
    float GyroX;
    float GyroY;
    float GyroZ;
    float MagX;
    float MagY;
    float MagZ;
    int lowPowerFlag;
    float CpuTick;
}DroneRTInfo;

typedef struct
{
    float Acc_x;
    float Acc_y;
    float Acc_z;

    float Acc_Uesr1;
    float Acc_User2;
    float Acc_User3;


}Info_Test;


/*
typedef struct
{
    float Pitch;
    float Roll;
    float Yaw;
    float HomeYaw;
    float ratePitch;
    float rateRoll;
    float rateYaw;
    float rateHeight;
    float accXaxis;
    float accYaxis;
    float accZaxis;
    float Height;
    float Height_V;
    float FlowX;
    float FlowY;
    float FlowX_V;
    float FlowY_V;
    float PointX;
    float PointY;
    float PointX_V;
    float PointY_V;
    float batteryVoltage;
    float GyroX;
    float GyroY;
    float GyroZ;
    float MagX;
    float MagY;
    float MagZ;
    int lowPowerFlag;
}DroneRTInfo;
*/

typedef enum{
  Drone_Mode_None=0,
  Drone_Mode_RatePitch, 
  Drone_Mode_RateRoll,
  Drone_Mode_RateYaw,
  Drone_Mode_Pitch,     
  Drone_Mode_Roll,
  Drone_Mode_Yaw,
  Drone_Mode_4Axis,     
}DroneFlightMode_TypeDef;

typedef enum
{
  Report_SET      = 0x01,
  Report_RESET    = 0x00,
}DroneReportSW_TypeDef;

typedef enum{    
    Drone_Off  = 0x00,
    Drone_On   = 0x01,
    Drone_Land = 0x02,
}DroneFlightOnOff_TypeDef;    

typedef struct{
    DroneFlightOnOff_TypeDef OnOff;
    DroneFlightMode_TypeDef DroneMode;
    DroneReportSW_TypeDef ReportSW;
    int landFlag;
}DroneFlightControl;

typedef struct
{
    float Pitch;
    float Roll;
    float Yaw;
    float RateRoll;
    float RatePitch;
    float RateYaw;
    float RateHeight;
    float Height;
    float VelHeight;
    float AccHeight;
}DroneTargetInfo;     



/**********System_dynamic****************/

typedef struct{           // throtte data.
    float PitchThrust;
    float RollThrust;
    float YawThrust;
    float HeightThrust;
    float BasicThrust;
}Thrust;

typedef struct       // motor output
{
    unsigned int M1;
    unsigned int M2;
    unsigned int M3;
    unsigned int M4;
}Throttle;     

/**************** mission control system ****************/

typedef struct     
{

    unsigned char Mission1;
    unsigned char Mission2;
    unsigned char Mission3;
    unsigned char Mission4;
    unsigned char Mission5;
    unsigned char Mission6;
    unsigned char Mission7;
    unsigned char Mission8;


}Mission_List;

typedef struct   
{

    unsigned char RUN;
    unsigned char STOP;
    unsigned char BUSY;

}Mission_Sta;

/***************** math data ******************/
//float union
typedef union{
        float fv;
        Uint16 sv[2];
}float_union;

/*****FLASH ******/

typedef struct
{
    Uint16 isGood;
    PIDPara pidPara;
    OffsetInfo Offset_Data;
}FlashData;

// black BOX
typedef struct
{
    DroneRTInfo RT_IN_BOX;

    DroneRTInfo RT_OUT_BOX;


}Black_box;

#endif /* SYMBOL_GLOBE_GLOBE_H_ */
