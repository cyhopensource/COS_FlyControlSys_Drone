/*
 * led.c
 *
 *  Created on: 31/03/2019
 *      Author: cyh
 *
 *
 */

#include "F28x_Project.h"
#include "led.h"
#include "sys_inside/delay.h"

void Led_Init(void)   
{

    EALLOW;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
    EDIS;

    GpioDataRegs.GPBSET.bit.GPIO34=1;
    GpioDataRegs.GPASET.bit.GPIO31=1;
    Led_On1();

}


void Led_On0(void)
{
    GpioDataRegs.GPACLEAR.bit.GPIO31=1;
}

void Led_Off0(void)
{
    GpioDataRegs.GPASET.bit.GPIO31=1;
}

void Led_On1(void)
{
    GpioDataRegs.GPBCLEAR.bit.GPIO34=1;
}

void Led_Off1(void)
{

    GpioDataRegs.GPBSET.bit.GPIO34=1;
}

void Sys_led(void)
{
    Led_On0();
    Delay_ms(500);
    Led_Off0();
    Delay_ms(500);
    Led_On0();
    //Delay_ms(500);
}
