/*
 ============================================================================
 Name        : whatdownApp.c
 Author      : Yuval Hamberg
 Version     :
 Copyright   : MIT
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* write */
#include "defines.h"
#include "Protocol.h"
#include "tcp.h"

#include "IOcomm.h"

#define MAX_CONNECTIONS_ALLWAED 1000

int main(int argc, char* argv[])
{
	puts("!!!TCP!!!"); /* prints !!!TCP!!! */


//	static char userName[MAX_USERNAME] = "yuvalH";
//	static char password[MAX_PASSWORD] = "mySpassword";
//
//	char buffer[MAX_MESSAGE_LENGTH];
//	int result;
//
//	result = Protocol_EncodeSignUp(userName, password, buffer);
//
//	printf("buffer(%d)\n", result);
//	write(1 , buffer , result);

	printf("\nstart Server\n\n");

	uint portNum = 4848;
	TCP_S_t* server;
	uint timeoutMS = 300000; /* 5 min */
	server = TCP_CreateServer(portNum, NULL, MAX_CONNECTIONS_ALLWAED, timeoutMS, IO_CommServerRecive, NULL, NULL, NULL);

	TCP_RunServer(server);


//	ServerReceiveMessage_t* message;
//	message = malloc (sizeof(ServerReceiveMessage_t));

//	int msgLength;
//	msgLength = Protocol_DecodeServer(buffer, result, message);
//
//	printf("\nmsg result %d\n", msgLength);
//	printf("type: %d\n", message->m_MessageType);
//	printf("user: %s\n", message->m_userName);
//	printf("pass: %s\n", message->m_password);

//	scanf



	return EXIT_SUCCESS;
}


