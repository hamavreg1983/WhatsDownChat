/*
 * groupsHandle.c
 *
 *  Created on: Jul 16, 2017
 *      Author: uv
 */

#include <string.h>
#include "groupsHandle.h"
#include "hashmap.h"
#include "Protocol.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define MAGIC_NUMBER_GRP_HNDL 0xdeadface
#define MAGIC_NUMBER_GRP_UNT 0xdeadbaac

#define MAX_USERS_IN_GROUP 1024

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
struct GroupHandel
{
	uint m_magicNumber;

	struct DSHashMap* m_groupContiner;

};

typedef struct GroupUnit
{
	uint m_magicNumber;

	char m_groupName[MAX_GROUP_NAME];
	int m_userInGroupNum;
	struct sockaddr_in* m_groupAddrs;
	int m_usersSockets[MAX_USERS_IN_GROUP];

} GroupUnit_t;

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */
static bool IsStructValid(GroupHandel_t* _groupsHndl);
static GroupUnit_t* CreateValue(const char* _groupName, struct sockaddr_in* m_groupAddrs, uint _socketNum);
static void DestoyValue(GroupUnit_t* _group);
static bool AddUser2Group(GroupUnit_t* _group, uint _socketNum);
static GroupUnit_t* GroupsHandel_FindGroup(GroupHandel_t* _groupsHndl, const char* _groupName);

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

GroupHandel_t* GroupsHandel_Create()
{
	GroupHandel_t* gHndl;
	gHndl = calloc(1, sizeof(GroupHandel_t) );
	if (!gHndl)
	{
		return NULL;
	}

	gHndl->m_groupContiner = ds_hashmap_create();
	if (! gHndl->m_groupContiner)
	{
		free(gHndl);
		return NULL;
	}

	return gHndl;
}

void GroupsHandel_Destroy(GroupHandel_t* _groupsHndl)
{
	if (! IsStructValid(_groupsHndl))
	{
		return;
	}
	/* TODO */

	_groupsHndl->m_magicNumber = 0;

	ds_hashmap_free(_groupsHndl->m_groupContiner, 1, 1); /* TODO might coause free core */

	return;
}

/* bool */
int GroupsHandel_NewGroup(GroupHandel_t* _groupsHndl, const char* _groupName, uint _socket, sockaddr_in_t* _addrs)
{
	if (! IsStructValid(_groupsHndl))
	{
		return FALSE;
	}

	/* check if exsist */
	if (GroupsHandel_IsGroupExist(_groupsHndl , _groupName) )
	{
		/* username key exsists */
		return FALSE;
	}

	GroupUnit_t* value = CreateValue(_groupName, _addrs, _socket);
	if (!value)
	{
		return FALSE;
	}

	ds_hashmap_put_str(_groupsHndl->m_groupContiner, (char*) _groupName, value);

	return TRUE;

}

/* bool */
int GroupsHandel_JoinGroup(GroupHandel_t* _groupsHndl, const char* _groupName, uint _socket, sockaddr_in_t** _addrsOUT)
{
	GroupUnit_t* aGroup;

	if (! IsStructValid(_groupsHndl))
	{
		return FALSE;
	}

	aGroup = GroupsHandel_FindGroup(_groupsHndl, _groupName);
	if (! aGroup)
	{
		return FALSE;
	}

	if (! AddUser2Group(aGroup, _socket) )
	{
		return FALSE;
	}

	*_addrsOUT = aGroup->m_groupAddrs;

	return TRUE;
}

/* bool */
int GroupsHandel_IsGroupExist(GroupHandel_t* _groupsHndl, const char* _groupName)
{
	if (! IsStructValid(_groupsHndl))
	{
		return FALSE;
	}

	if (NULL == ds_hashmap_get_str( _groupsHndl->m_groupContiner , (char*)_groupName) )
	{
		/* key exsists */
		return FALSE;
	}

	return TRUE;
}


/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool IsStructValid(GroupHandel_t* _groupsHndl)
{
	return !(NULL == _groupsHndl || _groupsHndl->m_magicNumber != MAGIC_NUMBER_GRP_HNDL);
}

static GroupUnit_t* CreateValue(const char* _groupName, struct sockaddr_in* _groupAddrs, uint _socketNum)
{
	GroupUnit_t* group = malloc(1 * sizeof(GroupUnit_t));

	strcpy( group->m_groupName , _groupName);
	group->m_groupAddrs = _groupAddrs;
	group->m_usersSockets[0] = _socketNum;
	group->m_userInGroupNum = 1;

	group->m_magicNumber = MAGIC_NUMBER_GRP_UNT;

	return group;
}

/* TODO use in delete geoup */
static void DestoyValue(GroupUnit_t* _group)
{
	free(_group);

	return;
}

static bool AddUser2Group(GroupUnit_t* _group, uint _socketNum)
{
	++_group->m_userInGroupNum;
	_group->m_usersSockets[_group->m_userInGroupNum] = _socketNum;

	return TRUE;
}

static GroupUnit_t* GroupsHandel_FindGroup(GroupHandel_t* _groupsHndl, const char* _groupName)
{
	if (! IsStructValid(_groupsHndl))
	{
		return FALSE;
	}

	return ds_hashmap_get_str( _groupsHndl->m_groupContiner , (char*)_groupName) ;
}






