/*
 * protocol.c
 *
 *  @date Jul 12, 2017
 *  @authorYuval Hamberg
 */

#include <stdlib.h> /* atoi */
#include <string.h> /* strncpy */
#include <stdio.h> /* sprintf */
#include <err.h> /* warn & err */
/* inet */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "defines.h"
#include "Protocol.h"
#include "tlv.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* TEMP */
//#define TRUE 1
//#define FALSE 0


/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */



/* ~~~ Internal function forward declaration ~~~~~~~~~~~~~~~~~~~~~~~~ */

static int CopyUntilDelimiter(void* _dst, void* _src, size_t _length, char* _delim, uint _delimLength);
static bool IsDelim(void* _msg, char* _delim, uint _delimLength);
static int DecodeGroupsName(ClientReceiveMessage_t* _message , void* decodedStr, uint groupsLength, char* _delim, uint _delimLength);
static int DecodeAddress(ClientReceiveMessage_t* _message , void* _decodedStr, char* _delim, uint _delimLength);

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int Protocol_EncodeSignUp(const char* _newUserName, const char* _password, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _newUserName || NULL == _password || NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%s%s%s%s", _newUserName, DELIMITER, _password, DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_SIGNUP, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}


int Protocol_EncodeSignUp_Response(BackEndStatus _responseStatus, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%c%s", _responseStatus, DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_SIGNUP, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}

int Protocol_EncodeLogIn(const char* _userName, const char* _password, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _userName || NULL == _password || NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%s%s%s%s", _userName, DELIMITER, _password, DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_LOGIN, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}

int Protocol_EncodeLogIn_Response(BackEndStatus _responseStatus, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%c%s", _responseStatus, DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_LOGIN, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}

int Protocol_DecodeClient(void* _dataToDecode, size_t _lenght, ClientReceiveMessage_t* _message )
{
	char decodedStr[MAX_MESSAGE_LENGTH];

	char datatypeFound;
	uint decodedStrLength;

	char* nextTLV_Ptr;
	uint nextTLV_Lenth;
	TLV_Result result;

	if (NULL == _dataToDecode || NULL == _message )
	{
		return FALSE;
	}

	result = TLV_decode(_dataToDecode, _lenght, decodedStr, &decodedStrLength, &datatypeFound, &nextTLV_Ptr, &nextTLV_Lenth);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	_message->m_messageType = datatypeFound;
	switch (_message->m_messageType)
		{
			case MESSAGETYPE_RESPONS:
				/* not used */
				warn("Didn't expect this response");
				return FALSE;
				break;
			case MESSAGETYPE_SIGNUP:
				_message->m_status = decodedStr[0];
				break;
			case MESSAGETYPE_LOGIN:
				_message->m_status = decodedStr[0];
				break;
			case MESSAGETYPE_LOGOUT:
				_message->m_status = decodedStr[0];
				break;
			case MESSAGETYPE_DELETE_USER:
				_message->m_status = decodedStr[0];
				break;
			case MESSAGETYPE_JOIN_GROUP:
				_message->m_status = decodedStr[0];
				DecodeAddress(_message , decodedStr, DELIMITER, DELIMITER_LENGHT);
				break;

			case MESSAGETYPE_CREATE_GROUP:
				_message->m_status = decodedStr[0];
				if (_message->m_status == BackEnd_SUCCESS)
				{
					DecodeAddress(_message , decodedStr, DELIMITER, DELIMITER_LENGHT);
				}
				break;

			case MESSAGETYPE_LEAVE_GROUP:
				_message->m_status = decodedStr[0];
				break;
			case MESSAGETYPE_GET_ALL_GROUPS:
				_message->m_status = decodedStr[0];
				DecodeGroupsName(_message , decodedStr, decodedStrLength - 1 - DELIMITER_LENGHT, DELIMITER, DELIMITER_LENGHT);
				break;

			default:
				/* error */
				return FALSE;
				break;
		}

	return TRUE;
}

bool Protocol_DecodeServer(void* _dataToDecode, size_t _lenght, ServerReceiveMessage_t* _message )
{
	char decodedStr[MAX_MESSAGE_LENGTH];

	char datatypeFound;
	uint decodedStrLength;

	char* nextTLV_Ptr;
	uint nextTLV_Lenth;
	TLV_Result result;
	int length;

	if (NULL == _dataToDecode || NULL == _message )
	{
		return FALSE;
	}

	result = TLV_decode(_dataToDecode, _lenght, decodedStr, &decodedStrLength, &datatypeFound, &nextTLV_Ptr, &nextTLV_Lenth);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	_message->m_MessageType = datatypeFound;
	switch (datatypeFound)
	{
		case MESSAGETYPE_RESPONS:
			/* not related to here */
			return FALSE;
			break;
		case MESSAGETYPE_SIGNUP:
			length = CopyUntilDelimiter( _message->m_userName , decodedStr, decodedStrLength, DELIMITER, DELIMITER_LENGHT);
			length = CopyUntilDelimiter( _message->m_password , decodedStr + length + DELIMITER_LENGHT, decodedStrLength - length - DELIMITER_LENGHT, DELIMITER, DELIMITER_LENGHT);
			break;
		case MESSAGETYPE_LOGIN:
			length = CopyUntilDelimiter( _message->m_userName , decodedStr, decodedStrLength, DELIMITER, DELIMITER_LENGHT);
			length = CopyUntilDelimiter( _message->m_password , (char*) decodedStr + length + DELIMITER_LENGHT, decodedStrLength, DELIMITER, DELIMITER_LENGHT);
			break;
		case MESSAGETYPE_LOGOUT:
			CopyUntilDelimiter( _message->m_userName , decodedStr, decodedStrLength, DELIMITER, DELIMITER_LENGHT);
			break;
		case MESSAGETYPE_DELETE_USER:
			CopyUntilDelimiter( _message->m_userName , decodedStr, decodedStrLength, DELIMITER, DELIMITER_LENGHT);
			break;
		case MESSAGETYPE_JOIN_GROUP:
			CopyUntilDelimiter(_message->m_groupName, decodedStr, decodedStrLength, DELIMITER, DELIMITER_LENGHT);
			break;
		case MESSAGETYPE_CREATE_GROUP:
			CopyUntilDelimiter(_message->m_groupName, decodedStr, decodedStrLength, DELIMITER, DELIMITER_LENGHT);
			break;
		case MESSAGETYPE_LEAVE_GROUP:
			CopyUntilDelimiter(_message->m_groupName, decodedStr, decodedStrLength, DELIMITER, DELIMITER_LENGHT);
			break;
		case MESSAGETYPE_GET_ALL_GROUPS:
			/* do nothing more */
			break;

		default:
			/* error */
			return FALSE;
			break;
	}

	return TRUE;
}

int Protocol_EncodeNewGroup(const char* _groupName, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _groupName || NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%s%s", _groupName, DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_CREATE_GROUP, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}

int Protocol_EncodeNewGroup_Response(BackEndStatus _responseStatus, sockaddr_in_t m_groupAdrres, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%c%s%s%s%u%s", _responseStatus, DELIMITER, inet_ntoa(m_groupAdrres.sin_addr) , DELIMITER, ntohs(m_groupAdrres.sin_port ), DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_CREATE_GROUP, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}

int Protocol_EncodeJoinGroup(const char* _groupNameToJoin, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _groupNameToJoin || NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%s%s", _groupNameToJoin, DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_JOIN_GROUP, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}

int Protocol_EncodeJoinGroup_Response(BackEndStatus _responseStatus, sockaddr_in_t m_groupAdrres, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%c%s%s%s%u%s", _responseStatus, DELIMITER, inet_ntoa(m_groupAdrres.sin_addr) , DELIMITER, ntohs(m_groupAdrres.sin_port ), DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_JOIN_GROUP, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}

int Protocol_EncodeGetAllGroups(void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%s", DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_GET_ALL_GROUPS, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;
}

int Protocol_EncodeGetAllGroups_Response(BackEndStatus _responseStatus, const char* _groupsNames, size_t _numGroups, void* _buffer)
{
	char tempMsg[MAX_MESSAGE_LENGTH];
	int length = 0;
	uint tlvLength;
	TLV_Result result;

	if (NULL == _buffer)
	{
		return GEN_ERROR;
	}

	length = sprintf(tempMsg, "%c%s%.*s%s", _responseStatus, DELIMITER, (int)_numGroups, _groupsNames , DELIMITER);

	result = TLV_encoder(tempMsg, (char) MESSAGETYPE_GET_ALL_GROUPS, length, _buffer, &tlvLength);
	if (!(result == TLV_SUCCESS || result == TLV_MORE_TLVS_TO_DECODE))
	{
		return GEN_ERROR;
	}

	return tlvLength;

}



/* ~~~ Internal function  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int CopyUntilDelimiter(void* _dst, void* _src, size_t _length, char* _delim, uint _delimLength)
{
	if( NULL == _dst || NULL == _src || NULL == _delim)
	{
		return GEN_ERROR;
	}

	uint charNum = 0;

	char* srcLoc = _src;
	char* dstLoc = _dst;

	while( charNum <= _length )
	{
		if ( IsDelim( ( srcLoc + charNum), _delim, _delimLength) == TRUE )
		{
			/* found a delimiter, so stop copying */
			dstLoc[charNum] = '\0';
			break;
		}
		else {
			/* copy char by char */
			dstLoc[charNum] = srcLoc[charNum];
			++charNum;
		}
	}

	return charNum;
}

static bool IsDelim(void* _msg, char* _delim, uint _delimLength)
{
	uint i;

	char* tmpMsg = (char*) _msg;

	for (i = 0; i <_delimLength ; ++i)
	{
		if ( tmpMsg[i] != _delim[i] )
		{
			return FALSE;
		}
	}

	return TRUE;
}

static int DecodeGroupsName(ClientReceiveMessage_t* _message , void* _decodedStr, uint _groupsLength, char* _delim, uint _delimLength)
{
	uint src_itr = 1 + DELIMITER_LENGHT;
	uint dsc_itr = 0;
	uint general_itr = 0;
	uint groupNum = 0;
	char numOfGroupsRecived[5];

	general_itr = CopyUntilDelimiter(numOfGroupsRecived + dsc_itr, (char*)_decodedStr + src_itr, _groupsLength, _delim, _delimLength);
	_message->m_numberOfGroups = atoi(numOfGroupsRecived);
	src_itr += general_itr + DELIMITER_LENGHT;
	dsc_itr += 0;

	while (dsc_itr < _groupsLength && groupNum <= _message->m_numberOfGroups)
	{
		general_itr = CopyUntilDelimiter(_message->m_GroupName + dsc_itr, (char*)_decodedStr + src_itr, _groupsLength, _delim, _delimLength);
		src_itr += general_itr + DELIMITER_LENGHT;
		dsc_itr += general_itr + 1;
		++groupNum;
	}

//	_message->m_numberOfGroups = groupNum;

	return general_itr;
}

static int DecodeAddress(ClientReceiveMessage_t* _message , void* _decodedStr, char* _delim, uint _delimLength)
{
	char ip[20] = {0};
	char port[10] = {0};

	int itr = 1 + _delimLength;
	itr += CopyUntilDelimiter( ip , ((char*)_decodedStr) + itr, MAX_MESSAGE_LENGTH, _delim, _delimLength);
	itr += _delimLength;
	itr += CopyUntilDelimiter( port , ((char*)_decodedStr) + itr, MAX_MESSAGE_LENGTH, _delim, _delimLength);

	_message->m_groupAdrres.sin_addr.s_addr =  inet_addr(ip) ;
	_message->m_groupAdrres.sin_port = htons(atoi(port));

	return itr;
}


