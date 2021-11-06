/*
 * send.c
 *
 *  Created on: 03/04/2019
 *      Author: cyh
 *
 *
 */

#include "F28x_Project.h"
#include "send.h"
#include "communication/sci.h"
#include "algorithm/math2.h"

extern DroneRTInfo RT_Info;
extern SensorData Sensor_Info;
extern PIDPara PID_ParaInfo;


unsigned char GyroDataToPC[16];
unsigned char DataAllToPC[20];

int     Mag_maxx=0, Mag_maxy=0, Mag_maxz=0;
int     Mag_minx=-0,Mag_miny=-0,Mag_minz=-0;


void sendRTInfo(void)    
{
    static unsigned char sendFlag = 1;
    unsigned char DataToPC[16];

    switch (sendFlag)
    {
        case 1:
            DataToPC[0]=0X55; 
            DataToPC[1]=0XAA;
            DataToPC[2]=0X00;

            FloatToUnsignedchar(3,RT_Info.Pitch ,DataToPC);

            FloatToUnsignedchar(7,RT_Info.Roll ,DataToPC);

            FloatToUnsignedchar(11,RT_Info.Yaw ,DataToPC);

            DataToPC[15]=0x55;

            sendFlag ++;
            break;
        case 2:
            DataToPC[0]=0X55;
            DataToPC[1]=0XAA;
            DataToPC[2]=0X01;

            FloatToUnsignedchar(3,RT_Info.Height ,DataToPC);

            FloatToUnsignedchar(7,RT_Info.PointX,DataToPC);

            FloatToUnsignedchar(11,RT_Info.PointY,DataToPC);

            DataToPC[15]=(unsigned int)(RT_Info.batteryVoltage * 10) ;

            sendFlag --;
            break;

        default:
            break;
    }

    scib_msg(DataToPC);
}

void sendGyroData(void)   
{
    //unsigned char GyroDataToPC[16];

    GyroDataToPC[0]=0X55;
    GyroDataToPC[1]=0XAA;

    GyroDataToPC[2]=0X20;

    FloatToUnsignedchar(3,RT_Info.GyroX,GyroDataToPC);
    FloatToUnsignedchar(7,RT_Info.GyroY,GyroDataToPC);
    FloatToUnsignedchar(11,RT_Info.GyroZ,GyroDataToPC);
    scib_msg(GyroDataToPC);
}

void sendAccData(void) 
{
    unsigned char AccDataToPC[16];

    AccDataToPC[0]=0X55;
    AccDataToPC[1]=0XAA;

    AccDataToPC[2]=0X21;

    FloatToUnsignedchar(3,RT_Info.accXaxis,AccDataToPC);
    FloatToUnsignedchar(7,RT_Info.accYaxis,AccDataToPC);
    FloatToUnsignedchar(11,RT_Info.accZaxis,AccDataToPC);
    scib_msg(AccDataToPC);
}

void sendMagData(void)
{
    unsigned char MagDataToPC[16];

    MagDataToPC[0]=0X55;
    MagDataToPC[1]=0XAA;

    MagDataToPC[2]=0X22;

    FloatToUnsignedchar(3,RT_Info.MagX,MagDataToPC);
    FloatToUnsignedchar(7,RT_Info.MagY,MagDataToPC);
    FloatToUnsignedchar(11,RT_Info.MagZ,MagDataToPC);
    scib_msg(MagDataToPC);
}


void sendPositionData(void)
{
    unsigned char PosDataToPC[16];

    PosDataToPC[0]=0X55;
    PosDataToPC[1]=0XAA;

    PosDataToPC[2]=0X23;

    FloatToUnsignedchar(3,RT_Info.Height_V *100,PosDataToPC);
    FloatToUnsignedchar(7,Sensor_Info.FlowVelX ,PosDataToPC);
    FloatToUnsignedchar(11,Sensor_Info.FlowVelY,PosDataToPC);
    scib_msg(PosDataToPC);
}

void sendUserData(void)
{
    unsigned char UserDataToPC[16];

    UserDataToPC[0]=0X55;
    UserDataToPC[1]=0XAA;

    UserDataToPC[2]=0X24;

    FloatToUnsignedchar(3,RT_Info.GyroX *100 ,UserDataToPC);
    FloatToUnsignedchar(7,RT_Info.FlowY_V *100 ,UserDataToPC);
    FloatToUnsignedchar(11,RT_Info.accZaxis *100 ,UserDataToPC);
    scib_msg(UserDataToPC);
}

void sendParaInfo(void)    
{
    unsigned char paraToPC[16];

    paraToPC[0]=0X55;
    paraToPC[1]=0XAA;

    paraToPC[2]=0X02;
    FloatToUnsignedchar(3,PID_ParaInfo.Pitch.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.Pitch.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.Pitch.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X03;
    FloatToUnsignedchar(3,PID_ParaInfo.Roll.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.Roll.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.Roll.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X04;
    FloatToUnsignedchar(3,PID_ParaInfo.PitchRate.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.PitchRate.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.PitchRate.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X05;
    FloatToUnsignedchar(3,PID_ParaInfo.RollRate.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.RollRate.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.RollRate.Kd,paraToPC);
    scib_msg(paraToPC);


    paraToPC[2]=0X06;
    FloatToUnsignedchar(3,PID_ParaInfo.Yaw.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.Yaw.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.Yaw.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X07;
    FloatToUnsignedchar(3,PID_ParaInfo.YawRate.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.YawRate.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.YawRate.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X08;
    FloatToUnsignedchar(3,PID_ParaInfo.PosZ.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.PosZ.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.PosZ.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X09;
    FloatToUnsignedchar(3,PID_ParaInfo.VelZ.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.VelZ.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.VelZ.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X0A;
    FloatToUnsignedchar(3,PID_ParaInfo.PosX.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.PosX.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.PosX.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X0B;
    FloatToUnsignedchar(3,PID_ParaInfo.PosY.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.PosY.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.PosY.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X0C;
    FloatToUnsignedchar(3,PID_ParaInfo.VelX.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.VelX.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.VelX.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X0D;
    FloatToUnsignedchar(3,PID_ParaInfo.VelY.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.VelY.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.VelY.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X0E;
    FloatToUnsignedchar(3,PID_ParaInfo.FlowX.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.FlowX.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.FlowX.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X0F;
    FloatToUnsignedchar(3,PID_ParaInfo.FlowY.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.FlowY.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.FlowY.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X10;
    FloatToUnsignedchar(3,PID_ParaInfo.FlowVelX.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.FlowVelX.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.FlowVelX.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X11;
    FloatToUnsignedchar(3,PID_ParaInfo.FlowVelY.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.FlowVelY.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.FlowVelY.Kd,paraToPC);
    scib_msg(paraToPC);

    paraToPC[2]=0X12;
    FloatToUnsignedchar(3,PID_ParaInfo.AccZ.Kp,paraToPC);
    FloatToUnsignedchar(7,PID_ParaInfo.AccZ.Ki,paraToPC);
    FloatToUnsignedchar(11,PID_ParaInfo.AccZ.Kd,paraToPC);
    scib_msg(paraToPC);
}

void sendRTOffset(void)
{
    int temp;
    unsigned char dataToPC[16];

    dataToPC[0]=0X55;
    dataToPC[1]=0XAA;
    dataToPC[2]=0X25;

    temp = Mag_minx;
    dataToPC[3] = temp & 0x00ff ;
    dataToPC[4] = (temp  & 0xff00 ) >>8 ;

    temp = Mag_maxx;
    dataToPC[5] = temp & 0x00ff;
    dataToPC[6] = (temp  & 0xff00 ) >>8;

    temp = Mag_miny;
    dataToPC[7] =  temp & 0x00ff;
    dataToPC[8] = (temp  & 0xff00 ) >>8;

    temp = Mag_maxy;
    dataToPC[9] =  temp & 0x00ff;
    dataToPC[10] = (temp  & 0xff00 ) >>8;

    temp = Mag_minz;
    dataToPC[11] =  temp & 0x00ff;
    dataToPC[12] = (temp  & 0xff00 ) >>8;

    temp = Mag_maxz;
    dataToPC[13] =  temp & 0x00ff;
    dataToPC[14] = (temp  & 0xff00 ) >>8;

    dataToPC[15] = 0xAA;
    scib_msg(dataToPC);
}

