/*
 * whatDownBackEndApp.c
 *
 *  Created on: Jul 15, 2017
 *      Author: yuval
 */

#include "whatDownBackEndApp.h"
#include "logic_backEnd.h"
#include "usersHandle.h"
#include "ipHandle.h"
#include "groupsHandle.h"


/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define MAGIC_NUMBER_ALIVE_BE_APP 0xfadefade

typedef int bool;

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct WhatDownBackEndApp
{
	uint m_magicNumber;

	UsersHandle_t* m_usersHandlePtr;
	IP_Handle_t* m_ipHndlPtr;
	GroupHandel_t* m_groupsHndlPtr;
	Logic_BE_t* m_BElogicPtr;
	TCP_S_t* m_TCPnet;

};

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */
static bool IsStructValid(WhatDownBackEndApp_t* _appBE);

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

	app->m_ipHndlPtr = IP_Handle_Create(CHAT_FIRSET_IP, CHAT_MAX_NUM_IP, CHAT_PORT);
	if (! app->m_ipHndlPtr)
	{
		UsersHandle_Destroy(app->m_usersHandlePtr);
		free(app);
		return NULL;
	}

	app->m_groupsHndlPtr = GroupsHandel_Create();
	if (!app->m_groupsHndlPtr)
	{
		IP_Handle_Destory(app->m_ipHndlPtr);
		UsersHandle_Destroy(app->m_usersHandlePtr);
		free(app);
		return NULL;
	}

	app->m_BElogicPtr = LogicBE_Create(app->m_usersHandlePtr, app->m_groupsHndlPtr, app->m_ipHndlPtr);
	if (! app->m_BElogicPtr )
	{
		GroupsHandel_Destroy(app->m_groupsHndlPtr);
		IP_Handle_Destory(app->m_ipHndlPtr);
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
		GroupsHandel_Destroy(app->m_groupsHndlPtr);
		IP_Handle_Destory(app->m_ipHndlPtr);
		UsersHandle_Destroy(app->m_usersHandlePtr);
		free(app);
		return NULL;
	}

	LogicBE_SetServerPTR(app->m_BElogicPtr, app->m_TCPnet);

	app->m_magicNumber = MAGIC_NUMBER_ALIVE_BE_APP;

	return app;
}

void WhatDownBackEndApp_Destroy(WhatDownBackEndApp_t* _appBE)
{
	if (! IsStructValid(_appBE))
	{
		return;
	}

	_appBE->m_magicNumber = 0;

	LogicBE_Destroy(_appBE->m_BElogicPtr);
	GroupsHandel_Destroy(_appBE->m_groupsHndlPtr);
	/* TODO make sure group didn't leave any address un-free-ed */
	IP_Handle_Destory(_appBE->m_ipHndlPtr);
	UsersHandle_Destroy(_appBE->m_usersHandlePtr);
	TCP_DestroyServer(_appBE->m_TCPnet);
	free(_appBE);

	return;
}

bool WhatDownBackEndApp_Run(WhatDownBackEndApp_t* _appBE)
{
	if (! IsStructValid(_appBE))
	{
		return FALSE;
	}

	return TCP_RunServer(_appBE->m_TCPnet);
}

bool WhatDownBackEndApp_Stop(WhatDownBackEndApp_t* _appBE)
{
	if (! IsStructValid(_appBE))
	{
		return FALSE;
	}

	return TCP_StopServer(_appBE->m_TCPnet);
}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool IsStructValid(WhatDownBackEndApp_t* _appBE)
{
	return !(NULL == _appBE || _appBE->m_magicNumber != MAGIC_NUMBER_ALIVE_BE_APP);
}




