/*
 * timer.c
 *
 *  Created on: 06/04/2019
 *      Author: cyh
 */

#include "F28x_Project.h"
#include "timer.h"
#include "symbol&globe/led.h"
#include "sys_dynamic/fly_sys.h"

unsigned char Led_flag = 0;
unsigned char temp4;

extern unsigned char Test_State;
extern unsigned char Fix_State;

void Timer_Init(void)   
{
/*
    CpuTimer0.RegsAddr = &CpuTimer0Regs;
    CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
    CpuTimer0Regs.TPR.bit.TDDR = 0;
    CpuTimer0Regs.TPRH.all = 0;
    CpuTimer0Regs.TCR.bit.TSS = 1;
    CpuTimer0Regs.TCR.bit.TRB = 1;
    CpuTimer0Regs.TCR.bit.SOFT=0;
    CpuTimer0Regs.TCR.bit.FREE=0;
    //CpuTimer0.InterruptCount = 0;
*/

    InitCpuTimers();   

    ConfigCpuTimer(&CpuTimer0, 200, 2000);

    ConfigCpuTimer(&CpuTimer1, 200, 500000);
    CpuTimer0Regs.TCR.all = 0x4001;
    CpuTimer1Regs.TCR.all = 0x4001;

    EALLOW;
    PieVectTable.TIMER0_INT = &cpu_timer0_isr;
    PieVectTable.TIMER1_INT = &cpu_timer1_isr;
    EDIS;

    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    IER |= M_INT13;  
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;


}

void Timer_Control(unsigned char sta)
{
    if(sta==0)
        CpuTimer0Regs.TCR.bit.TSS = 1;
    if(sta==1)
        CpuTimer0Regs.TCR.bit.TSS = 0;
}

__interrupt void cpu_timer0_isr(void)  // 2ms
{

    CpuTimer0.InterruptCount++;

    temp4 = Data();

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void cpu_timer1_isr(void)
{



    GpioDataRegs.GPATOGGLE.bit.GPIO31=1;

    if(Fix_State == 2)  // for calibration of fly mission.

        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;


    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


