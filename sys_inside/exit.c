/*
 * exit.c
 *
 *  Created on: 31/03/2019
 *      Author: cyh
 *
 *
 */

#include "F28x_Project.h"
#include "exit.h"
#include "sensor/mpu9250.h"




unsigned char MPU_sta = 0;



void EXTI_Pinconfig(void)
{
    // GPIO0 and GPIO1 are inputs
    EALLOW;
    GpioCtrlRegs.GPDMUX2.bit.GPIO124 = 0;         // GPIO
    GpioCtrlRegs.GPDDIR.bit.GPIO124 = 0;          // input
    GpioCtrlRegs.GPDQSEL2.bit.GPIO124 = 0;        // XINT1 Synch to SYSCLKOUT only
    EDIS;

    GPIO_SetupXINT1Gpio(124); 
}

void Exit_Init(void)
{
    EALLOW;
    PieVectTable.XINT1_INT = &xint1_isr;
    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Group 1 INT4
    IER |= M_INT1;                              // Enable CPU INT1

    EXTI_Pinconfig();

    // Configure XINT1
    XintRegs.XINT1CR.bit.POLARITY = 0;          // Falling edge interrupt

    // Enable XINT1 and XINT2
    XintRegs.XINT1CR.bit.ENABLE = 1;            // Enable XINT1
}

interrupt void xint1_isr(void)   // Interrupt priority configuration
{


    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;

    IER |= M_INT1;
    IER &= M_INT1;                         // Set "global" priority

    //PieCtrlRegs.PIEIER1.all &= MG1_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    EINT;
/*
    if(MPU_sta == 0)
    {
        temp2 = MPU6000_Read(MPU6000_Value2);
        MPU_sta = 1;    
    }

*/
    // Acknowledge this interrupt to get more from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;


    // Restore registers saved
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

//    GpioDataRegs.GPBCLEAR.bit.GPIO40=1;
}

