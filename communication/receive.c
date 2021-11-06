/*
 * receive.c
 *
 *  Created on: 03/04/2019
 *      Author: cyh
 */

#include <algorithm/math2.h>
#include "F28x_Project.h"
#include "receive.h"
#include "sys_dynamic/pwm.h"


int32_t ulock_time,lock_time;
int16_t lock = 1;
extern Eular g_Eular;  


extern Chx_Width Chx;
extern Remote_Command Command_Uint,Command;
extern Test_Mode Test_M;

extern unsigned char Fix_State;

#define PI_2 3.1415926

// read remote signal
void ReceiveData_Norm(Remote_Command *Command,Chx_Width *p)
{
    Command->Roll=      Constraint_f(((float)p->Ch6/200-999)/1000.0f,0.0,1.0);
    Command->Pitch=     Constraint_f(((float)p->Ch5/200-999)/1000.0f,0.0,1.0);
    Command->Throttle=  Constraint_f(((float)p->Ch2/200-999)/1000.0f,0.0,1.0);     
    Command->Yaw=       Constraint_f(((float)p->Ch7/200-999)/1000.0f,0.0,1.0);

}

void ReceiveData_Convert(Remote_Command *Command_Uint,Remote_Command *Command)
{
    Command->Throttle=  (Command_Uint->Throttle);
    Command->Pitch   =  (Command_Uint->Pitch - 0.5f) * PI_2 / 6.0 * 2.0f;
    Command->Roll    =  (Command_Uint->Roll - 0.5f) * PI_2 / 6.0 * 2.0f;

    Command->Yaw = Constraint_f(Command->Yaw + 0.005*(Command_Uint->Yaw-0.499f) * PI_2 * 2.0f,-PI_2,PI_2);
}

void Remote_CommandGet(Remote_Command *Command)  
{
    int i;
    ReceiveData_Norm(&Command_Uint,&Chx);
    ReceiveData_Convert(&Command_Uint,Command);

    if((Chx.Ch2 + Chx.Ch5) <410000)
    {
        for(i = 0;i<10000;i++)
            GpioDataRegs.GPBSET.bit.GPIO34 = 1;   


        Test_M.Test1 = WFY_Test;

    }

    while(Chx.Ch2 < 230000 && Test_M.Test1 == WFY_Test)   
    {
        PWM_OUTPUT(0,0,0,0);
        Chx.Ch2 = 0;

    }

}



void Lock_Control(Remote_Command *command)
{
    if(command->Pitch<=0.1&&command->Roll<=0.1&&command->Yaw>=0.9&&command->Throttle<=0.1)
    {
        ulock_time++;
        if(command->Pitch<=0.1&&command->Roll<=0.1&&command->Yaw>=0.9&&command->Throttle<=0.1&&ulock_time>100)
        {
            lock=0;
            Command.Yaw = g_Eular.yaw;
        }
    }
    else
        ulock_time=0;
    if(command->Pitch<=0.1&&command->Roll<=0.1&&command->Yaw<=0.1&&command->Throttle<=0.1)
    {
            lock_time++;
        if(command->Pitch<=0.1&&command->Roll<=0.1&&command->Yaw<=0.1&&command->Throttle<=0.1&&lock_time>100)
            lock=1;
    }
    else
        lock_time=0;

}
