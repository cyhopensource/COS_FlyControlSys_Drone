/*
 * cap.c
 *
 *  Created on: 28/03/2019
 *      Author: cyh
 *
 *
 */

#include "F28x_Project.h"
#include "cap.h"
#include "communication/receive.h"

#define BUFFER_SIZE 256

#define PWM3_TIMER_MIN     10
#define PWM3_TIMER_MAX     8000

#define EPWM_TIMER_UP   1
#define EPWM_TIMER_DOWN 0

Uint32  EPwm3TimerDirection;
Uint32 ECapResults[BUFFER_SIZE];
uint32_t count = 0,count1 = 0,count2 = 0;

Chx_Width Chx;
extern Remote_Command Command_Uint,Command;


void Cap_init(void)   
{

    EALLOW;
    InputXbarRegs.INPUT7SELECT = 131;   // X-bar.
    InputXbarRegs.INPUT8SELECT = 130;
    InputXbarRegs.INPUT9SELECT = 63;
    InputXbarRegs.INPUT10SELECT = 64;
    InputXbarRegs.INPUT11SELECT = 26;
    InputXbarRegs.INPUT12SELECT = 27;
    EDIS;

    GPIO_SetupPinOptions(131,GPIO_INPUT,GPIO_ASYNC);
    GPIO_SetupPinOptions(130,GPIO_INPUT,GPIO_ASYNC);
    GPIO_SetupPinOptions(63,GPIO_INPUT,GPIO_ASYNC);
    GPIO_SetupPinOptions(64,GPIO_INPUT,GPIO_ASYNC);
    GPIO_SetupPinOptions(26,GPIO_INPUT,GPIO_ASYNC);
    GPIO_SetupPinOptions(27,GPIO_INPUT,GPIO_ASYNC);

    //InitEPwm3Gpio();  // GPIO4 - EPwm3A.

    EALLOW;
    CpuSysRegs.PCLKCR3.bit.ECAP1 = 1;  
    CpuSysRegs.PCLKCR3.bit.ECAP2 = 1;
    CpuSysRegs.PCLKCR3.bit.ECAP3 = 1;
    CpuSysRegs.PCLKCR3.bit.ECAP4 = 1;
    CpuSysRegs.PCLKCR3.bit.ECAP5 = 1;
    CpuSysRegs.PCLKCR3.bit.ECAP6 = 1;
    EDIS;

    EALLOW;   
    PieVectTable.ECAP1_INT = &ecap1_isr;
    PieVectTable.ECAP2_INT = &ecap2_isr;
    PieVectTable.ECAP3_INT = &ecap3_isr;
    PieVectTable.ECAP4_INT = &ecap4_isr;
    PieVectTable.ECAP5_INT = &ecap5_isr;
    PieVectTable.ECAP6_INT = &ecap6_isr;

    EDIS;

    PieCtrlRegs.PIEIER4.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER4.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER4.bit.INTx3 = 1;
    PieCtrlRegs.PIEIER4.bit.INTx4 = 1;
    PieCtrlRegs.PIEIER4.bit.INTx5 = 1;
    PieCtrlRegs.PIEIER4.bit.INTx6 = 1;

    InitECapture1();
    InitECapture2();
    InitECapture3();
    InitECapture4();
    InitECapture5();
    InitECapture6();

    IER |= M_INT4;   

}

//  init PWM module.
void InitECapture1(void)
{
    ECap1Regs.ECEINT.all = 0x0000;    
    ECap1Regs.ECCLR.all = 0xFFFF;   
    ECap1Regs.ECCTL1.bit.CAPLDEN = 0;
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;

    ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;   // One-shot
    ECap1Regs.ECCTL2.bit.STOP_WRAP = 1;     // Stop at 4 events
    ECap1Regs.ECCTL1.bit.CAP1POL = 0;       // Falling edge
    ECap1Regs.ECCTL1.bit.CAP2POL = 1;       // Rising edge
    ECap1Regs.ECCTL1.bit.CTRRST1 = 0;       // Difference operation
    ECap1Regs.ECCTL1.bit.CTRRST2 = 0;       // Difference operation
    ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;      // Enable sync in
    ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;     // Pass through
    ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units


    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
    ECap1Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
    ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1-CAP4 register loads
    ECap1Regs.ECEINT.bit.CEVT2 = 1;         // 4 events = __interrupt

}


void InitECapture2(void)
{
    ECap2Regs.ECEINT.all = 0x0000;    
    ECap2Regs.ECCLR.all = 0xFFFF;  
    ECap2Regs.ECCTL1.bit.CAPLDEN = 0;
    ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;

    ECap2Regs.ECCTL2.bit.CONT_ONESHT = 1;   // One-shot
    ECap2Regs.ECCTL2.bit.STOP_WRAP = 1;     // Stop at 4 events
    ECap2Regs.ECCTL1.bit.CAP1POL = 0;       // Falling edge
    ECap2Regs.ECCTL1.bit.CAP2POL = 1;       // Rising edge
    ECap2Regs.ECCTL1.bit.CTRRST1 = 0;       // Difference operation
    ECap2Regs.ECCTL1.bit.CTRRST2 = 0;       // Difference operation
    ECap2Regs.ECCTL2.bit.SYNCI_EN = 1;      // Enable sync in
    ECap2Regs.ECCTL2.bit.SYNCO_SEL = 0;     // Pass through
    ECap2Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units


    ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
    ECap2Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
    ECap2Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1-CAP4 register loads
    ECap2Regs.ECEINT.bit.CEVT2 = 1;         // 4 events = __interrupt

}
void InitECapture3(void)
{
    ECap3Regs.ECEINT.all = 0x0000;   
    ECap3Regs.ECCLR.all = 0xFFFF;   
    ECap3Regs.ECCTL1.bit.CAPLDEN = 0;
    ECap3Regs.ECCTL2.bit.TSCTRSTOP = 0;

    ECap3Regs.ECCTL2.bit.CONT_ONESHT = 1;   // One-shot
    ECap3Regs.ECCTL2.bit.STOP_WRAP = 1;     // Stop at 4 events
    ECap3Regs.ECCTL1.bit.CAP1POL = 0;       // Falling edge
    ECap3Regs.ECCTL1.bit.CAP2POL = 1;       // Rising edge
    ECap3Regs.ECCTL1.bit.CTRRST1 = 0;       // Difference operation
    ECap3Regs.ECCTL1.bit.CTRRST2 = 0;       // Difference operation
    ECap3Regs.ECCTL2.bit.SYNCI_EN = 1;      // Enable sync in
    ECap3Regs.ECCTL2.bit.SYNCO_SEL = 0;     // Pass through
    ECap3Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units

    ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
    ECap3Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
    ECap3Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1-CAP4 register loads
    ECap3Regs.ECEINT.bit.CEVT2 = 1;         // 4 events = __interrupt

}

void InitECapture4(void)
{
    ECap4Regs.ECEINT.all = 0x0000;   
    ECap4Regs.ECCLR.all = 0xFFFF;    
    ECap4Regs.ECCTL1.bit.CAPLDEN = 0;
    ECap4Regs.ECCTL2.bit.TSCTRSTOP = 0;

    ECap4Regs.ECCTL2.bit.CONT_ONESHT = 1;   // One-shot
    ECap4Regs.ECCTL2.bit.STOP_WRAP = 1;     // Stop at 4 events
    ECap4Regs.ECCTL1.bit.CAP1POL = 0;       // Falling edge
    ECap4Regs.ECCTL1.bit.CAP2POL = 1;       // Rising edge
    ECap4Regs.ECCTL1.bit.CTRRST1 = 0;       // Difference operation
    ECap4Regs.ECCTL1.bit.CTRRST2 = 0;       // Difference operation
    ECap4Regs.ECCTL2.bit.SYNCI_EN = 1;      // Enable sync in
    ECap4Regs.ECCTL2.bit.SYNCO_SEL = 0;     // Pass through
    ECap4Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units


    ECap4Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
    ECap4Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
    ECap4Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1-CAP4 register loads
    ECap4Regs.ECEINT.bit.CEVT2 = 1;         // 4 events = __interrupt

}

void InitECapture5(void)
{
    ECap5Regs.ECEINT.all = 0x0000;   
    ECap5Regs.ECCLR.all = 0xFFFF;     
    ECap5Regs.ECCTL1.bit.CAPLDEN = 0;
    ECap5Regs.ECCTL2.bit.TSCTRSTOP = 0;

    ECap5Regs.ECCTL2.bit.CONT_ONESHT = 1;   // One-shot
    ECap5Regs.ECCTL2.bit.STOP_WRAP = 1;     // Stop at 4 events
    ECap5Regs.ECCTL1.bit.CAP1POL = 0;       // Falling edge
    ECap5Regs.ECCTL1.bit.CAP2POL = 1;       // Rising edge
    ECap5Regs.ECCTL1.bit.CTRRST1 = 0;       // Difference operation
    ECap5Regs.ECCTL1.bit.CTRRST2 = 0;       // Difference operation
    ECap5Regs.ECCTL2.bit.SYNCI_EN = 1;      // Enable sync in
    ECap5Regs.ECCTL2.bit.SYNCO_SEL = 0;     // Pass through
    ECap5Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units


    ECap5Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
    ECap5Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
    ECap5Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1-CAP4 register loads
    ECap5Regs.ECEINT.bit.CEVT2 = 1;         // 4 events = __interrupt

}

void InitECapture6(void)
{
    ECap6Regs.ECEINT.all = 0x0000;  
    ECap6Regs.ECCLR.all = 0xFFFF;     
    ECap6Regs.ECCTL1.bit.CAPLDEN = 0;
    ECap6Regs.ECCTL2.bit.TSCTRSTOP = 0;

    ECap6Regs.ECCTL2.bit.CONT_ONESHT = 1;   // One-shot
    ECap6Regs.ECCTL2.bit.STOP_WRAP = 1;     // Stop at 4 events
    ECap6Regs.ECCTL1.bit.CAP1POL = 0;       // Falling edge
    ECap6Regs.ECCTL1.bit.CAP2POL = 1;       // Rising edge
    ECap6Regs.ECCTL1.bit.CTRRST1 = 0;       // Difference operation
    ECap6Regs.ECCTL1.bit.CTRRST2 = 0;       // Difference operation
    ECap6Regs.ECCTL2.bit.SYNCI_EN = 1;      // Enable sync in
    ECap6Regs.ECCTL2.bit.SYNCO_SEL = 0;     // Pass through
    ECap6Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units

    ECap6Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
    ECap6Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
    ECap6Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1-CAP4 register loads
    ECap6Regs.ECEINT.bit.CEVT2 = 1;         // 4 events = __interrupt

}


__interrupt void ecap1_isr(void)
{
    //volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    //IER |= M_INT4;
    //IER    &= M_INT4;                         // Set "global" priority
    //PieCtrlRegs.PIEIER4.all &= MG4_1;   // Set "group"  priority
    //PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    //EINT;

    count1 = ECap1Regs.CAP1;
    count2 = ECap1Regs.CAP2;

    if(count1<count2)
        Chx.Ch1 = count2-count1;
    else
        Chx.Ch1 = count2-count1+0xffffffff;

    ECap1Regs.ECCLR.bit.CEVT2 = 1;    
    ECap1Regs.ECCLR.bit.INT = 1;
    ECap1Regs.ECCTL2.bit.REARM = 1;

    Lock_Control(&Command_Uint);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;  

    // Restore registers saved:
    //DINT;
    //PieCtrlRegs.PIEIER4.all = TempPIEIER;
}
__interrupt void ecap2_isr(void)
{
    //volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    //IER |= M_INT4;
    //IER    &= M_INT4;                         // Set "global" priority
    //PieCtrlRegs.PIEIER4.all &= MG4_2;   // Set "group"  priority
    //PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    //EINT;

    count1 = ECap2Regs.CAP1;
    count2 = ECap2Regs.CAP2;

    if(count1<count2)
        Chx.Ch2=count2-count1;
    else
        Chx.Ch2=count2-count1+0xffffffff;

    ECap2Regs.ECCLR.bit.CEVT2 = 1;   
    ECap2Regs.ECCLR.bit.INT = 1;
    ECap2Regs.ECCTL2.bit.REARM = 1;    

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;    

    //DINT;
    //PieCtrlRegs.PIEIER4.all = TempPIEIER;
}
__interrupt void ecap3_isr(void)
{
    //volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    //IER |= M_INT4;
    //IER    &= M_INT4;                         // Set "global" priority
    //PieCtrlRegs.PIEIER4.all &= MG4_3;   // Set "group"  priority
    //PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    //EINT;

    count1 = ECap3Regs.CAP1;
    count2 = ECap3Regs.CAP2;

    if(count1<count2)
        Chx.Ch3=count2-count1;
    else
        Chx.Ch3=count2-count1+0xffffffff;

    ECap3Regs.ECCLR.bit.CEVT2 = 1;    
    ECap3Regs.ECCLR.bit.INT = 1;
    ECap3Regs.ECCTL2.bit.REARM = 1;   

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;   

    //DINT;
    //PieCtrlRegs.PIEIER4.all = TempPIEIER;
}
__interrupt void ecap4_isr(void)
{
    //volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    //IER |= M_INT4;
    //IER    &= M_INT4;                         // Set "global" priority
    //PieCtrlRegs.PIEIER4.all &= MG4_4;   // Set "group"  priority
    //PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    //EINT;

    count1 = ECap4Regs.CAP1;
    count2 = ECap4Regs.CAP2;

    if(count1<count2)
        Chx.Ch4=count2-count1;
    else
        Chx.Ch4=count2-count1+0xffffffff;

    ECap4Regs.ECCLR.bit.CEVT2 = 1;    
    ECap4Regs.ECCLR.bit.INT = 1;
    ECap4Regs.ECCTL2.bit.REARM = 1;    

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;   
}
__interrupt void ecap5_isr(void)
{
    //volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    //IER |= M_INT4;
    //IER    &= M_INT4;                         // Set "global" priority
    //PieCtrlRegs.PIEIER4.all &= MG4_5;   // Set "group"  priority
    //PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    //EINT;

    count1 = ECap5Regs.CAP1;
    count2 = ECap5Regs.CAP2;

    if(count1<count2)
        Chx.Ch5=count2-count1;
    else
        Chx.Ch5=count2-count1+0xffffffff;

    //PID_Control(Chx.Ch5);

    ECap5Regs.ECCLR.bit.CEVT2 = 1;   
    ECap5Regs.ECCLR.bit.INT = 1;
    ECap5Regs.ECCTL2.bit.REARM = 1;    

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;   


    //DINT;
    //PieCtrlRegs.PIEIER4.all = TempPIEIER;

}
__interrupt void ecap6_isr(void)
{
    //volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    //IER |= M_INT4;
    //IER    &= M_INT4;                         // Set "global" priority
    //PieCtrlRegs.PIEIER4.all &= MG4_6;   // Set "group"  priority
    //PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts   
    //EINT;

    count1 = ECap6Regs.CAP1;
    count2 = ECap6Regs.CAP2;

    if(count1<count2)
        Chx.Ch6=count2-count1;
    else
        Chx.Ch6=count2-count1+0xffffffff;

    //PID_Status_Control(Chx.Ch6); 

    ECap6Regs.ECCLR.bit.CEVT2 = 1;    
    ECap6Regs.ECCLR.bit.INT = 1;
    ECap6Regs.ECCTL2.bit.REARM = 1;  

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;   

    //DINT;
    //PieCtrlRegs.PIEIER4.all = TempPIEIER;
}



