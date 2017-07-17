/*
 * logic_backEnd.h
 *
 *  Created on: Jul 15, 2017
 *      Author: yuval
 */

#ifndef LOGIC_BACKEND_H_
#define LOGIC_BACKEND_H_


#include "defines.h"
#include "tcp.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct Logic_BE Logic_BE_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Logic_BE_t* LogicBE_Create(void* _usersHandel, void* _groupHandle, void* _IP_handle);

int LogicBE_SetServerPTR(Logic_BE_t* _logicBE, TCP_S_t* _server);

void LogicBE_Destroy(Logic_BE_t* _logic);

/* call back functions */
int LogicBE_ReciveDataFunc(void* _data, size_t _sizeData, uint _socketNum, void* _contex);
int LogicBE_NewClientFunc(uint _socketNum, void* _contex);
int LogicBE_ClientDissconnectedFunc(uint _socketNum, void* _contex);
int LogicBE_ErrorFunc(TCP_SERVER_USER_ERROR _status, uint _socketNum, void* _contex);






#endif /* LOGIC_BACKEND_H_ */
