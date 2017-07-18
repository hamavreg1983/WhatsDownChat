/**
 *  @file logicFE.h
 *
 *  @date Jul 16, 2017
 *  @author Yuval Hamberg
 *
 *  @brief handle the logic and decision making for the Front End (client side) of whatDown char app.
 */

#ifndef LOGICFE_H_
#define LOGICFE_H_

#include "defines.h"
#include "tcp_client.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct Logic_FE Logic_FE_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief create and setup
 * @param netClient a pointer to the TCP net for client connection
 * @return the pointer to the struct
 */
Logic_FE_t* LogicFE_Create(TCP_C_t* netClient);

/**
 * @brief cleans up after the processing
 * @param _logic
 */
void LogicFE_Destroy(Logic_FE_t* _logic);

/**
 * @brief Handle the send and receive of Signup request and answer to the server.
 * @param _logic the pointer to the module struct.
 * @param _username char* msg
 * @param _password char* msg
 * @return TRUE for success. FALSE for fail
 */
int LogicFE_Signup(Logic_FE_t* _logic, const char* _username, const char* _password);

/**
 * @brief Handle the send and receive of login request and answer to the server.
 * @param _logic the pointer to the module struct.
 * @param _username char* msg
 * @param _password char* msg
 * @return TRUE for success. FALSE for fail
 */
bool LogicFE_Login(Logic_FE_t* _logic, const char* _username, const char* _password);

/**
 * @brief Handle the send and receive of login request and answer to the server.
 * @param _logic the pointer to the module struct.
 * @param _groupName char* the group name to be created.
 * @return TRUE for success. FALSE for fail
 */
int LogicFE_CreateGroup(Logic_FE_t* _logic, const char* _groupName);

/**
 * @brief Handle the send and receive of join an existing group request and answer to the server.
 * @param _logic the pointer to the module struct.
 * @param _groupName char* the group name to be created.
 * @return TRUE for success. FALSE for fail
 */
int LogicFE_JoinGroup(Logic_FE_t* _logic, const char* _groupName);

/**
 * @brief Handle the send and receive of join an existing group request and answer to the server.
 * @param _logic  the pointer to the module struct.
 * @param _GroupsName_out a string with all the groups name. divided by delimiter
 * @param _numOfGroups_out how many group have been read.
 * @param _bufferSize the max size of buffer to be copied to.
 * @return
 */
int LogicFE_GetAllGroupsName(Logic_FE_t* _logic, char* _GroupsName_out, uint* _numOfGroups_out, uint _bufferSize);


/* more function to come */

#endif /* LOGICFE_H_ */
