/*
 * ipHandle.c
 *
 *  Created on: Jul 16, 2017
 *      Author: yuval
 */

#include <netinet/in.h> /* struct sockadd */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ipHandle.h"
#include "queue.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define MAGIC_NUMBER_ALIVE_IP_HANDLE 0xeeccface

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
struct IP_Handle
{
	uint m_magicNumber;

	struct DSQueue* m_ipContiner;
};

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */
static bool IsStructValid(IP_Handle_t* _ipHndl);

static bool CreateAddrsAndQue(struct DSQueue* _ipContiner , const char* _firstIP, uint _numOfAdrs, uint _port);
static sockaddr_in_t* CreateAddrs(uint32_t _ip, uint _port);

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

IP_Handle_t* IP_Handle_Create(const char* _firestIP, uint _maxNumOfIPs, uint _portNum)
{
	IP_Handle_t* ipHndl;

	if (NULL == _firestIP || 0 == _maxNumOfIPs)
	{
		return NULL;
	}

	ipHndl = calloc(1, sizeof(IP_Handle_t) );
	if (!ipHndl)
	{
		return NULL;
	}

	ipHndl->m_ipContiner = ds_queue_create(_maxNumOfIPs);
	if (! ipHndl->m_ipContiner)
	{
		free(ipHndl);
		return NULL;
	}

	/* pouplate the queue with free addresses */
	CreateAddrsAndQue(ipHndl->m_ipContiner , _firestIP, _maxNumOfIPs, _portNum);

	ipHndl->m_magicNumber = MAGIC_NUMBER_ALIVE_IP_HANDLE;
	return ipHndl;
}

void IP_Handle_Destory(IP_Handle_t* _ipHndl)
{
	sockaddr_in_t* addr;

	if (!IsStructValid(_ipHndl) )
	{
		return;
	}

	_ipHndl->m_magicNumber = 0;

	ds_queue_free(_ipHndl->m_ipContiner);

	/* free all addresses */
	while (0 != ds_queue_length(_ipHndl->m_ipContiner))
	{
		addr = ds_queue_get(_ipHndl->m_ipContiner);
		free(addr);
	}
	/* TODO we do not free the struct that are not free. just the one in the que! */

	free(_ipHndl);
	return;
}

sockaddr_in_t* IP_Handle_GetFreeIP(IP_Handle_t* _ipHndl)
{
	if (!IsStructValid(_ipHndl) )
	{
		return NULL;
	}

	/* queue is empty, but do not block on it */
	if (0 == ds_queue_length(_ipHndl->m_ipContiner))
	{
		return NULL;
	}

	return ds_queue_get(_ipHndl->m_ipContiner);
}

bool IP_Handle_Release(IP_Handle_t* _ipHndl, sockaddr_in_t* _addressToRelease)
{
	if (!IsStructValid(_ipHndl) )
	{
		return FALSE;
	}

	/* check if queue is full. should never happen. */
	if (ds_queue_length(_ipHndl->m_ipContiner) == ds_queue_capacity(_ipHndl->m_ipContiner) )
	{
		return FALSE;
	}

	ds_queue_put(_ipHndl->m_ipContiner, _addressToRelease);

	return TRUE;
}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool IsStructValid(IP_Handle_t* _ipHndl)
{
	return ! (NULL == _ipHndl || _ipHndl->m_magicNumber != MAGIC_NUMBER_ALIVE_IP_HANDLE);
}


static bool CreateAddrsAndQue(struct DSQueue* _ipContiner , const char* _firstIP, uint _numOfAdrs, uint _port)
{
	uint i;
	uint32_t ip;
	sockaddr_in_t* addr;
	ip = inet_addr(_firstIP);

	for (i = 0 ; i < _numOfAdrs ; ++i)
	{
		if (NULL == (addr = CreateAddrs( (ip), _port) ) )
		{
			return FALSE;
		}

		ds_queue_put(_ipContiner, addr);

		ip += 256 * 256 * 256; /* this caouses the last address to increse by one.  */
		if ((i % 255) == 0) /* buggy */
		{
			ip -= 256 * 256;
		}
	}


	return TRUE;
}


static sockaddr_in_t* CreateAddrs(uint32_t _ip, uint _port)
{
	sockaddr_in_t* addrs;
	if(!_ip)
	{
		return NULL;
	}

	addrs = calloc(1, sizeof(struct sockaddr_in) );
	if (!addrs)
	{
		return NULL;
	}

	addrs->sin_family = AF_INET;
	addrs->sin_addr.s_addr = _ip;
	addrs->sin_port = htons(_port);

	return addrs;
}





