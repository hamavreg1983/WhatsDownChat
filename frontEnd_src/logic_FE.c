/*
 * logic_FE.c
 *
 *  Created on: Jul 16, 2017
 *      Author: uv
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* inet_ntoa */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

	char m_userName[MAX_USERNAME];
	/* list of group name */

	ClientReceiveMessage_t* m_recivebuf;
};

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */

static int LogicFE_Send(Logic_FE_t* _logic, void* _msg,  uint _msgLength);

static int LogicFE_Recive( TCP_C_t* _netClient , ClientReceiveMessage_t* _recivebuf);

static bool IsStructValid(Logic_FE_t* _logic);

static bool OpenChatWindows(sockaddr_in_t* _sockaddr_t, const char* _name, const char* _groupName);

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

	strcpy( logicFE->m_userName , "UnknownName" );

	return logicFE;
}

int LogicFE_Signup(Logic_FE_t* _logic, const char* _username, const char* _password)
{
	int status;

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
	if (length <= 0)
	{
		return -1;
	}

	result = LogicFE_Send(_logic, buffer, length);
	if (result <= 0)
	{
		return -1;
	}

	status = LogicFE_Recive( _logic->m_netClient , _logic->m_recivebuf);
	if (status == BackEnd_SUCCESS)
	{
		strcpy( _logic->m_userName , _username);
	}
	return status;
}

int LogicFE_CreateGroup(Logic_FE_t* _logic, const char* _groupName)
{

	if (NULL == _groupName)
	{
		return -1;
	}

	if (! IsStructValid(_logic))
	{
		return -1;
	}

	/* check values */

	char buffer[MAX_MESSAGE_LENGTH];
	uint length;
	int result;

	length = Protocol_EncodeNewGroup(_groupName, buffer);
	if (length <= 0)
	{
		return -1;
	}

	result = LogicFE_Send(_logic, buffer, length);
	if (result <= 0)
	{
		return -1;
	}

	int status;
	status = LogicFE_Recive( _logic->m_netClient , _logic->m_recivebuf);

	if (status == BackEnd_SUCCESS)
	{
		/* TODO add group to group list */

		OpenChatWindows(&_logic->m_recivebuf->m_groupAdrres, _logic->m_userName, _groupName);
	}

	return status;
}

int LogicFE_JoinGroup(Logic_FE_t* _logic, const char* _groupName)
{
	if (NULL == _groupName)
	{
		return -1;
	}

	if (! IsStructValid(_logic))
	{
		return -1;
	}

	/* check values */

	char buffer[MAX_MESSAGE_LENGTH];
	uint length;
	int result;


	length = Protocol_EncodeJoinGroup(_groupName, buffer);
	if (length <= 0)
	{
		return -1;
	}

	result = LogicFE_Send(_logic, buffer, length);
	if (result <= 0)
	{
		return -1;
	}

	int status;
	status = LogicFE_Recive( _logic->m_netClient , _logic->m_recivebuf);

	if (status == BackEnd_SUCCESS)
	{
		/* TODO add group to group list */

		OpenChatWindows(&_logic->m_recivebuf->m_groupAdrres, _logic->m_userName, _groupName);
	}

	return status;

}

int LogicFE_GetAllGroupsName(Logic_FE_t* _logic, char* _groupsName_out, uint* _numOfGroups_out, uint _bufferSize)
{
	if (NULL == _groupsName_out || NULL == _numOfGroups_out)
	{
		return -1;
	}

	if (! IsStructValid(_logic))
	{
		return -1;
	}

	/* check values */

	char buffer[MAX_MESSAGE_LENGTH];
	uint length;
	int result;


	length = Protocol_EncodeGetAllGroups(buffer);
	if (length <= 0)
	{
		return -1;
	}

	result = LogicFE_Send(_logic, buffer, length);
	if (result <= 0)
	{
		return -1;
	}

	int status;
	status = LogicFE_Recive( _logic->m_netClient , _logic->m_recivebuf);

	if (status == BackEnd_SUCCESS)
	{
		/* TODO should remove group user is member of? */

		*_numOfGroups_out = _logic->m_recivebuf->m_numberOfGroups;

		memcpy(_groupsName_out , _logic->m_recivebuf->m_GroupName, _bufferSize);
	}

	return status;

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

#ifndef NDBUG
	printf("recived(%d): %.*s .\n", recv_bytes, recv_bytes, (char*) buffer);
#endif

	Protocol_DecodeClient(buffer, recv_bytes, _recivebuf);

#ifndef NDBUG
	printf("Msg Type:%d. status:%d\n", _recivebuf->m_messageType , _recivebuf->m_status);
#endif



	return _recivebuf->m_status;
}

static bool IsStructValid(Logic_FE_t* _logic)
{
	return ! (NULL == _logic || _logic->m_magicNumer != MAGIC_NUMBER_ALIVE_LOGIC_FE);
}

static bool OpenChatWindows(sockaddr_in_t* _sockaddr_t, const char* _name, const char* _groupName)
{
	uint port;

	char writerCommand[MAX_MESSAGE_LENGTH];
	char readerCommand[MAX_MESSAGE_LENGTH];

	if (NULL == _sockaddr_t || NULL == _name)
	{
		return FALSE;
	}

	/* TODO remove hardcocded */
#define WINDOW_HIGHT_WRITER 10
#define WINDOW_HIGHT_READER 30
#define WINDOW_WIDTH 100
#define WINDOW_X_POS 100
#define WINDOW_Y_POS_WRITER 600
#define WINDOW_Y_POS_READER 0

	port = ntohs(_sockaddr_t->sin_port );
	char* ip = inet_ntoa(_sockaddr_t->sin_addr) ;

	/* setup setting for new windows */
	sprintf(writerCommand, "gnome-terminal --geometry=100x10+100+600 --command=\"../chats/writer %s %d %s %s%c", ip, port, _name, _groupName, '\"');
	sprintf(readerCommand, "gnome-terminal --geometry=100x30+100+0   --command=\"../chats/reader %s %d %s%c", ip, port, _groupName, '\"');

	system(writerCommand);
	system(readerCommand);

#ifndef DNDBUG
	printf("Group Create (%s %d) and windows chats were opened. Enjoy\n", ip, port);
#endif

	return TRUE;
}

