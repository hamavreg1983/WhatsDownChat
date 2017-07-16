/*
 * ipHandle.h
 *
 *  Created on: Jul 16, 2017
 *      Author: yuval
 */

#ifndef IPHANDLE_H_
#define IPHANDLE_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct sockaddr_in sockaddr_in_t;

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct IP_Handle IP_Handle_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

IP_Handle_t* IP_Handle_Create(const char* _firestIP, uint _maxNumOfIPs, uint _portNum);

void IP_Handle_Destory(IP_Handle_t* _ipHndl);

sockaddr_in_t* IP_Handle_GetFreeIP(IP_Handle_t* _ipHndl);

bool IP_Handle_Release(IP_Handle_t* _ipHndl, sockaddr_in_t* _addressToRelease);


#endif /* IPHANDLE_H_ */
