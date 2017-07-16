/*
 * ClientWhatDownApp.c
 *
 *  Created on: Jul 16, 2017
 *      Author: uv
 */

#include <stdio.h> /*TODO remove */
#include <stdlib.h>/*TODO remove */
#include "ClientWhatDownApp.h"
#include "tcp_client.h"
#include "logicFE.h"
#include "Client_ui.h"


/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define MAGIC_NUMBER_ALIVE_CLIENT_APP 0xfaceaaaa
/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct WhatDownClientApp
{
		uint m_magicNumber;

		TCP_C_t* m_server;
		Logic_FE_t* m_logicFE;
		Client_UI* m_UI;
} WhatDownClientApp_t ;

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

WhatDownClientApp_t* WhatDownClientApp_Create(const char* _serverIP, uint _serverPort)
{
	WhatDownClientApp_t* client;
	client = malloc(1 * sizeof(WhatDownClientApp_t) );
	if (!client)
	{
		return NULL;
	}

	client->m_server = TCP_CreateClient( (char*)_serverIP, _serverPort);
	if (! client->m_server)
	{
		free(client);
		return NULL;
	}

	client->m_logicFE = LogicFE_Create( client->m_server );
	if (!client->m_logicFE)
	{
		/* TODO fail */
		return NULL;
	}

	client->m_UI = UI_Create(client->m_logicFE);
	if (!client->m_UI)
	{
		/* TODO fail */
		return NULL;
	}



	client->m_magicNumber = MAGIC_NUMBER_ALIVE_CLIENT_APP;

	return client;
}

void WhatDownClientApp_Destroy(WhatDownClientApp_t* _appBE)
{

}

bool WhatDownClientApp_Run(WhatDownClientApp_t* _appBE)
{
	/* TODO check param */

	Ui_Run(_appBE->m_UI);

	return TRUE;
}

bool WhatDownClientApp_Stop(WhatDownClientApp_t* _appBE)
{

}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

