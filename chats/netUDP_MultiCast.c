/*
 * netUDP_MultiCast.c
 *
 *  @date Jul 18, 2017
 *  @authoruv
 */

#include "netUDP_MultiCast.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define MAGIC_NUMBER_ALIVE_SENDER 0xfacefedc
#define MAGIC_NUMBER_ALIVE_RECV 0xfaceabcd
/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
struct UDP_MultiCast
{
	uint m_magicNumber;

	struct sockaddr_in* m_sockaddr;
	int m_fd_socket;
};

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

UDP_MultiCast_t* UDP_MultiCast_Sender_Create(const char* _ip, uint _port)
{
	UDP_MultiCast_t* net;

	if (NULL == _ip || _port < 1000)
	{
		return NULL;
	}

	net = malloc(1 * sizeof(UDP_MultiCast_t) );
	if (!net)
	{
		return NULL;
	}

	net->m_sockaddr = malloc(1 * sizeof(struct sockaddr_in) );
	if (!net->m_sockaddr)
	{
		free(net);
		return NULL;
	}

	if ((net->m_fd_socket = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("socket create fail");
		return NULL;
	}

	/* set up destination address */
	memset(net->m_sockaddr,0,sizeof(*(net->m_sockaddr)));
	net->m_sockaddr->sin_family=AF_INET;
	net->m_sockaddr->sin_addr.s_addr=inet_addr(_ip);
	net->m_sockaddr->sin_port=htons(_port);

	net->m_magicNumber = MAGIC_NUMBER_ALIVE_SENDER;

	return net;
}

void UDP_MultiCast_Sender_Destroy(UDP_MultiCast_t* _net)
{
	if(NULL == _net || _net->m_magicNumber != MAGIC_NUMBER_ALIVE_SENDER)
	{
		return;
	}

	_net->m_magicNumber = 0;

	close(_net->m_fd_socket);
	free(_net->m_sockaddr);
	free(_net);
	return;
}


int UDP_MultiCast_Send(UDP_MultiCast_t* _net, void* _msg, uint _msgLength)
{
	int result;
	if(NULL == _net || _net->m_magicNumber != MAGIC_NUMBER_ALIVE_SENDER)
	{
		return GEN_ERROR;
	}

	if ((result = sendto(_net->m_fd_socket, _msg, _msgLength,0,(struct sockaddr *) _net->m_sockaddr, sizeof(*(_net->m_sockaddr)))) < 0)
	{
		perror("sendto fail");
		return GEN_ERROR;
	}

	return result;
}




UDP_MultiCast_t* UDP_MultiCast_Reciver_Create(const char* _ip, uint _port)
{
	UDP_MultiCast_t* net;
	bool yes = TRUE;
	struct ip_mreq mreq;

	if (NULL == _ip || _port < 1000)
	{
		return NULL;
	}

	net = malloc(1 * sizeof(UDP_MultiCast_t) );
	if (!net)
	{
		return NULL;
	}

	net->m_sockaddr = malloc(1 * sizeof(struct sockaddr_in) );
	if (!net->m_sockaddr)
	{
		free(net);
		return NULL;
	}


	/* create what looks like an ordinary UDP socket */
	if (( net->m_fd_socket = socket(AF_INET,SOCK_DGRAM,0)) < 0) {
		perror("socket");
		free(net->m_sockaddr);
		free(net);
		return(NULL);
	}

	/* allow multiple sockets to use the same PORT number */
	if (setsockopt( net->m_fd_socket ,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0)
	{
		perror("Reusing ADDR failed");
		free(net->m_sockaddr);
		free(net);
		return(NULL);
	}

	/* set up destination address */
	memset(net->m_sockaddr ,0,sizeof( *(net->m_sockaddr) ));
	net->m_sockaddr->sin_family = AF_INET;
	net->m_sockaddr->sin_addr.s_addr = inet_addr(_ip);
	net->m_sockaddr->sin_port = htons(_port);

	/* bind to receive address */
	if (bind( net->m_fd_socket ,(struct sockaddr *) net->m_sockaddr ,sizeof( *(net->m_sockaddr) )) < 0)
	{
		perror("bind");
		free(net->m_sockaddr);
		free(net);
		return(NULL);
	}

	/* use setsockopt() to request that the kernel join a multicast group */
	memset( &mreq , 0 , sizeof(struct ip_mreq));
	mreq.imr_multiaddr.s_addr = inet_addr(_ip);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt( net->m_fd_socket ,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)
	{
		perror("setsockopt failed");
		free(net->m_sockaddr);
		free(net);
		return(NULL);
	}

	net->m_magicNumber = MAGIC_NUMBER_ALIVE_RECV;
	return net;

}

void UDP_MultiCast_Reciver_Destroy(UDP_MultiCast_t* _netRecive)
{
	if(NULL == _netRecive || _netRecive->m_magicNumber != MAGIC_NUMBER_ALIVE_RECV)
	{
		return;
	}

	_netRecive->m_magicNumber = 0;

	close(_netRecive->m_fd_socket);
	free(_netRecive->m_sockaddr);
	free(_netRecive);
	return;
}


int UDP_MultiCast_Recive(UDP_MultiCast_t* _netRecive, void* _buffer, size_t _bufferSize)
{
	int addrlen;
	int result;

	if(NULL == _netRecive || _netRecive->m_magicNumber != MAGIC_NUMBER_ALIVE_RECV)
	{
		return GEN_ERROR;
	}

	addrlen = sizeof( *(_netRecive->m_sockaddr) );

	if ( (result = recvfrom( _netRecive->m_fd_socket , _buffer , _bufferSize , 0 , (struct sockaddr *)_netRecive->m_sockaddr ,(uint*) &addrlen) ) < 0 )
	{
		perror("recvfrom fail");
	}

	return result;
}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

