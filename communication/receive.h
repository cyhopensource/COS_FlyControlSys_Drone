/*
 * receive.h
 *
 *  Created on: 03/04/2019
 *      Author: cyh
 */

#ifndef COMMUNICATION_RECEIVE_H_
#define COMMUNICATION_RECEIVE_H_

#include "F28x_Project.h"
#include "symbol&globe/globe.h"

void ReceiveData_Norm(Remote_Command *Command,Chx_Width *p);
void ReceiveData_Convert(Remote_Command *Command_Uint,Remote_Command *Command);
void Remote_CommandGet(Remote_Command *Command);

#endif /* COMMUNICATION_RECEIVE_H_ */
