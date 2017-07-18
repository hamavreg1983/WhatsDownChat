/**
 * @file writer.c
 *
 *  @date Jul 18, 2017
 *  @author Yuval Hamberg
 *
 *  @brief joins a multicast group and send messages from stdin to group
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "netUDP_MultiCast.h"
#include "defines.h"

#define MSG_BUF_SIZE 1024

int main(int argc, char *argv[])
{
	char message[MSG_BUF_SIZE] = {0};
	int port;
	int n;
	char ip[16];
	char nickName[64];
	char groupName[64];

	if (argc == 5)
	{
		strcpy(ip, argv[1] );
		port = atoi(argv[2]);
		strcpy(nickName, argv[3]);
		strcpy(groupName, argv[4]);
	}
	else
	{
		strcpy(ip, "225.225.225.225" );
		port = 2255;
		strcpy(nickName, "myUser");
		strcpy(groupName, "unknown");
	}

	printf("Writer group:%s (%s)\n------------------\n(type text and press enter to send. 0000 would exit.\n", groupName, ip);

	UDP_MultiCast_t* net;
	net = UDP_MultiCast_Sender_Create(ip, port);
	if (!net)
	{
		printf("fail to create.\n");
		return 1;
	}

	/* now just sendto() our destination! */
	while (TRUE) {
		n = sprintf(message, KCYN "%s%s" KNRM, nickName, ": ");
		fgets(message + n, MSG_BUF_SIZE - n, stdin);
		message[strcspn(message, "\n")] = 0;

		if (0 == (strcmp( message + n, "0000" ) ) )
		{
			return 0;
		}

		if ( UDP_MultiCast_Send(net, message, strlen(message)+1 ) < 0)
		{
			perror("sendto fail");
			return 1;
		}
	}

	return 0;
}
