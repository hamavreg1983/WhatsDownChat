/*
 * client.c
 *
 *  Created on: Jul 4, 2017
 *      Author: uv
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "Protocol.h"
#include "tcp_client.h"

#define MAX_MSG_SIZE 1024
#define NDBUG /* remove for debug */


int main(int argc, char* argv[])
{
	uint serverPort = 4848;  		/* Default value */
	char serverIP[16] = "127.0.0.1"; /* Default value */
	char msg[MAX_MSG_SIZE];			/* Default value */
	void* buffer[MAX_MSG_SIZE];

	if (argc == 3)
	{
		strcpy(serverIP , argv[1]);
		serverPort = atoi(argv[2]) ;
	}

	printf("--START--\n");
	TCP_C_t* client;
	client = TCP_CreateClient(serverIP, serverPort);
	if (!client)
	{
		printf("\nERROR. coud not connect to server ip %s port %d. \nNothing to do. user should re Run.\n\n", serverIP, serverPort);
		return 1;
	}

	int sent_bytes;
	int recv_bytes;
	while ( TRUE )
	{
		printf("\nType msg to be send (0000 to exit): ");

		fgets(msg, MAX_MSG_SIZE , stdin); 		/* safer. no overflow */
		msg[strcspn(msg, "\n")] = 0; 			/* remove trailing \n */
		sanity_check(msg, MAX_MSG_SIZE, '_'); 	/* remove illegal unsafe char */

		if (! strcmp("0000" , msg)) /* breaking out */
		{
			break;
		}

		char sendMsgProtocol[MAX_MSG_SIZE];
		int length;
		length = Protocol_EncodeSignUp(msg, "pass1WorD", sendMsgProtocol);

		sent_bytes = TCP_ClientSend(client, sendMsgProtocol, length) ;
		printf("\nJust send this msg:%s\n",sendMsgProtocol);
		if (0 > sent_bytes)
		{
			printf("\nError. send %d bytes", sent_bytes);
		}
		else
		{
			recv_bytes = TCP_ClientRecive(client, buffer, MAX_MSG_SIZE);
			if (0 == recv_bytes)
			{
				printf("\n server closed connection. exiting.");
				break;
			}
			printf("recived(%d): %s.\n", recv_bytes, (char*) buffer);

			ClientReceiveMessage_t recivebuf;
			Protocol_DecodeClient(buffer, recv_bytes, &recivebuf);
#ifndef NDBUG
			printf("Msg Type:%d. status:%d\n", recivebuf.m_messageType , recivebuf.m_status);
#endif
		}
	}

	TCP_DestroyClient(client);
	printf("\n--END--\n");
}


