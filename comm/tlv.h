#ifndef __TLV__
#define __TLV__

#include "defines.h"
#include "Protocol.h"

/* remove to turn on debug printout */
#define NDEBUG  
 
/** 
 *  @file tlv.h
 *  @brief encoding / decodeing system for commanacation. 
 * 
 *  @details Type Legnth Value. a system to send and recive information.  wraps varius type of info and varied size into package.
 *	functions are unsafe. inadaqunt space would result in undifined behiver.
 * 
 *  @author Author Yuval Hamberg (yuval.hamberg@gmail.com) 
 *	@date April 2017
 * 
 *  @bug No known bugs.
 *	@bug check that no str function are called that prevent non string information.
 */ 


/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* #define TLV_TYPE_LENGTH 1 			*/ /* size in char of type of information send */
#define TLV_META_LENGTH_LENGTH TLV_LENGHT_LENGTHT			/* size in char of number that is the size of str information send. eg. 2 digits is 42 */
#define TLV_META_LENGTH HEADER_LENGTH


typedef enum TLV_Result {
	TLV_SUCCESS = 0,
	TLV_MORE_TLVS_TO_DECODE, 		
	TLV_TRANCATED_TLV, 			
	TLV_NO_TLV_FOUND,
	TLV_INPUT_ERROR,
	TLV_UNKNOWN_ERROR,
	TLV_UNKNOWN_TYPE,
	TLV_ALLOCATION_ERROR
} TLV_Result;

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */



/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/** @brief TLV_encoder
 *  @details encode a stream of information.
 *
 * @params [in] char* _inputStr: information to be encoded
 * @params [in] char _dataType: the type of information encoded
 * @params [in] Uint dataLenght: the length of information in bytes.
 *
 * @params [out] char* _tlvedString: the encoded information
 * @params [out] Uint* _tlvedStringLength: the encoded information length in bytes.
 *
 * @returns check retuen values in above TLV_Result enum.
 * @retval TLV_Result
 */
TLV_Result TLV_encoder(char* _inputStr, char _dataType, Uint dataLenght, char* _tlvedString, Uint* _tlvedStringLength);



/** @brief TLV_decode
 *  @details decode a stream of information.
 *
 * @params [in] char* _TLV_String: the stream of information.
 * @params [in] Uint _TLV_StringLength:  the stream of information length in bytes.
 *
 * @params [out] char* _decodedStr: the information inside the stream.
 * @params [out] Uint* _decodedStrLength: the information inside the stream length in bytes..
 * @params [out] char* _datatypeFound: data type reprentation.
 * @params [out] char** _nextTLV_Ptr: pointer to the next call if user wants.
 * @params [out] Uint* _nextTLV_Lenth: the length in bytes of the next call.
 *
 * @returns check retuen values in above TLV_Result enum.
 * @retval TLV_Result
 */
TLV_Result TLV_decode(char* _TLV_String, Uint _TLV_StringLength, char* _decodedStr, Uint* _decodedStrLength, char* _datatypeFound, char** _nextTLV_Ptr, Uint* _nextTLV_Lenth);


#endif /* __TLV__ */
