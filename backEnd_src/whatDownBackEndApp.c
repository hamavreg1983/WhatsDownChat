/*
 * whatDownBackEndApp.c
 *
 *  Created on: Jul 15, 2017
 *      Author: yuval
 */

#include "whatDownBackEndApp.h"
#include "logic_backEnd.h"
#include "usersHandle.h"
/* groupsHandle */
/* iphandle*/


/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define MAGIC_NUMBER_ALIVE_BE_APP 0xfadefade

typedef int bool;

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct WhatDownBackEndApp
{
	uint m_magicNumber;

	UsersHandle_t* m_usersHandlePtr;
	/* groupsHandle */
	/* iphandle*/
	Logic_BE_t* m_BElogicPtr;
	TCP_S_t* m_TCPnet;


};

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

WhatDownBackEndApp_t* WhatDownBackEndApp_Create()
{
	WhatDownBackEndApp_t* app;
	app = calloc(1, sizeof(WhatDownBackEndApp_t));
	if (!app)
	{
		return NULL;
	}

	app->m_usersHandlePtr = UsersHandle_Create();
	if (! app->m_usersHandlePtr)
	{
		free(app);
		return NULL;
	}

	app->m_BElogicPtr = LogicBE_Create(app->m_usersHandlePtr, NULL, NULL); /* TODO fill other DB */
	if (! app->m_BElogicPtr )
	{
		UsersHandle_Destroy(app->m_usersHandlePtr);
		free(app);
		return NULL;
	}

	app->m_TCPnet = TCP_CreateServer(SERVER_PORT, SERVER_IP, SERVER_MAX_CONNECTION, SERVER_TIMOUT_MS,
			LogicBE_ReciveDataFunc,
			LogicBE_NewClientFunc,
			LogicBE_ClientDissconnectedFunc,
			LogicBE_ErrorFunc,
			app->m_BElogicPtr	);

	if (!app)
	{
		LogicBE_Destroy(app->m_BElogicPtr);
		UsersHandle_Destroy(app->m_usersHandlePtr);
		free(app);
		return NULL;
	}

	LogicBE_SetServerPTR(app->m_BElogicPtr, app->m_TCPnet);

	app->m_magicNumber = MAGIC_NUMBER_ALIVE_BE_APP;

	return app;
}

// TODO void WhatDownBackEndApp_Destroy(WhatDownBackEndApp_t* _appBE);

bool WhatDownBackEndApp_Run(WhatDownBackEndApp_t* _appBE)
{
	/* TODO check input */

	return TCP_RunServer(_appBE->m_TCPnet);

}

// TODO bool WhatDownBackEndApp_Stop(WhatDownBackEndApp_t* _appBE);

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

