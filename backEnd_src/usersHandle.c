/*
 * usersHandle.c
 *
 *  Created on: Jul 15, 2017
 *      Author: yuval
 */

#include <string.h> /* strcpy */
#include "usersHandle.h"
#include "Protocol.h"
#include "hashmap.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define USERS_HANDLE_MAGIC_NUMBER 0xfacefade
#define USER_MAGIC_NUMBER 0xfaceabcd

#define CAPACITY 128

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct UsersHandle
{
	uint m_magicNumber;

	struct DSHashMap* m_continer;
};

typedef struct User
{
	uint m_magicNumber;

	char m_userName[MAX_USERNAME];
	char m_password[MAX_PASSWORD];
	char m_nickName[MAX_USERNAME]; /* not implemented */
	uint m_premission; /* not implemented */
	int m_socketNum;
	bool m_isConnected;

} User_t;



/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~~~~~~~~ */
bool IsStructValid(UsersHandle_t* _usersHandel);

User_t* CreateValue(char* _userName, char* _password, char* _nickname, uint _premission, int _socketNum);

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

UsersHandle_t* UsersHandle_Create()
{

	UsersHandle_t* userHandel;
	userHandel = malloc (1 * sizeof(UsersHandle_t) );
	if (!userHandel)
	{
		return NULL;
	}

	userHandel->m_continer = ds_hashmap_create();
	if (! userHandel->m_continer)
	{
		free(userHandel);
		return NULL;
	}

	userHandel->m_magicNumber = USERS_HANDLE_MAGIC_NUMBER;

	return userHandel;
}

void UsersHandle_Destroy(UsersHandle_t* _usersHandel)
{
	if (! IsStructValid(_usersHandel))
	{
		return;
	}

	_usersHandel->m_magicNumber = 0;
	ds_hashmap_free( _usersHandel->m_continer , TRUE , TRUE); /* last argumetn mgth free core dump */

	free(_usersHandel);

	return;
}

int UsersHandle_AddNewUser(UsersHandle_t* _usersHandel, char* _userName, char* _password, char* _nickname, uint _premission, int _socketNum)
{
	if (! IsStructValid(_usersHandel) || !_userName || ! _password)
	{
		return FALSE;
	}

	/* check if exsist */
	if (UsersHandle_IsUserExist(_usersHandel , _userName) )
	{
		/* username key exsists */
		return FALSE;
	}

	User_t* value = CreateValue(_userName, _password, _nickname, _premission, _socketNum);
	if (!value)
	{
		return FALSE;
	}

	ds_hashmap_put_str(_usersHandel->m_continer, _userName, value);

	return TRUE;
}

int UsersHandle_IsUserExist(UsersHandle_t* _usersHandel, char* _userName)
{
	if (! IsStructValid(_usersHandel) || !_userName)
	{
		return FALSE;
	}

	if (NULL == ds_hashmap_get_str( _usersHandel->m_continer , _userName) )
	{
		/* username key exsists */
		return FALSE;
	}

	return TRUE;
}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

bool IsStructValid(UsersHandle_t* _usersHandel)
{
	return (NULL != _usersHandel) || (_usersHandel->m_magicNumber == USERS_HANDLE_MAGIC_NUMBER);
}

User_t* CreateValue(char* _userName, char* _password, char* _nickname, uint _premission, int _socketNum)
{
	if (!_userName || ! _password)
	{
		return NULL;
	}

	User_t* value;
	value = malloc(1 * sizeof (User_t) );
	if(!value)
	{
		return NULL;
	}

	strncpy(value->m_userName, _userName, MAX_USERNAME);
	strncpy(value->m_password, _password, MAX_PASSWORD);
	if (_nickname)
	{
		strncpy(value->m_nickName, _nickname, MAX_USERNAME);
	}
	value->m_premission = _premission;
	value->m_socketNum = _socketNum;
	value->m_magicNumber = USER_MAGIC_NUMBER;

	return value;
}





