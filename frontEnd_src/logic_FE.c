/*
 * logic_FE.c
 *
 *  Created on: Jul 16, 2017
 *      Author: uv
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logicFE.h"
#include "Protocol.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define MAGIC_NUMBER_ALIVE_LOGIC_FE 0xfacecdcd
/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct Logic_FE
{
	uint m_magicNumer;

	TCP_C_t* m_netClient;
//	void* m_ui;

	ClientReceiveMessage_t* m_recivebuf;
};
/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */

static int LogicFE_Send(Logic_FE_t* _logic, void* _msg,  uint _msgLength);

static int LogicFE_Recive( TCP_C_t* _netClient , ClientReceiveMessage_t* _recivebuf);

static bool IsStructValid(Logic_FE_t* _logic);

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

	logicFE->m_recivebuf = calloc(1, sizeof(ClientReceiveMessage_t));
	if (! logicFE->m_recivebuf )
	{
		free(logicFE);
		return NULL;
	}

	logicFE->m_netClient = _netClient;
//	logicFE->m_ui = _ui;
	logicFE->m_magicNumer = MAGIC_NUMBER_ALIVE_LOGIC_FE;

	return logicFE;
}

int LogicFE_Signup(Logic_FE_t* _logic, const char* _username, const char* _password)
{
	/* TODO check input param */
	if (! IsStructValid(_logic))
	{
		return -1;
	}

	/* check values */

	char buffer[MAX_MESSAGE_LENGTH];
	uint length;
	int result;

	length = Protocol_EncodeSignUp(_username, _password, buffer);
	/* TODO check return */

	result = LogicFE_Send(_logic, buffer, length);
	/* TODO check return */

	return LogicFE_Recive( _logic->m_netClient , _logic->m_recivebuf);
	/* TODO check return */

}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int LogicFE_Send(Logic_FE_t* _logic, void* _msg,  uint _msgLength)
{
	/*TODO check input ? */

	/* send response */
	int sentBytes;
	sentBytes = TCP_ClientSend(_logic->m_netClient, _msg, _msgLength);
	if (0 >= sentBytes)
	{
		perror("Error sending msg from client");
		return sentBytes;
	}


	return sentBytes;
}

static int LogicFE_Recive( TCP_C_t* _netClient , ClientReceiveMessage_t* _recivebuf)
{
	char buffer[MAX_MESSAGE_LENGTH];
	int recv_bytes;

	/* empty struct to prevent old data */
	memset(_recivebuf , 0 , sizeof(ClientReceiveMessage_t) );


	recv_bytes = TCP_ClientRecive(_netClient, buffer, MAX_MESSAGE_LENGTH);
	if (0 == recv_bytes)
	{
		printf("\n server closed connection. exiting.");
		return BackEnd_SYSTEM_FAIL;
	}
	printf("recived(%d): %s.\n", recv_bytes, (char*) buffer);

	Protocol_DecodeClient(buffer, recv_bytes, _recivebuf);

	printf("Msg Type:%d. status:%d\n", _recivebuf->m_messageType , _recivebuf->m_status);

	return _recivebuf->m_status;
}

static bool IsStructValid(Logic_FE_t* _logic)
{
	return ! (NULL == _logic || _logic->m_magicNumer != MAGIC_NUMBER_ALIVE_LOGIC_FE);
}



