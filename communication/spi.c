/*
 * spi.c
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 */

#include "communication/spi.h"
#include "F28x_Project.h"

#define SPI_BRR        ((200E6 / 4) / 500E3) - 1

void spi_xmit(Uint16 a)
{
    SpiaRegs.SPITXBUF = a;
}

void Init_spi_gpio()
{
    EALLOW;

    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;  // Enable pull-up on GPIO58 (SPISIMOA)
    GpioCtrlRegs.GPBPUD.bit.GPIO59 = 0;  // Enable pull-up on GPIO59 (SPISOMIA)
    GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0;  // Enable pull-up on GPIO60 (SPICLKA)

    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO59 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO60 = 3; // Asynch input GPIO18 (SPICLKA)

    GpioCtrlRegs.GPBGMUX2.bit.GPIO58 = 3;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO59 = 3;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO60 = 3;

    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 3; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 3; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 3; // Configure GPIO18 as SPICLKA

    //mpu9250 spi
    GPIO_SetupPinMux(125, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(125, GPIO_OUTPUT, GPIO_PUSHPULL);
    //lsm303
    GPIO_SetupPinMux(124, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(124, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_WritePin(125, 1);
    GPIO_WritePin(124, 1);
    EDIS;
}

void Init_Spi(void) 
{

    SpiaRegs.SPICCR.bit.SPISWRESET = 0;
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;
    SpiaRegs.SPICCR.bit.SPICHAR = (8-1);
    SpiaRegs.SPICCR.bit.SPILBK = 0 ;
    SpiaRegs.SPICCR.bit.HS_MODE = 0 ;

    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
    SpiaRegs.SPICTL.bit.TALK = 1;
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
    SpiaRegs.SPICTL.bit.SPIINTENA = 0;

    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = 49;   // 1M baudrate

    SpiaRegs.SPIPRI.bit.FREE = 1;

    SpiaRegs.SPICCR.bit.SPISWRESET = 1;

    Init_spi_gpio();
}

void spi_fifo_init()
{
    SpiaRegs.SPIFFTX.all = 0xE040;
    SpiaRegs.SPIFFRX.all = 0x2044;
    SpiaRegs.SPIFFCT.all = 0x0;

    Init_Spi();
}
/*
unsigned char SPI_ReadWrite_Byte(unsigned char byte)   //
{
    spi_xmit(((Uint16)byte)<<8);
    while(SpiaRegs.SPIFFRX.bit.RXFFST !=1);    
    return SpiaRegs.SPIRXBUF;
}

void Spi_send(Uint16 a)   
{
    SpiaRegs.SPITXBUF = a;
}
*/
/*
unsigned char SPI_ReadWrite_Byte(unsigned char data)
{
    unsigned char retry=0;
    while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1)
    {
        retry++;
        if(retry>200)return 0;
    }
    SpiaRegs.SPITXBUF=(data|0x8000)<<8;
    retry=0;
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1)
    {
        retry++;
        if(retry>200)return 0;
    }
    return ((SpiaRegs.SPIRXBUF)&0x00ff);
}
*/

unsigned char SPI_ReadWrite_Byte(unsigned char data)
{

    spi_xmit(((Uint16)data)<<8);
    while(SpiaRegs.SPIFFRX.bit.RXFFST !=1) { }
    return SpiaRegs.SPIRXBUF;
}

