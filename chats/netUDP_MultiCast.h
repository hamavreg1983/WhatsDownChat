/*
 * netUDP_MultiCast.h
 *
 *  Created on: Jul 18, 2017
 *      Author: uv
 */

#ifndef NETUDP_MULTICAST_H_
#define NETUDP_MULTICAST_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define MSG_MAX_SIZE 1024

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct UDP_MultiCast UDP_MultiCast_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

UDP_MultiCast_t* UDP_MultiCast_Sender_Create(const char* _ip, uint _port);

void UDP_MultiCast_Sender_Destroy(UDP_MultiCast_t* _net);

int UDP_MultiCast_Send(UDP_MultiCast_t* _net, void* _msg, uint _msgLength);





UDP_MultiCast_t* UDP_MultiCast_Reciver_Create(const char* _ip, uint _port);

void UDP_MultiCast_Reciver_Destroy(UDP_MultiCast_t* _net);

int UDP_MultiCast_Recive(UDP_MultiCast_t* _netRecive, void* _buffer, size_t _bufferSize);






#endif /* NETUDP_MULTICAST_H_ */
