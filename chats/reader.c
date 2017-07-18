/*
 * listener.c -- joins a multicast group and echoes all data it receives from
 *		the group to its stdout...
 *
 * Antony Courtney,	25/11/94
 * Modified by: Frédéric Bastien (25/03/04)
 * to compile without warning and work correctly
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "netUDP_MultiCast.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define MSG_BUF_SIZE 1024
#define MAX_GROUP_NAME 64
#define GO_UP_LINE_TERMINAL "\033[1A"

/* ~~~ Internal function forward declartion ~~~~~~~~~~~~~~~~~ */
static void PrintMsg(const char* _msg);


int main(int argc, char *argv[])
{
	int nbytes;
	int port;
	char ip[16];
	char groupName[MAX_GROUP_NAME];
	char msgbuf[MSG_BUF_SIZE];

	if (argc == 4)
	{
		strcpy(ip, argv[1] );
		port = atoi(argv[2]);
		strncpy(groupName, argv[3] , MAX_GROUP_NAME);
	}
	else
	{
		strcpy(ip, "225.225.225.225" );
		port = 2255;
		strncpy(groupName, "Unknown" , MAX_GROUP_NAME);
	}

	UDP_MultiCast_t* readerClient;
	readerClient = UDP_MultiCast_Reciver_Create(ip, port);
	if (!readerClient)
	{
		printf("allocation fail\n");
		return 5;
	}

	/* now just enter a read-print loop */
	printf("reader group:%s (%s)\n-----------------------------------------\n\n",groupName, ip);
	while (TRUE)
	{
		if ((nbytes = UDP_MultiCast_Recive( readerClient, msgbuf, MSG_BUF_SIZE) ) < 0)
		{
			printf("Fail to read incoming msg.\n");
		}
		else
		{
			PrintMsg(msgbuf);
		}
	}
	return 0;
}

/* ~~~ Internal function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void PrintMsg(const char* _msg)
{
	int i;

	printf("%s", GO_UP_LINE_TERMINAL);
	for (i = 0; i < strlen(_msg) - 5 ; ++i)
		{
			putchar('-');
		}
		putchar('\n');

	printf( "| %s |\n" , _msg);

	for (i = 0; i < strlen(_msg) - 5 ; ++i)
	{
		putchar('-');
	}
	putchar('\n');

	return;
}




