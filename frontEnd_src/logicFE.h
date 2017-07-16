/*
 * logicFE.h
 *
 *  Created on: Jul 16, 2017
 *      Author: uv
 */

#ifndef LOGICFE_H_
#define LOGICFE_H_

//#include "defines.h"
#include "tcp_client.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct Logic_FE Logic_FE_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Logic_FE_t* LogicFE_Create(TCP_C_t* netClient);

void LogicFE_Destroy(Logic_FE_t* _logic);

int LogicFE_ReciveDataFunc(void* _data, size_t _sizeData, uint _socketNum, void* _contex);


#endif /* LOGICFE_H_ */