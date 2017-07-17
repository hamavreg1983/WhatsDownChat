/*
 * groupsHandle.h
 *
 *  Created on: Jul 16, 2017
 *      Author: uv
 */

#ifndef GROUPSHANDLE_H_
#define GROUPSHANDLE_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct sockaddr_in sockaddr_in_t;

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct GroupHandel GroupHandel_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

GroupHandel_t* GroupsHandel_Create();

void GroupsHandel_Destroy(GroupHandel_t* _groupsHndl);

bool GroupsHandel_NewGroup(GroupHandel_t* _groupsHndl, const char* _groupName, uint _socket, sockaddr_in_t* _addrs);

bool GroupsHandel_JoinGroup(GroupHandel_t* _groupsHndl, const char* _groupName, uint _socket, sockaddr_in_t** _addrsOUT);

bool GroupsHandel_LeaveGroup(GroupHandel_t* _groupsHndl, const char* _groupName, uint _socket);

bool GroupsHandel_IsGroupExist(GroupHandel_t* _groupsHndl, const char* _groupName);

sockaddr_in_t* GroupsHandel_GetGroupAddres(GroupHandel_t* _groupsHndl, const char* _groupName);


#endif /* GROUPSHANDLE_H_ */
