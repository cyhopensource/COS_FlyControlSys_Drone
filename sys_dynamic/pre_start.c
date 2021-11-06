/*
 * pre_start.c
 *
 *  Created on: 01/04/2019
 *      Author: cyh
 *
 *  2019.4.1
 */

#include "F28x_Project.h"
#include "pre_start.h"
#include "sys_dynamic/pwm.h"
#include "algorithm/PID_control.h"

unsigned char StartFly;
unsigned char Flying;

extern PIDOut OriginalPitch,OriginalRoll,OriginalYaw,OriginalHeight,OriginalPosX,OriginalPosY,OriginalPosZ,
                    OriginalPitchRate,OriginalRollRate,OriginalYawRate,OriginalVelX,OriginalVelY,OriginalVelZ,
                    OriginalHeightRate;
extern PIDPara PID_ParaInfo;

extern DroneRTInfo RT_Info;    
extern DroneFlightControl FlightControl;

Uint16 Preparationtime = 0;
float PreparationPitch = 0;
float PreparationRoll = 0;
float PreparationYaw = 0;
unsigned char PreparationFlag = 0;

void Pre_fly(void)
{


    //while (1)
    //{
    if(FlightControl.OnOff == Drone_On)// && RT_Info.Height >= 0.01f)
    {
        if(FlightControl.DroneMode == Drone_Mode_4Axis)
        {
            if(Preparationtime < 800)  
            {
                Preparationtime ++;
                PreparationPitch += RT_Info.Pitch;
                PreparationRoll += RT_Info.Roll;
                PWM_OUTPUT(300,300,300,300);    // motor speed of ratation init
                if(Preparationtime == 800)
                    PreparationFlag = 1;
            }
            else
            {

                if(PreparationFlag)
                {
                    PreparationPitch /= 800;
                    PreparationRoll /= 800;
                    PreparationFlag = 0;
                }
                Flying = 1;
                StartFly = 1;
                Attitude_control(PreparationPitch,PreparationRoll,PreparationYaw);
                Safety_Protection();   
            }
        }
        else
        {
            Flying = 0;   

            Attitude_control(0,0,0);    // PID output for motor
            Height_control(0);   
        }
    }
    else     
            {
                PreparationFlag = true;
                PreparationPitch = 0;
                PreparationRoll = 0;
                PreparationYaw = 0;
                Preparationtime = 0;
                StartFly = 0;
                OriginalPitchRate.iOut = 0;
                OriginalRollRate.iOut = 0;
                OriginalYaw.iOut = 0;
                OriginalVelZ.iOut = 0;
                OriginalVelX.iOut = 0;
                OriginalVelY.iOut = 0;
                PWM_OUTPUT(0,0,0,0);
            }

}


//}




