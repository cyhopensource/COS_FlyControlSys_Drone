/*
 * send.h
 *
 *  Created on: 03/04/2019
 *      Author: cyh
 */

#ifndef COMMUNICATION_SEND_H_
#define COMMUNICATION_SEND_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"

void sendRTInfo(void);
void sendParaInfo(void);
void sendGyroData(void);
void sendAccData(void);
void sendMagData(void);
void sendPositionData(void);
void sendUserData(void);
void sendRTOffset(void);



#endif /* COMMUNICATION_SEND_H_ */
