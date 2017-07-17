/*
 * logic_backEnd.c
 *
 *  Created on: Jul 15, 2017
 *      Author: yuval
 */

#include <string.h> /* memset */
#include <err.h>
#include "logic_backEnd.h"
#include "Protocol.h"
#include "usersHandle.h"
#include "ipHandle.h"
#include "groupsHandle.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define MAGIC_NUMBER_BE_LOGIC 0xfacebaad

#define MINIMAL_USER_PASSWORD 3

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct Logic_BE
{
	uint m_magicNumber;

	TCP_S_t* m_net;
	void* m_usersHandel;
	void* m_groupHandle;
	IP_Handle_t* m_IP_handle;

	ServerReceiveMessage_t* m_decodedMsg;
};

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */

static int LogicBE_Send(Logic_BE_t* _logic, uint _socketNum, MessageType _msgType, BackEndStatus _responseResult, void* _msg,  uint _msgLength);

static bool SignUp(Logic_BE_t* _logicBE, ServerReceiveMessage_t* m_decodedMsg, uint _socketNum);
static bool CreateGroup(Logic_BE_t* _logicBE, ServerReceiveMessage_t* _decodedMsg, uint _socketNum);
static bool JoinGroup(Logic_BE_t* _logicBE, ServerReceiveMessage_t* _decodedMsg, uint _socketNum);

static bool IsStructValid(Logic_BE_t* _logicBE);
static bool FlushServerReceiveMessage_t(ServerReceiveMessage_t* _decodedMsg);

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Logic_BE_t* LogicBE_Create(void* _usersHandel, void* _groupHandle, void* _IP_handle)
{
	Logic_BE_t* aLogic;

	if (!_usersHandel || !_groupHandle || !_IP_handle)
	{
		return NULL;
	}

	aLogic = malloc( 1* sizeof(Logic_BE_t) );
	if (!aLogic)
	{
		return NULL;
	}

	aLogic->m_decodedMsg = calloc(1 , sizeof(ServerReceiveMessage_t));
	if (!aLogic->m_decodedMsg)
	{
		free(aLogic);
		return NULL;
	}

	aLogic->m_usersHandel = _usersHandel;
	aLogic->m_groupHandle = _groupHandle;
	aLogic->m_IP_handle = _IP_handle;

	aLogic->m_magicNumber = MAGIC_NUMBER_BE_LOGIC;
	return aLogic;
}

int LogicBE_SetServerPTR(Logic_BE_t* _logicBE, TCP_S_t* _server)
{
	if (! IsStructValid(_logicBE))
	{
		return FALSE;
	}

	_logicBE->m_net = _server;

	return TRUE;
}

void LogicBE_Destroy(Logic_BE_t* _logicBE)
{
	if (! IsStructValid(_logicBE))
	{
		perror("Ilagle Free");
		return;
	}

	_logicBE->m_magicNumber = 0;

	TCP_DestroyServer(_logicBE->m_net);
	free(_logicBE->m_decodedMsg);
	free(_logicBE);

	return;
}

int LogicBE_ReciveDataFunc(void* _data, size_t _sizeData, uint _socketNum, void* _contex)
{
	if (! IsStructValid(_contex))
	{
		return GEN_ERROR;
	}

	/* decode msg recived */
	if (! Protocol_DecodeServer(_data, _sizeData, ((Logic_BE_t*)_contex)->m_decodedMsg ) )
	{
		/* msg is not full? what to do? */
		perror("ERORR111\n");
		return GEN_ERROR;
	}

	switch ( ( (Logic_BE_t*)_contex)->m_decodedMsg->m_MessageType )
	{
		case MESSAGETYPE_SIGNUP:
			SignUp(_contex, ((Logic_BE_t*)_contex)->m_decodedMsg, _socketNum);
			break;

		case MESSAGETYPE_LOGIN:

			break;
		case MESSAGETYPE_LOGOUT:

			break;
		case MESSAGETYPE_DELETE_USER:

			break;
		case MESSAGETYPE_JOIN_GROUP:
			JoinGroup(_contex, ((Logic_BE_t*)_contex)->m_decodedMsg, _socketNum);
			break;

		case MESSAGETYPE_CREATE_GROUP:
			CreateGroup(_contex, ((Logic_BE_t*)_contex)->m_decodedMsg, _socketNum);
			break;

		case MESSAGETYPE_LEAVE_GROUP:

			break;
		case MESSAGETYPE_GET_ALL_GROUPS:

			break;
		default:
			warn("Unknown msg type %d recived from socket %d.\n", ( (Logic_BE_t*)_contex)->m_decodedMsg->m_MessageType , _socketNum );
			break;
	}

	/* clear struct for next transmission */
	FlushServerReceiveMessage_t( ( ( (Logic_BE_t*)_contex)->m_decodedMsg ) );

	return TRUE;
}

int LogicBE_NewClientFunc(uint _socketNum, void* _contex)
{

}
int LogicBE_ClientDissconnectedFunc(uint _socketNum, void* _contex)
{

}
int LogicBE_ErrorFunc(TCP_SERVER_USER_ERROR _status, uint _socketNum, void* _contex)
{

}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool IsStructValid(Logic_BE_t* _logicBE)
{
	return !(_logicBE == NULL || _logicBE->m_magicNumber != MAGIC_NUMBER_BE_LOGIC);
}

static bool FlushServerReceiveMessage_t(ServerReceiveMessage_t* _decodedMsg)
{
	if (!_decodedMsg)
	{
		return FALSE;
	}
	memset(_decodedMsg , 0, sizeof(ServerReceiveMessage_t));
	return TRUE;
}

static bool SignUp(Logic_BE_t* _logicBE, ServerReceiveMessage_t* _decodedMsg, uint _socketNum)
{
	if (strlen(_decodedMsg->m_userName) < MINIMAL_USER_PASSWORD || strlen(_decodedMsg->m_userName) > MAX_USERNAME )
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_SIGNUP, BackEnd_USER_NAME_INVALID, "",  0);
		return FALSE;
	}

	if (strlen(_decodedMsg->m_password) < MINIMAL_USER_PASSWORD || strlen(_decodedMsg->m_password) > MAX_PASSWORD )
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_SIGNUP, BackEnd_PASSWORD_INVALID, "",  0);
		return FALSE;
	}

	if (UsersHandle_IsUserExist(_logicBE->m_usersHandel, _decodedMsg->m_userName) )
	{
		/* username exsists */
		LogicBE_Send(_logicBE , _socketNum, MESSAGETYPE_SIGNUP, BackEnd_USER_NAME_TAKEN, "",  0);
		return FALSE;
	}

	if (! UsersHandle_AddNewUser(_logicBE->m_usersHandel, _decodedMsg->m_userName, _decodedMsg->m_password, NULL, 0, _socketNum) )
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_SIGNUP, BackEnd_SYSTEM_FAIL, "",  0);
		return FALSE;
	}

	LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_SIGNUP, BackEnd_SUCCESS, "",  0);

	return TRUE;
}

static bool CreateGroup(Logic_BE_t* _logicBE, ServerReceiveMessage_t* _decodedMsg, uint _socketNum)
{
	sockaddr_in_t* addrs;

	if (strlen(_decodedMsg->m_groupName) > MAX_GROUP_NAME)
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_CREATE_GROUP, BackEnd_GROUP_NAME_INVALID, "",  0);
		return FALSE;
	}

	addrs = IP_Handle_GetFreeIP(_logicBE->m_IP_handle);
	if (!addrs)
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_CREATE_GROUP, BackEnd_NO_FREE_IP, "",  0);
		return FALSE;
	}

	if (GroupsHandel_IsGroupExist(_logicBE->m_groupHandle, _decodedMsg->m_groupName) )
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_CREATE_GROUP, BackEnd_GROUP_NAME_TAKEN, "",  0);
		return FALSE;
	}

	if (! GroupsHandel_NewGroup(_logicBE->m_groupHandle, _decodedMsg->m_groupName, _socketNum, addrs) )
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_CREATE_GROUP, BackEnd_SYSTEM_FAIL, "",  0);
		return FALSE;
	}

	LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_CREATE_GROUP, BackEnd_SUCCESS, addrs,  sizeof(addrs));

	return TRUE;
}


static bool JoinGroup(Logic_BE_t* _logicBE, ServerReceiveMessage_t* _decodedMsg, uint _socketNum)
{
	sockaddr_in_t* addrs = NULL;

	if (strlen(_decodedMsg->m_groupName) > MAX_GROUP_NAME || strlen(_decodedMsg->m_groupName) <= 1)
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_JOIN_GROUP, BackEnd_GROUP_NAME_INVALID, "",  0);
		return FALSE;
	}

	if (!GroupsHandel_IsGroupExist(_logicBE->m_groupHandle, _decodedMsg->m_groupName) )
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_JOIN_GROUP, BackEnd_GROUP_DO_NOT_EXIST, "",  0);
		return FALSE;
	}

	/* get group  IP from groupHndl */
	if ( !GroupsHandel_JoinGroup(_logicBE->m_groupHandle, _decodedMsg->m_groupName, _socketNum, &addrs) )
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_JOIN_GROUP, BackEnd_USER_NAME_TAKEN, "",  0);
		return FALSE;
	}

//	addrs = GroupsHandel_GetGroupAddres(_logicBE->m_groupHandle , _decodedMsg->m_groupName);
	if (!addrs)
	{
		LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_JOIN_GROUP, BackEnd_NO_FREE_IP, "",  0);
		return FALSE;
	}

	LogicBE_Send(_logicBE, _socketNum, MESSAGETYPE_JOIN_GROUP, BackEnd_SUCCESS, addrs,  sizeof(addrs));

	return TRUE;
}


static int LogicBE_Send(Logic_BE_t* _logic, uint _socketNum, MessageType _msgType, BackEndStatus _responseResult, void* _msg,  uint _msgLength)
{

	/* send response */
	char buffer[MAX_MESSAGE_LENGTH] = { '\0' };
	uint length;
	int sentBytes;

	/* TODO fill Switch Case */
	switch (_msgType)
	{
		case MESSAGETYPE_SIGNUP:
			length = Protocol_EncodeSignUp_Response(_responseResult, buffer);
			break;

		case MESSAGETYPE_LOGIN:

			break;
		case MESSAGETYPE_LOGOUT:

			break;
		case MESSAGETYPE_DELETE_USER:

			break;
		case MESSAGETYPE_JOIN_GROUP:
			length = Protocol_EncodeJoinGroup_Response(_responseResult, *(sockaddr_in_t*)_msg, buffer);
			break;
		case MESSAGETYPE_CREATE_GROUP:
			length = Protocol_EncodeNewGroup_Response(_responseResult, *(sockaddr_in_t*)_msg, buffer);
			break;

		case MESSAGETYPE_LEAVE_GROUP:

			break;
		case MESSAGETYPE_GET_ALL_GROUPS:

			break;
		default:
			warn("Unknown msg type %d to send to socket %d.\n", _msgType , _socketNum );
			break;
	}

	sentBytes = TCP_Send(_socketNum, buffer, length);

	return sentBytes;
}

