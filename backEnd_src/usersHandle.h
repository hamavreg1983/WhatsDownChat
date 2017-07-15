/*
 * usersHandle.h
 *
 *  Created on: Jul 15, 2017
 *      Author: yuval
 */

#ifndef USERSHANDLE_H_
#define USERSHANDLE_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct UsersHandle UsersHandle_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

UsersHandle_t* UsersHandle_Create();

void UsersHandle_Destroy(UsersHandle_t* _usersHandel);

int UsersHandle_AddNewUser(UsersHandle_t* _usersHandel, char* _userName, char* _password, char* _nickname, uint _premission, int _socketNum);

bool UsersHandle_RemoveUser(UsersHandle_t* _usersHandel, char* _userName);

int UsersHandle_CountUsers(UsersHandle_t* _usersHandel);

bool UsersHandle_IsUserExist(UsersHandle_t* _usersHandel, char* _userName);


#endif /* USERSHANDLE_H_ */
