/*
 * logic_FE.c
 *
 *  Created on: Jul 16, 2017
 *      Author: uv
 */

#include <stdio.h>
#include <stdlib.h>
#include "logicFE.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define MAGIC_NUMBER_ALIVE_LOGIC_FE 0xfacecdcd
/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct Logic_FE
{
	uint m_magicNumer;

	TCP_C_t* m_netClient;
	void* m_ui;

};
/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Logic_FE_t* LogicFE_Create(TCP_C_t* _netClient)
{
	Logic_FE_t* logicFE;
	if (NULL == _netClient)
	{
		return NULL;
	}

	logicFE = calloc(1, sizeof(Logic_FE_t) );
	if (!logicFE)
	{
		return NULL;
	}

	logicFE->m_netClient = _netClient;
//	logicFE->m_ui = _ui;
	logicFE->m_magicNumer = MAGIC_NUMBER_ALIVE_LOGIC_FE;

	return logicFE;
}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

