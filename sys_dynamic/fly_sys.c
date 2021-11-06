/*
 * fly_sys.c
 *
 *  Created on: 01/04/2019  All system setup and test.
 *      Author: cyh
 */


#include "algorithm/filter.h"
#include "F28x_project.h"
#include "fly_sys.h"
#include "sys_dynamic/pre_start.h"
#include "algorithm/filter.h"
#include "communication/receive.h"
#include "communication/send.h"
#include "sensor/mpu9250.h"
#include "communication/cap.h"
#include "communication/sci.h"
#include "communication/spi.h"
#include "sys_dynamic/pwm.h"
#include "algorithm/imu.h"
#include "sys_inside/exit.h"
#include "algorithm/PID_control.h"
#include "symbol&globe/led.h"
#include "sys_inside/timer.h"
#include "communication/PCData.h"
//#include "FLASH_API/FlashAPI.h"

Uint16 RecivePCData[16];
Uint16 ReciveMvData[16];

unsigned char STATE_3;   
unsigned char STATE_2;
unsigned char STATE_CLK;
unsigned char STATE_CLK_ALL;
unsigned char temp2;

#define  DEF_OK    1
#define  DEF_FALSE                  0u   
#define  DEF_TRUE                   1u
#define  DATA_GOT  1    
#define  DATA_FAIL 0
#define  DATA_OK   1
#define  UP        2
#define  LAND      0
#define  DOWN      1
#define  FLY_ON    1
#define  FLY_OFF   0
#define  Command_GOT  1      
#define  Command_FAIL 0
#define  SEND_OK      1    
#define  SEND_FAIL    0
#define  True   1
#define  False  0


//Mission_List List;
KalmanFilter XAxis,YAxis,ZAxis;  

Remote_Command Command_Uint,*Command;
/*
PIDOut OriginalPitch,OriginalRoll,OriginalYaw,OriginalHeight,OriginalPosX,OriginalPosY,OriginalPosZ,
                    OriginalPitchRate,OriginalRollRate,OriginalYawRate,OriginalVelX,OriginalVelY,OriginalVelZ,
                    OriginalHeightRate;
*/
PIDOut OriginalPitch,OriginalRoll,OriginalYaw,OriginalPosX,OriginalPosY,OriginalPosZ,
OriginalPitchRate,OriginalRollRate,OriginalYawRate,OriginalVelX,OriginalVelY,OriginalVelZ,
OriginalFlowX,OriginalFlowY,OriginalFlowVelX,OriginalFlowVelY,OriginalAccZ,OriginalHeight,OriginalHeightRate;

PIDPara PID_ParaInfo;

DroneTargetInfo Target_Info;                                                             
DroneFlightControl FlightControl;                                                        
DroneRTInfo RT_Info;    
FlyMode Fly_Mode;
SensorData Sensor_Info;
RemoteControl RockerControl;
Thrust UAVThrust;
Throttle Throttle_Info;
OffsetInfo OffsetData;
Butter_Parameter Accel_Parameter;      
Butter_Parameter Flow_Parameter;
Control_mode C_mode;
Error Error_Fix;
Test_Mode Test_M;
Info_Test RT_Test;

Black_box Box;

Eular g_Eular = {0,0,0};

MPU6000_TYPE *MPU6000_Value2;   

float MPU_Info[6];

extern unsigned char StartFly;
extern unsigned char Flying;
extern unsigned char MPU_sta;

unsigned char Data(void);
unsigned char Fly(void);

unsigned char Data_Handle(void);
unsigned char Start_up(void);
unsigned char Data_Combine(void);
unsigned char Fly_Up(void);
unsigned char SendData(void);
unsigned char ReceiveData(void);

extern unsigned char Test_State;
extern unsigned char Fix_State;

/********** main system control **********/
/*
 * 1:receive remote data 
 * 2:calcul the sensor data
 *
 */
void Hardware_Init(void)    
{
    Timer_Init();
    Led_Init();        // led init
    spi_fifo_init();
    Cap_init();
    Sci_Init();
    C28x_BSP_Epwm_Init();     
    MPU6500_initialize();
    DELAY_US(500*100);
    MPU6500_Init_Offset();
    DELAY_US(500*100);
    Set_Cutoff_Frequency(500, 30 ,&Accel_Parameter);//para of butterworth init.
    DELAY_US(500*100);
    //Load_ParaConfig();      
    QuadrotorPara_Init();      // basic para init.


}

void System_all(void)   // top-level mission
{

    Process_PCData();     // fly mission plan

    STATE_2 = ReceiveData(); 

    if(C_mode.Mode_1 == WFY)

        STATE_2 = Control_Data();   

    STATE_2 =  Fly();  

    if(STATE_2 == FLY_ON)
    {
        STATE_CLK++;         // system counter
    }

    STATE_CLK_ALL++;      // main counter

    STATE_2 = SendData();      // in the interrupt of the timer0

}

/******Run boot system task*******/
unsigned char Fly(void)     // second level fly mission.
{
    STATE_3 = Start_up(); 

    if(STATE_3 == UP)
    {
        Fly_Up();
        return FLY_ON;
    }
    else
        return FLY_OFF;

}

unsigned char Data(void) 
{


    temp2 = Data_Handle();

    temp2 = Data_Combine();


    return DATA_OK;   

}


/************basic control mission **********/
unsigned char Control_Data()
{

    Quadrotor_Control();

    return DEF_OK;

}

unsigned char Data_Handle(void)   // mission 1: data calcul
{

    IMU_getInfo();  


    return  DATA_GOT;    

}

unsigned char Start_up(void)   
{
    Pre_fly();    // check the state of start.

    if(Flying == 1)    
    {

        Target_Info.Height = 0.10;  
        return UP;
    }
    else
        return LAND;
}

unsigned char Data_Combine(void)
{
    //POS_KalmanFilter(&ZAxis,Sensor_Info.US100_Zaxis,RT_Info.accZaxis);  
    RT_Info.Height = ZAxis.Axis_Pos;
    RT_Info.Height_V = ZAxis.Axis_Vel;   
/*
    RT_Info.AccX = MPU_data->acc_x;
    RT_Info.AccY = MPU_data->acc_y;
    RT_Info.AccZ = MPU_data->acc_z;
    RT_Info.GyroX = MPU_data->gyro_x;
    RT_Info.GyroY = MPU_data->gyro_y;
    RT_Info.GyroZ = MPU_data->gyro_z;
*/
    g_Eular.roll = RT_Info.Roll;
    g_Eular.yaw = RT_Info.Yaw;
    g_Eular.pitch = RT_Info.Pitch;

    return 1;

}

unsigned char Data_Combine_2(void)   // combine with kalman data.
{

    static   float FlowX_Array[30];
    static   float FlowY_Array[30];

    POS_KalmanFilter(&ZAxis,Sensor_Info.US100_Zaxis,RT_Info.accZaxis);
    RT_Info.Height = ZAxis.Axis_Pos;
    RT_Info.Height_V = ZAxis.Axis_Vel;    

    if(Fly_Mode == Data_Point )
    {
       /*The acceleration X-axis of the geographic coordinate system corresponds to the camera's X-axis data */
        POS_KalmanFilter(&XAxis,Sensor_Info.Raspberry_Xaxis/100,RT_Info.AccX);
        RT_Info.PointX = XAxis.Axis_Pos;
        RT_Info.PointX_V = XAxis.Axis_Vel;

       /*The acceleration X-axis of the geographic coordinate system corresponds to the camera's Y-axis data*/
        POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
        RT_Info.PointY = YAxis.Axis_Pos;
        RT_Info.PointY_V = YAxis.Axis_Vel;
    }
    else if(Fly_Mode == Data_Flow)   
    {
        OpticalFlow_Estimation(Sensor_Info.FlowVelX /100,Sensor_Info.FlowVelY /100,RT_Info.AccX,-RT_Info.AccY);
        RT_Info.FlowX = Average_Filter(RT_Info.FlowX_V * 0.08f,30,FlowX_Array)  * 30 ;
        RT_Info.FlowY = Average_Filter(RT_Info.FlowY_V * 0.08f,30,FlowY_Array)  * 30 ;

        //            RT_Info.FlowX += RT_Info.FlowX_V * 0.08f;
        //            RT_Info.FlowY += RT_Info.FlowY_V * 0.08f;

    }
    else if(Fly_Mode == Data_Follow)
    {
        OpticalFlow_Estimation(Sensor_Info.FlowVelX /100,Sensor_Info.FlowVelY /100,RT_Info.AccX,-RT_Info.AccY); 

        POS_KalmanFilter(&XAxis,Sensor_Info.Raspberry_Xaxis/100,RT_Info.AccX);
        RT_Info.PointX = XAxis.Axis_Pos;

        POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
        RT_Info.PointY = YAxis.Axis_Pos;
    }

    return 1;

}

unsigned char Fly_Up(void)
{
    float Climbing = 0.015;     // climb speed.
    float Declining = 0.008;

    Position_control(Fly_Mode,Climbing,Declining);
    return 0;

}

unsigned char ReceiveData(void)   
{
    Remote_CommandGet(Command);


    return Command_GOT;

}

unsigned char SendData(void)  
{

    //Send_Eular((int16_t)RT_Test.Acc_Uesr1,(int16_t)RT_Test.Acc_User2,(int16_t)RT_Info.AccZ);
    Send_Eular((int16_t)(g_Eular.roll*5729.5779/50),(int16_t)(g_Eular.pitch*5729.5779/50),(int16_t)(g_Eular.yaw*5729.5779/50));
    //Send_Acc((int16_t)RT_Test.Acc_Uesr1,(int16_t)RT_Test.Acc_User2,(int16_t)RT_Info.AccZ);
    //Send_MOTO((int16_t)RT_Test.Acc_Uesr1,(int16_t)RT_Test.Acc_User2, (int16_t)RT_Info.AccX,0);

    return SEND_OK;

}

void Process_PCData(void)
{
    if(Test_M.Test1 == WFY_Test && C_mode.Mode_1 == WFY)
    {
        GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
        Test_Mission();
    }

    if(Fix_State == 1)       // mission of calibration RT_Info.
        Fixed_Mission();
    /*
    if(Fix_State == 2)      // mission of acc sensor calibration.

        Fix_Acc();
*/

}
/******** mission init *******/
void QuadrotorPara_Init(void)
{
    GpioDataRegs.GPBSET.bit.GPIO34=1;
    Test_M.Test1 = Null;
    //FlightControl.OnOff = Drone_Off;
    C_mode.Mode_1 = Bluetooth;

}


/*********test mission**********/
void End_Mission(void)
{

    FlightControl.OnOff = Drone_Off;  

    C_mode.Mode_1 = Bluetooth;

}

void Test_Mission(void)
{
    FlightControl.OnOff = Drone_On;     

    //C_mode.Mode_1 = Bluetooth;   

    FlightControl.DroneMode = Drone_Mode_4Axis;  

    Fly_Mode = Data_Headmode;

}

/**************mission calibration**************/

void Fixed_Mission(void)
{
    float tempP,tempR,tempY;
    int i;
    tempP = 0;
    tempR = 0;
    tempY = 0;
    for(i = 0;i<5000;i++)
    {
        GpioDataRegs.GPBTOGGLE.bit.GPIO34=1;

        tempP += RT_Info.Pitch - 0;

        tempR += RT_Info.Roll - 0;

        tempY += RT_Info.Yaw - 0;
    }

    if(tempP<0)
        Error_Fix.Pitch = -tempP/5000;
    if(tempP>0)
        Error_Fix.Pitch = tempP/5000;
    if(tempR<0)
        Error_Fix.Roll = -tempR/5000;
    if(tempR>0)
        Error_Fix.Roll = tempR/5000;

    Error_Fix.Yaw = tempY/10000;


    GpioDataRegs.GPBSET.bit.GPIO34=1;  
    GpioDataRegs.GPBSET.bit.GPIO34=1;
    Fix_State = 0;
}

