/*
 * ReceivePCData.c
 *
 *
 *  2019.4.13
 *  accuracy 1/1000.
 *
 *  recive order: Roll、Pitch、Yaw
 *
 *  Created on: 13/04/2019
 *      Author: cyh
 */

#include "PCData.h"
#include "F28x_Project.h"
#include "sci.h"
//#include "FLASH_API/FlashAPI.h"



extern PIDPara PID_ParaInfo;
extern Control_mode C_mode;

unsigned char data_to_send[23];
//static unsigned char state = 0;
unsigned char Test_State = 0;
unsigned char Fix_State = 0;

void PCData_Control(unsigned char input)
{
    if(input == 0xCC)   // calibration mode.
        Fix_State = 1;

    if(input == 0xDD)     // remote mode.
        C_mode.Mode_1 = WFY;
        GpioDataRegs.GPBSET.bit.GPIO34 = 1;

    if(input == 0xBB)     // fly ready.
        Test_State = 1;
    if(input == 0xA1 && Test_State == 1)    //  flyup.
        Test_State = 2;
    if(input == 0xB1 && Test_State == 2)  // land.
        Test_State = 3;

}

//  motor data.
void Send_MOTO(int16_t PWM_MOTO1,int16_t PWM_MOTO2,int16_t PWM_MOTO3,int16_t PWM_MOTO4)
{
    unsigned char  _cnt=0;
    unsigned char  i=0;
    unsigned char sum = 0;

    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0x06;
    data_to_send[_cnt++]=16;
    data_to_send[_cnt++]=PWM_MOTO1>>8;  
    data_to_send[_cnt++]=PWM_MOTO1&0x00ff;   
    data_to_send[_cnt++]=PWM_MOTO2>>8;
    data_to_send[_cnt++]=PWM_MOTO2&0x00ff;
    data_to_send[_cnt++]=PWM_MOTO3>>8;
    data_to_send[_cnt++]=PWM_MOTO3&0x00ff;
    data_to_send[_cnt++]=PWM_MOTO4>>8;
    data_to_send[_cnt++]=PWM_MOTO4&0x00ff;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;

    for(i=0;i<_cnt;i++)
      sum += data_to_send[i];
    data_to_send[_cnt++] = sum;
    Uart_Put_Buf(data_to_send,_cnt);
}

void Send_Acc(int16_t Acc_x,int16_t Acc_y,int16_t Acc_z)
{
    unsigned char  _cnt=0;    
    unsigned char  i=0;
    unsigned char sum = 0;

    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0x02;  
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=Acc_x>>8;
    data_to_send[_cnt++]=Acc_x;
    data_to_send[_cnt++]=Acc_y>>8;
    data_to_send[_cnt++]=Acc_y;
    data_to_send[_cnt++]=Acc_z>>8;
    data_to_send[_cnt++]=Acc_z;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;

    data_to_send[3] = _cnt-4;

    for(i=0;i<_cnt;i++)
      sum += data_to_send[i];
    data_to_send[_cnt++] = sum;
    Uart_Put_Buf(data_to_send,_cnt);
}


void Send_Eular(int16_t roll,int16_t pitch,int16_t yaw)   // data from pc software
{
    unsigned char  _cnt=0;    
    unsigned char  i=0;
    unsigned char sum = 0;

    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0x01;  
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=roll>>8;  
    data_to_send[_cnt++]=roll;  
    data_to_send[_cnt++]=pitch>>8;
    data_to_send[_cnt++]=pitch;
    data_to_send[_cnt++]=yaw>>8;
    data_to_send[_cnt++]=yaw;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=0;
    data_to_send[_cnt++]=1;

    data_to_send[3] = _cnt-4;

    for(i=0;i<_cnt;i++)
      sum += data_to_send[i];
    data_to_send[_cnt++] = sum;
    Uart_Put_Buf(data_to_send,_cnt);
}


//  data check_sum
static void ANO_DT_Send_Check(u8 head, u8 check_sum)
{
    int i;
    data_to_send[0]=0xAA;
    data_to_send[1]=0xAA;
    data_to_send[2]=0xEF;
    data_to_send[3]=2;
    data_to_send[4]=head;
    data_to_send[5]=check_sum;


    u8 sum = 0;
    for(i=0;i<6;i++)
        sum += data_to_send[i];
    data_to_send[6]=sum;

    Uart_Put_Buf(data_to_send,7);
}



void ANO_DT_Data_Receive_Prepare(u8 data)
{
    static u8 RxBuffer[50];
    static u8 _data_len = 0,_data_cnt = 0;
    static u8 state = 0;

    if(state==0&&data==0xAA)
    {
        state=1;
        RxBuffer[0]=data;
    }
    else if(state==1&&data==0xAF)
    {
        state=2;
        RxBuffer[1]=data;
    }
    else if(state==2&&data<0XF1)
    {
        state=3;
        RxBuffer[2]=data;
    }
    else if(state==3&&data<50)
    {
        state = 4;
        RxBuffer[3]=data;
        _data_len = data;
        _data_cnt = 0;
    }
    else if(state==4&&_data_len>0)
    {
        _data_len--;
        RxBuffer[4+_data_cnt++]=data;
        if(_data_len==0)
            state = 5;
    }
    else if(state==5)
    {
        state = 0;
        RxBuffer[4+_data_cnt]=data;
        ANO_DT_Data_Receive_Anl(RxBuffer,_data_cnt+5);
    }
    else
        state = 0;
}


void ANO_DT_Data_Receive_Anl(u8 *data_buf,u8 num)
{
    int i;
    u8 sum = 0;
    for(i=0;i<(num-1);i++)
        sum += *(data_buf+i);
    //if(!(sum==*(data_buf+num-1)))
        //return;
    //if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))     return;
    /*
    if(*(data_buf+2)==0X01)   //   用于飞控校准.
    {
        if(*(data_buf+4)==0X01)
            mpu6050.Acc_CALIBRATE = 1;
        if(*(data_buf+4)==0X02)
            mpu6050.Gyro_CALIBRATE = 1;
        if(*(data_buf+4)==0X03)
        {
            mpu6050.Acc_CALIBRATE = 1;
            mpu6050.Gyro_CALIBRATE = 1;
        }
    }
    */
    /*
    if(*(data_buf+2)==0X02)    //    用于飞控特殊功能数据的发送.
    {
        if(*(data_buf+4)==0X01)
        {
            f.send_pid1 = 1;
            f.send_pid2 = 1;
            f.send_pid3 = 1;
            f.send_pid4 = 1;
            f.send_pid5 = 1;
            f.send_pid6 = 1;
        }
        if(*(data_buf+4)==0X02)
        {

        }
        if(*(data_buf+4)==0XA0)
        {
            f.send_version = 1;
        }
        if(*(data_buf+4)==0XA1)
        {
            Para_ResetToFactorySetup();
        }
    }
    */
    if(*(data_buf+2)==0X10)                             //PID1
    {
        PID_ParaInfo.RollRate.Kp  = 0.001*((*(data_buf+4)<<8)|*(data_buf+5));
        PID_ParaInfo.RollRate.Ki  = 0.001*((*(data_buf+6)<<8)|*(data_buf+7));
        PID_ParaInfo.RollRate.Kd  = 0.001*((*(data_buf+8)<<8)|*(data_buf+9));
        PID_ParaInfo.PitchRate.Kp = 0.001*((*(data_buf+10)<<8)|*(data_buf+11));
        PID_ParaInfo.PitchRate.Ki = 0.001*((*(data_buf+12)<<8)|*(data_buf+13));
        PID_ParaInfo.PitchRate.Kd = 0.001*((*(data_buf+14)<<8)|*(data_buf+15));
        PID_ParaInfo.YawRate.Kp   = 0.001*((*(data_buf+16)<<8)|*(data_buf+17));
        PID_ParaInfo.YawRate.Ki   = 0.001*((*(data_buf+18)<<8)|*(data_buf+19));
        PID_ParaInfo.YawRate.Kd   = 0.001*((*(data_buf+20)<<8)|*(data_buf+21));
        ANO_DT_Send_Check(*(data_buf+2),sum);
        //Write_Config();                           // write into FLASH.

                //Param_SavePID();
    }
    if(*(data_buf+2)==0X11)                             //PID2
    {
        PID_ParaInfo.Roll.Kp     = 0.001*((*(data_buf+4)<<8)|*(data_buf+5));
        PID_ParaInfo.Roll.Ki     = 0.001*((*(data_buf+6)<<8)|*(data_buf+7));
        PID_ParaInfo.Roll.Kd     = 0.001*((*(data_buf+8)<<8)|*(data_buf+9));
        PID_ParaInfo.Pitch.Kp     = 0.001*((*(data_buf+10)<<8)|*(data_buf+11));
        PID_ParaInfo.Pitch.Ki     = 0.001*((*(data_buf+12)<<8)|*(data_buf+13));
        PID_ParaInfo.Pitch.Kd     = 0.001*((*(data_buf+14)<<8)|*(data_buf+15));
        PID_ParaInfo.Yaw.Kp   = 0.001*((*(data_buf+16)<<8)|*(data_buf+17));
        PID_ParaInfo.Yaw.Ki    = 0.001*((*(data_buf+18)<<8)|*(data_buf+19));
        PID_ParaInfo.Yaw.Kd     = 0.001*((*(data_buf+20)<<8)|*(data_buf+21));
        ANO_DT_Send_Check(*(data_buf+2),sum);
        //Write_Config();
                //Param_SavePID();
    }
    if(*(data_buf+2)==0X12)                             //PID3
    {
        PID_ParaInfo.Height.Kp  = 0.001*((*(data_buf+4)<<8)|*(data_buf+5) );
        PID_ParaInfo.Height.Ki  = 0.001*((*(data_buf+6)<<8)|*(data_buf+7) );
        PID_ParaInfo.Height.Kd  = 0.001*((*(data_buf+8)<<8)|*(data_buf+9) );
        PID_ParaInfo.HeightRate.Kp = 0.001*((*(data_buf+10)<<8)|*(data_buf+11) );
        PID_ParaInfo.HeightRate.Ki = 0.001*((*(data_buf+12)<<8)|*(data_buf+13) );
        PID_ParaInfo.HeightRate.Kd = 0.001*((*(data_buf+14)<<8)|*(data_buf+15) );
        //ctrl_2.PID[PIDYAW].kp   = 0.001*((*(data_buf+16)<<8)|*(data_buf+17) );
        //ctrl_2.PID[PIDYAW].ki   = 0.001*((*(data_buf+18)<<8)|*(data_buf+19) );
        //ctrl_2.PID[PIDYAW].kd   = 0.001*((*(data_buf+20)<<8)|*(data_buf+21) );
        ANO_DT_Send_Check(*(data_buf+2),sum);
                //Param_SavePID();
    }
    if(*(data_buf+2)==0X13)                             //PID4
    {
        ANO_DT_Send_Check(*(data_buf+2),sum);
    }
    if(*(data_buf+2)==0X14)                             //PID5
    {
        ANO_DT_Send_Check(*(data_buf+2),sum);
    }
    if(*(data_buf+2)==0X15)                             //PID6
    {
        ANO_DT_Send_Check(*(data_buf+2),sum);
    }
}





