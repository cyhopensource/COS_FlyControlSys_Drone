/*
 * PID_control.c
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 *
 *
 */

#include "F28x_Project.h"
#include "PID_control.h"
#include "sys_dynamic/pwm.h"
#include "algorithm/PID_control.h"
#include "algorithm/math2.h"
#include "math.h"

//#include "algorithm/math.h"

#define PI 3.1415926

extern Thrust UAVThrust;
extern Throttle Throttle_Info;
extern DroneFlightControl FlightControl;

extern PIDOut OriginalPitch,OriginalRoll,OriginalYaw,OriginalPosX,OriginalPosY,OriginalPosZ,
OriginalPitchRate,OriginalRollRate,OriginalYawRate,OriginalVelX,OriginalVelY,OriginalVelZ,
OriginalFlowX,OriginalFlowY,OriginalFlowVelX,OriginalFlowVelY,OriginalAccZ,OriginalHeight,OriginalHeightRate;

extern PIDPara PID_ParaInfo;
extern DroneRTInfo RT_Info;   
extern DroneTargetInfo Target_Info;
extern RemoteControl RockerControl;

extern SensorData Sensor_Info;

extern Remote_Command Command_Uint,Command;    // command.



float PID_Control(PID *PIDpara, PIDOut *PIDstatus, float expect_PID, float feedback_PID
                                , float PIDtime, float Integrallimiter,float LowpassFilter)
{   // Integrallimiter 

    PIDstatus->error = expect_PID - feedback_PID;   
    PIDstatus->differential = (PIDstatus->error - PIDstatus->lasterror)/PIDtime;  
    PIDstatus->differential = PIDstatus->differentialFliter + (PIDtime / (LowpassFilter + PIDtime)) * (PIDstatus->differential - PIDstatus->differentialFliter);

    PIDstatus->differentialFliter = PIDstatus->differential;

    PIDstatus->lasterror = PIDstatus->error;

    PIDstatus->pOut = PIDpara->Kp * PIDstatus->error;      // ratio output.
    PIDstatus->iOut += PIDpara->Ki * PIDstatus->error; 
    PIDstatus->dOut = PIDpara->Kd * PIDstatus->differential;   

    PIDstatus->iOut = Limits_data(PIDstatus->iOut,Integrallimiter,-Integrallimiter);   
    PIDstatus->value = PIDstatus->pOut + PIDstatus->iOut + PIDstatus->dOut;  

    return PIDstatus->value;   

}

/***************************(Yaw , roll , pitch) ***************************/

void Attitude_control(float PitchCalibration,float RollCalibration,float YawCalibration)
{
    float pitchErro = (Target_Info.Pitch-(RT_Info.Pitch-PitchCalibration));   
    OriginalPitch.value = PID_ParaInfo.Pitch.Kp * pitchErro;    
    if(FlightControl.DroneMode!=Drone_Mode_RatePitch)
    {
        UAVThrust.PitchThrust = PID_Control(&PID_ParaInfo.PitchRate,&OriginalPitchRate,OriginalPitch.value,
                                                                RT_Info.ratePitch,0.005,80,lowpass_filter);
    }
    else
    {
        UAVThrust.PitchThrust = PID_Control(&PID_ParaInfo.PitchRate,&OriginalPitchRate,Target_Info.RatePitch/100,
                                                                RT_Info.ratePitch,0.005,80,lowpass_filter);
    }

    float rollErro = (Target_Info.Roll-(RT_Info.Roll-RollCalibration));    
    OriginalRoll.value = PID_ParaInfo.Roll.Kp * rollErro;
    if(FlightControl.DroneMode!=Drone_Mode_RateRoll)
    {
        UAVThrust.RollThrust = PID_Control(&PID_ParaInfo.RollRate,&OriginalRollRate,OriginalRoll.value,
                                                                  RT_Info.rateRoll,0.005,80,lowpass_filter);
    }
    else
    {
        UAVThrust.RollThrust = PID_Control(&PID_ParaInfo.RollRate,&OriginalRollRate,Target_Info.RateRoll/100,
                                                                   RT_Info.rateRoll,0.005,80,lowpass_filter);
    }

    UAVThrust.YawThrust = PID_Control(&PID_ParaInfo.YawRate,&OriginalYaw,0,RT_Info.rateYaw,0.005,80,lowpass_filter);

    float yawErro = (Target_Info.Yaw - (RT_Info.Yaw - YawCalibration));  
    OriginalYaw.value = PID_ParaInfo.Yaw.Kp*yawErro;
    if(FlightControl.DroneMode!=Drone_Mode_RateYaw)
        {
            UAVThrust.YawThrust = PID_Control(&PID_ParaInfo.YawRate,&OriginalYawRate,OriginalYaw.value,
                                                                      RT_Info.rateYaw,0.005,80,lowpass_filter);
        }
    else
        {
            UAVThrust.YawThrust = PID_Control(&PID_ParaInfo.YawRate,&OriginalYawRate,Target_Info.RateYaw/100,
                                                                       RT_Info.rateYaw,0.005,80,lowpass_filter);
        }

    Calculate_Thrust();     

}


void Throttle_Angle_Compensate(void)
{
  float CosPitch_CosRoll=ABS(cos(RT_Info.Pitch/180*PI)*cos(RT_Info.Roll/180*PI));
  float Temp=0;
  if(CosPitch_CosRoll>=0.999999f)  CosPitch_CosRoll=0.999999f;
  if(CosPitch_CosRoll<=0.000001f)  CosPitch_CosRoll=0.000001f;
  if(CosPitch_CosRoll<=0.50f)  CosPitch_CosRoll=0.50f;//Pitch,Roll 30
  if(UAVThrust.HeightThrust != 0)
  {
      Temp=(uint16_t)(MAX(ABS(100*RT_Info.Pitch),ABS(100*RT_Info.Roll)));
      Temp=Limits_data(9000-Temp,3000,0)/(3000*CosPitch_CosRoll);
      UAVThrust.BasicThrust= 530*Temp; 
      UAVThrust.BasicThrust=(uint16_t)(Limits_data(UAVThrust.BasicThrust,570,530));
  }
  else UAVThrust.BasicThrust= 530;
}

/**********PID with motor*********/

void Calculate_Thrust()
{

    //UAVThrust.BasicThrust= 230;
    if(FlightControl.DroneMode==Drone_Mode_4Axis)
    {


        Throttle_Info.M1 =  - UAVThrust.PitchThrust
                            + UAVThrust.RollThrust//- UAVThrust.RollThrust
                            - UAVThrust.YawThrust
                            + UAVThrust.HeightThrust
                            + UAVThrust.BasicThrust;

        Throttle_Info.M2 =  + UAVThrust.PitchThrust
                            + UAVThrust.RollThrust//- UAVThrust.RollThrust
                            + UAVThrust.YawThrust
                            + UAVThrust.HeightThrust
                            + UAVThrust.BasicThrust;

        Throttle_Info.M3 =  + UAVThrust.PitchThrust
                            - UAVThrust.RollThrust//+ UAVThrust.RollThrust
                            - UAVThrust.YawThrust
                            + UAVThrust.HeightThrust
                            + UAVThrust.BasicThrust;

        Throttle_Info.M4 =  - UAVThrust.PitchThrust
                            - UAVThrust.RollThrust//+ UAVThrust.RollThrust
                            + UAVThrust.YawThrust
                            + UAVThrust.HeightThrust
                            + UAVThrust.BasicThrust;

    }

    else if(FlightControl.DroneMode==Drone_Mode_Pitch || FlightControl.DroneMode==Drone_Mode_RatePitch)
    {
        Throttle_Info.M1 = - UAVThrust.PitchThrust + UAVThrust.BasicThrust;
        Throttle_Info.M2 = + UAVThrust.PitchThrust + UAVThrust.BasicThrust;
        Throttle_Info.M3 = + UAVThrust.PitchThrust + UAVThrust.BasicThrust;
        Throttle_Info.M4 = - UAVThrust.PitchThrust + UAVThrust.BasicThrust;
    }
    else if(FlightControl.DroneMode==Drone_Mode_Roll || FlightControl.DroneMode==Drone_Mode_RateRoll)
    {
        Throttle_Info.M1 = - UAVThrust.RollThrust + UAVThrust.BasicThrust;
        Throttle_Info.M2 = - UAVThrust.RollThrust + UAVThrust.BasicThrust;
        Throttle_Info.M3 = + UAVThrust.RollThrust + UAVThrust.BasicThrust;
        Throttle_Info.M4 = + UAVThrust.RollThrust + UAVThrust.BasicThrust;
    }

    if(Throttle_Info.M1 > 900)  Throttle_Info.M1=900;
    if(Throttle_Info.M2 > 900)  Throttle_Info.M2=900;
    if(Throttle_Info.M3 > 900)  Throttle_Info.M3=900;
    if(Throttle_Info.M4 > 900)  Throttle_Info.M4=900;

    if(Throttle_Info.M1 < 50)  Throttle_Info.M1=50;
    if(Throttle_Info.M2 < 50)  Throttle_Info.M2=50;
    if(Throttle_Info.M3 < 50)  Throttle_Info.M3=50;
    if(Throttle_Info.M4 < 50)  Throttle_Info.M4=50;

    PWM_OUTPUT(Throttle_Info.M1,Throttle_Info.M2,Throttle_Info.M3,Throttle_Info.M4);  

}
/********************height PID control****************/

void Height_control(float HeightCalibration)
{
    float HeightErro = (Target_Info.Height - (RT_Info.Height - HeightCalibration));

    OriginalHeight.value = PID_ParaInfo.Yaw.Kp*HeightErro;
    if(FlightControl.DroneMode!=Drone_Mode_RateYaw)

    {
        UAVThrust.HeightThrust = PID_Control(&PID_ParaInfo.HeightRate,&OriginalHeightRate,OriginalHeight.value,
                                          RT_Info.rateHeight,0.005,80,lowpass_filter);
    }
    else
    {
        UAVThrust.HeightThrust = PID_Control(&PID_ParaInfo.HeightRate,&OriginalHeightRate,Target_Info.RateHeight/100,
                                          RT_Info.rateHeight,0.005,80,lowpass_filter);
    }

}

/*******************position PID control  ****************/


void Position_control(unsigned char Data_flag,float Climb,float Decline)
{

    static float TgtHeight = 0;
    if(FlightControl.landFlag==1)
    {
        TgtHeight = TgtHeight - Decline;
        if(RT_Info.Height<0.10f)
        {
            FlightControl.OnOff = Drone_Land;
            FlightControl.landFlag = 0;
            TgtHeight = 0;
        }
    }
    else{

        if(TgtHeight < Target_Info.Height)
        {
            TgtHeight = TgtHeight + Climb;
        }
        else
        {
            TgtHeight = Target_Info.Height;
        }
    }

    float heightErro = TgtHeight - RT_Info.Height; 
    OriginalPosZ.value = PID_ParaInfo.PosZ.Kp * heightErro;

    UAVThrust.HeightThrust = PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.01,120,lowpass_filter);

    //if(RT_Info.Height > 0.1f)
    if(RT_Info.Height >= 0.0f)
    {
        switch (Data_flag)  // different mode to fly.
        {

            case 0:   
                Target_Info.Pitch = 0.04f * RockerControl.XaxisPos;
                Target_Info.Roll = 0.04f * RockerControl.YaxisPos;
                break;

            case 1:

                break;

            case 2:    


                if((int16_t)Command.Pitch == 0  && (int16_t)Command.Roll == 0 &&
                        Sensor_Info.Raspberry_Xaxis!=0 && Sensor_Info.Raspberry_Yaxis!=0)
                {
                    OriginalPosX.value = PID_ParaInfo.PosX.Kp * RT_Info.PointX;  

                    Target_Info.Pitch =  Limits_data( - PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
                                                                    RT_Info.PointX_V,0.005,3,lowpass_filter) , 6 , -6 );

                    OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;

                    Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
                                                                RT_Info.PointY_V,0.005,3,lowpass_filter) , 6 , -6);
                }
                else
                {
                    Target_Info.Pitch = 0.03f * RockerControl.XaxisPos;
                    Target_Info.Roll = 0.03f * RockerControl.YaxisPos;
                }

                break;

            case 3:    // flow the black line.

                OriginalPosX.value = PID_ParaInfo.PosX.Kp * RT_Info.PointX;

                Target_Info.Pitch = - PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
                                                  RT_Info.PointX_V,0.01,4,lowpass_filter);

                OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;

                Target_Info.Roll = PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
                                               RT_Info.PointY_V,0.01,4,lowpass_filter);

            case 4:

                    if(Command.Pitch == 0  && Command.Roll == 0)  
                    {
               
                        OriginalFlowX.value =   PID_ParaInfo.FlowX.Kp  * RT_Info.FlowX;
                        OriginalFlowY.value =   PID_ParaInfo.FlowY.Kp  * RT_Info.FlowY;

                        Target_Info.Pitch = - Limits_data( PID_Control(&PID_ParaInfo.FlowVelX,&OriginalFlowVelX,OriginalFlowX.value,
                                                                       RT_Info.FlowX_V,0.005,1.5,lowpass_filter) , 25, -25 ) ;

                        Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.FlowVelY,&OriginalFlowVelY,OriginalFlowY.value,
                                                                    RT_Info.FlowY_V,0.005,1.5,lowpass_filter) , 25, -25 );
                    }
                    else
                    {
                        Target_Info.Pitch = 50*Command.Pitch;
                        Target_Info.Roll = 50*Command.Roll;
                    }


                break;


            case 5:


                break;

            case 6:

                break;

            default:

                break;
        }

    }

}

/****************PID angle protector*****************/
void Safety_Protection(void)
{
  if(RT_Info.Pitch >=30 || RT_Info.Pitch <= -30 || RT_Info.Roll >= 30 || RT_Info.Roll <= -30)
  {
      PWM_OUTPUT(0,0,0,0);
      while(1);
  }

}



