/*
 * sci.c
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 *
 */

#include "sci.h"
#include "PCData.h"
#include "F28x_Project.h"

extern unsigned char Test_State;
extern Uint16 RecivePCData[16];
extern Uint16 ReciveMvData[16];
unsigned char PCData[32];

void U16ToU8(Uint16 *input,unsigned char *output,unsigned char length)
{
    int i;
    for(i = 0;i<length;i++)
        output[i] = input[i]&0x00ff;   
        output[i + 1] =(input[i]>>8)&0x00ff;  
}

void Sci_Init()
{
    Scib_Init();
    Scic_Init();
}

// using by bluetooth
void Scib_Init()   

{
    /*
    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2);
    GPIO_SetupPinOptions(19, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2);
    GPIO_SetupPinOptions(18, GPIO_OUTPUT, GPIO_ASYNC);

    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;    // Enable pull-up for GPIO19 (SCIRXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;    // Disable pull-up for GPIO18 (SCITXDB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO19 for SCIRXDB operation
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO18 for SCITXDB operation
    EDIS;

    //EALLOW;  // This is needed to write to EALLOW protected registers
    //PieVectTable.SCIB_RX_INT = &scibRxFifoIsr;
    //EDIS;    // This is needed to disable write to EALLOW protected registers

    ScibRegs.SCICCR.all = 0x0007;      // 1 stop bit,  No loopback
    // No parity,8 char bits,
    // async mode, idle-line protocol
    ScibRegs.SCICTL1.all = 0x0003;     // enable TX, RX, internal SCICLK,
    // Disable RX ERR, SLEEP, TXWAKE
    ScibRegs.SCICTL2.bit.TXINTENA = 1;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
    ScibRegs.SCIHBAUD.all = 0x0000;    //115200 baund @ LSPCLK = 50Mhz
    ScibRegs.SCILBAUD.all = 0x0036;
    ScibRegs.SCICCR.bit.LOOPBKENA = 0; // Enable loop back
    ScibRegs.SCIFFTX.all = 0xC040;
    ScibRegs.SCIFFRX.all = 0x0030;
    ScibRegs.SCIFFCT.all = 0x00;

    ScibRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
    ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;
    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;

    IER |= M_INT9;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, INT3
    EINT;
    ERTM;  // Enable Global realtime interrupt DBGM
    */
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;    // Enable pull-up for GPIO19 (SCIRXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;    // Disable pull-up for GPIO18 (SCITXDB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO19 for SCIRXDB operation
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO18 for SCITXDB operation
    EDIS;

    ScibRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
    // No parity,8 char bits,
    // async mode, idle-line protocol
    ScibRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
    // Disable RX ERR, SLEEP, TXWAKE
    //ScibRegs.SCICTL2.all = 0x0003;
    ScibRegs.SCICTL2.bit.TXINTENA = 1;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;

    //
    // SCIA at 115200 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x00 and LBAUD = 0x36.
    //
    ScibRegs.SCIHBAUD.all = 0x0000;
    ScibRegs.SCILBAUD.all = 0x0036;

    //FIFO
    ScibRegs.SCIFFTX.bit.SCIFFENA=1;
    ScibRegs.SCIFFTX.bit.SCIRST=1; 
    ScibRegs.SCIFFRX.bit.RXFFIL=1;
    ScibRegs.SCIFFRX.bit.RXFFIENA=1;

    ScibRegs.SCIFFCT.all = 0x00;

    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
    ScibRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset

    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.SCIB_RX_INT = &scibRxFifoIsr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    IER |= M_INT9;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, INT3
    EINT;
    ERTM;  // Enable Global realtime interrupt DBGM

}



//  using by Openmv camera data.

void Scic_Init()
{

    GPIO_SetupPinMux(139, GPIO_MUX_CPU1, 6);
    GPIO_SetupPinOptions(139, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(56, GPIO_MUX_CPU1, 6);
    GPIO_SetupPinOptions(56, GPIO_OUTPUT, GPIO_ASYNC);

    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.SCIC_RX_INT = &scicRxFifoIsr;  
    EDIS;    // This is needed to disable write to EALLOW protected registers

    ScicRegs.SCICCR.all = 0x0007;      // 1 stop bit,  No loopback
                                       // No parity,8 char bits,
                                       // async mode, idle-line protocol
    ScicRegs.SCICTL1.all = 0x0003;     // enable TX, RX, internal SCICLK,
                                       // Disable RX ERR, SLEEP, TXWAKE
    ScicRegs.SCICTL2.bit.TXINTENA = 1;
    ScicRegs.SCICTL2.bit.RXBKINTENA = 1;
    ScicRegs.SCIHBAUD.all = 0x0000;    //115200 baund @ LSPCLK = 50Mhz
    ScicRegs.SCILBAUD.all = 0x0035;
    ScicRegs.SCICCR.bit.LOOPBKENA = 0; // Enable loop back
    ScicRegs.SCIFFTX.all = 0xC040;
    ScicRegs.SCIFFRX.all = 0x0030;
    ScicRegs.SCIFFCT.all = 0x00;

    ScicRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
    ScicRegs.SCIFFTX.bit.TXFIFORESET = 1;
    ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;

    IER |= M_INT8;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER8.bit.INTx5 = 1;   // PIE Group 8, INT5
    EINT;
    ERTM;  // Enable Global realtime interrupt DBGM
}

void scic_msg(unsigned char * msg)
{
    int i;
    while (ScicRegs.SCIFFTX.bit.TXFFST != 0) {}
    for (i = 0;i < 16;i ++){
        ScicRegs.SCITXBUF.all = msg[i];
    }
}

void scib_msg(unsigned char * msg)    // send to PC.
{
    int i;
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0) {}
    for (i = 0;i < 16;i ++){
        ScibRegs.SCITXBUF.all = msg[i];
    }
}

/*******************   second method to send   *****************/
void Uart_Put_Buf(unsigned char *data_to_send,unsigned char _cnt)
{
    unsigned char i=0;
    for(;i<_cnt;i++)
        UARTCharPut(data_to_send[i]);
}

void UARTCharPut(unsigned char ch)
{
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0);
    ScibRegs.SCITXBUF.all=ch;
}



__interrupt void scicRxFifoIsr(void)  
{
    Uint16 i;
    for(i=0;i<16;i++)
    {
        ReciveMvData[i]=ScicRegs.SCIRXBUF.all;  // Read data
    }

    ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack 

}

__interrupt void scibRxFifoIsr(void)   
{
    //Uint16 i;
    unsigned char Temp = 0;
    //for(i=0;i<16;i++)
    //{
    Temp = ScibRegs.SCIRXBUF.all;  // Read data
    //}



    //U16ToU8(RecivePCData,PCData,16);  

    ANO_DT_Data_Receive_Prepare(Temp);
    PCData_Control(Temp);


    ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack

}








