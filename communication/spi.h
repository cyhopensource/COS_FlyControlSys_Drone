/*
 * spi.h
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 */

#ifndef COMMUNICATION_SPI_H_
#define COMMUNICATION_SPI_H_

#include "F28x_Project.h"

void Init_spi_gpio();
void Init_Spi(void);
void spi_fifo_init();
unsigned char SPI_ReadWrite_Byte(unsigned char byte);
void Spi_send(Uint16 a);

#endif /* COMMUNICATION_SPI_H_ */
