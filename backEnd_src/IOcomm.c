/*
 * IOcomm.c
 *
 *  Created on: Jul 13, 2017
 *      Author: uv
 */

#include "tcp.h"
#include "Protocol.h"
#include "defines.h"


int TempPrint(ServerReceiveMessage_t* DecodedMsg)
{
	printf("type: %d\n", DecodedMsg->m_MessageType);
	printf("user: %s\n", DecodedMsg->m_userName);
	printf("pass: %s\n", DecodedMsg->m_password);



	return TRUE;
}

int IO_CommServerRecive(void* _data, size_t _sizeData, uint _socketNum, void* _contex)
{
	ServerReceiveMessage_t DecodedMsg;

	printf("raw data recived:%s\n", (char*) _data);


	if (! Protocol_DecodeServer(_data, _sizeData, &DecodedMsg) )
	{
		perror("ERORR111\n");
	}

	TempPrint(&DecodedMsg);

	char buffer[MAX_MESSAGE_LENGTH];
	uint length;
	length = Protocol_EncodeSignUp_Response(BackEnd_USER_NAME_INVALID, buffer);

	TCP_Send(_socketNum, buffer, length);

	return -1;
}



