/**
 *  @file ipHandle.h
 *
 *  @date Jul 16, 2017
 *  @author Yuval Hamberg
 *
 *  @brief A handle of communication address. IP and port, holds a struct sockaddr_in of unused ones. FIFO implamentaion.
 *
 *  @TODO add comments to API
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

/**
 * @brief asks for an address to use. no one also would use it until the caller returns it.
 * @param _ipHndl the pointer to the struct
 * @return pointer to the address struct used in network module. NULL if errors.
 */
sockaddr_in_t* IP_Handle_GetFreeIP(IP_Handle_t* _ipHndl);

bool IP_Handle_Release(IP_Handle_t* _ipHndl, sockaddr_in_t* _addressToRelease);


#endif /* IPHANDLE_H_ */
