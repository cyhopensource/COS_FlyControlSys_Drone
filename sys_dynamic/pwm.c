/*
 * pwm.c
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 */

#include <sys_dynamic/pwm.h>
#include "F28x_Project.h"
#include "pwm.h"



void InitEPwm1Example()
{
    EPwm1Regs.TBPRD = 12499;                       // Set timer period

    EPwm1Regs.CMPA.bit.CMPA = 6250;
    EPwm1Regs.CMPB.bit.CMPB = 6250;
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;          // Slow just to observe on
                                                   // the scope

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;    // Set PWM2A on Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;

    EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;    // Set PWM2B on Zero
    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;

}


//
//  InitEPwm6Example - Initialize EPWM2 configuration
//
void InitEPwm2Example()
{
    EPwm2Regs.TBPRD = 12499;                       // Set timer period

    EPwm2Regs.CMPA.bit.CMPA = 6250;
    EPwm2Regs.CMPB.bit.CMPB = 6250;
    EPwm2Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     // Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;          // Slow just to observe on
                                                   // the scope
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;    // Set PWM2A on Zero
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;

    EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET;    // Set PWM2B on Zero
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;
}

void C28x_BSP_Epwm_Init()
{

    CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;

    InitEPwm1Gpio();
    InitEPwm2Gpio();

    InitEPwm1Example();
    InitEPwm2Example();

}

void PWM_OUTPUT(unsigned int Motor1,    
                unsigned int Motor2,
                unsigned int Motor3,
                unsigned int Motor4)
{
    Motor1+=1000;
    Motor2+=1000;
    Motor3+=1000;
    Motor4+=1000;

    EPwm1Regs.CMPA.bit.CMPA = (unsigned int)(6.25*Motor4);
    EPwm1Regs.CMPB.bit.CMPB = (unsigned int)(6.25*Motor1);
    EPwm2Regs.CMPA.bit.CMPA = (unsigned int)(6.25*Motor2);
    EPwm2Regs.CMPB.bit.CMPB = (unsigned int)(6.25*Motor3);
}



