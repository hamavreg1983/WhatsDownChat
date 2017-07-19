
#include <stdlib.h> /* atoi */
#include <string.h> /* strncpy */
#include <stdio.h> /* sprintf */
#include <err.h> /* warn & err */

#include "tlv.h"
#include "defines.h"


/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */




/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */



/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


TLV_Result TLV_encoder(char* _inputStr, char _datatype, Uint dataLenght, char* _tlvedString, Uint* _tlvedStringLength)
{
	int sprintfResult;
	if (NULL == _inputStr || NULL == _tlvedString || 0 == dataLenght)
	{
		warn("TLV_encoder error. checkparam. _inputStr:%s _tlvedString:%s dataLenght:%d", _inputStr, _tlvedString, dataLenght);
		return TLV_INPUT_ERROR;
	}
	
	sprintfResult = sprintf(_tlvedString, "%c%0*d%s", _datatype, TLV_META_LENGTH_LENGTH, dataLenght, _inputStr);
	if (-1 == sprintfResult) 
	{
		warn("TLV_encoder error. sprintf %d. _inputStr:%s _tlvedString:%s dataLenght:%d", sprintfResult, _inputStr, _tlvedString, dataLenght);
		return TLV_UNKNOWN_ERROR;
	}
	
	*_tlvedStringLength = sprintfResult;
	
	#if !defined(NDEBUG)
		printf(" TLV: %s lengthStr:%d\n", _tlvedString, sprintfResult);
	#endif
	
	return TLV_SUCCESS;
}



TLV_Result TLV_decode(char* _TLV_String, Uint _TLV_StringLength, char* _decodedStr, Uint* _decodedStrLength, char* _datatypeFound, char** _nextTLV_Ptr, Uint* _nextTLV_Lenth)
{
	Uint lengthStr;
	char temp_lengthStr[TLV_META_LENGTH_LENGTH];
	Uint totalSizeOfTLV;
	
	if (NULL == _TLV_String || NULL == _decodedStr || TLV_TYPE_LENGTH + TLV_META_LENGTH_LENGTH >= _TLV_StringLength)
	{
		*_nextTLV_Ptr = NULL;
		*_nextTLV_Lenth = 0;
		_datatypeFound = NULL;
		_decodedStr = NULL;
		
		warn("TLV_decode Bad Input _TLV_String:%s _decodedStr:%s " , _TLV_String , _decodedStr);
		return TLV_INPUT_ERROR;
	}
	
	/* if user doent want type, he can send NULL pointer */
	if (NULL != _datatypeFound)
	{
		strncpy(_datatypeFound, _TLV_String, TLV_TYPE_LENGTH);
	}
	
	strncpy(temp_lengthStr, _TLV_String + TLV_TYPE_LENGTH , TLV_META_LENGTH_LENGTH);
	lengthStr = atoi(temp_lengthStr);
	*_decodedStrLength = lengthStr;
	
	strncpy(_decodedStr, _TLV_String + TLV_TYPE_LENGTH + TLV_META_LENGTH_LENGTH, lengthStr);
/*	_decodedStr[lengthStr] = '\0';*/
	
	
	totalSizeOfTLV = TLV_TYPE_LENGTH + TLV_META_LENGTH_LENGTH + lengthStr; /* for readabilty */
	
	#if !defined(NDEBUG)
		printf(" _datatypeFound:%c\n",*_datatypeFound);
		printf(" lengthStr:%d\n",lengthStr);
		printf(" _decodedStr:%s\n",_decodedStr);
	#endif
/*	warn("TLV_decode normal. _TLV_String:%s _decodedStr:%s " , _TLV_String , _decodedStr);*/
	
	/* if there is more TLVs in input string */
	if (_TLV_StringLength > totalSizeOfTLV)
	{
		*_nextTLV_Ptr = (_TLV_String + totalSizeOfTLV);
		*_nextTLV_Lenth = (_TLV_StringLength - totalSizeOfTLV);
/*		printf("\nTEST _nextTLV_Ptr:%s\n", *_nextTLV_Ptr);*/
		return TLV_MORE_TLVS_TO_DECODE;
	}
	
	/* if didn't get all of the input string needed and was cut in the middle */
	if (_TLV_StringLength < totalSizeOfTLV)
	{
		warn("TLV_TRANCATED_TLV beacouse : _TLV_StringLength %d < totalSizeOfTLV %d",_TLV_StringLength, totalSizeOfTLV);
		*_nextTLV_Ptr = _TLV_String;
		*_nextTLV_Lenth = _TLV_StringLength;
		return TLV_TRANCATED_TLV;
	}
	
	/* progreccing the pointer to the next empty spot */
	
/*	*_nextTLV_Ptr = (_TLV_String + TLV_META_LENGTH + *_decodedStrLength);*/
	*_nextTLV_Ptr = (_TLV_String + totalSizeOfTLV);
	*_nextTLV_Lenth = (_TLV_StringLength - totalSizeOfTLV); /* should be zero */
	
	return TLV_SUCCESS;
}




/* ~~~ Internal function  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


