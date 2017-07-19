/**
 *  @file groupsHandle.h
 *
 *  @date Jul 16, 2017
 *  @author Yuval Hamberg
 *
 *  @brief handle the groups of chats information. the groups that exist, their address, their members and so on.
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

int GroupsHandel_GetGroupsName(GroupHandel_t* _groupsHndl, char* _groupsNames_out, size_t _bufferSize, size_t* _groupsLength_out);


#endif /* GROUPSHANDLE_H_ */
