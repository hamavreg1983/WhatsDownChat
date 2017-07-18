/**
 *  @file logic_backEnd.h
 *
 *  @date Jul 15, 2017
 *  @author Yuval Hamberg
 *
 *  @brief handle the logic and decision making for the Back End (server side) of whatDown char app.
 */

#ifndef LOGIC_BACKEND_H_
#define LOGIC_BACKEND_H_


#include "defines.h"
#include "tcp.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct Logic_BE Logic_BE_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief create and setup for the process
 * @param _usersHandel a pointer the the module the deals with Users.
 * @param _groupHandle a pointer the the module the deals with chat groups.
 * @param _IP_handle a pointer the the module the deals with allocatin IP address.
 * @return a pointer to the struct
 */
Logic_BE_t* LogicBE_Create(void* _usersHandel, void* _groupHandle, void* _IP_handle);

/**
 * @brief add to the logic the pointer to the TCP server. as both modules in to be setup at the same time, the pointer is added just after create.
 * @param _logicBE the pointer to the struct
 * @param _server a pointer to the TCP server
 * @return TRUE for succses and FALSE if one of the parameters is wrong
 */
bool LogicBE_SetServerPTR(Logic_BE_t* _logicBE, TCP_S_t* _server);

/**
 * @brief cleans up after the processing
 * @param _logic a pointer to the TCP server
 */
void LogicBE_Destroy(Logic_BE_t* _logic);

/** call back functions (from the TCP server) */

/**
 * @brief call back function when TCP server get a msg.
 * @param _data the information received
 * @param _sizeData the number of bytes received
 * @param _socketNum file descriptor of the incoming data originated from.
 * @param _contex was given to the TCP server at create. usually the pointer to Logic_BE.
 * @return TRUE for success and FALSE for errors
 */
bool LogicBE_ReciveDataFunc(void* _data, size_t _sizeData, uint _socketNum, void* _contex);

/**
 * @brief call bacl function when TCP server get a new client connected to .
 * @param _socketNum file descriptor of the incoming data originated from.
 * @param _contex was given to the TCP server at create. usually the pointer to Logic_BE.
 * @return TRUE for success and FALSE for errors
 */
int LogicBE_NewClientFunc(uint _socketNum, void* _contex);

/**
 * @brief call bacl function when TCP server get a client disconnect to .
 * @param _socketNum file descriptor of the incoming data originated from.
 * @param _contex was given to the TCP server at create. usually the pointer to Logic_BE.
 * @return TRUE for success and FALSE for errors
 */
int LogicBE_ClientDissconnectedFunc(uint _socketNum, void* _contex);

/**
 * @brief call bacl function when TCP server get an error.
 * @param _status represnt the error.
 * @param _socketNum file descriptor of the incoming data originated from.
 * @param _contex was given to the TCP server at create. usually the pointer to Logic_BE.
 * @return TRUE for success and FALSE for errors
 */
int LogicBE_ErrorFunc(int _status, uint _socketNum, void* _contex);




#endif /* LOGIC_BACKEND_H_ */
