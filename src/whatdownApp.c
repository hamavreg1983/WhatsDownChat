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



int main(int argc, char* argv[])
{
	puts("!!!TCP!!!"); /* prints !!!TCP!!! */


	static char userName[MAX_USERNAME] = "yuvalH";
	static char password[MAX_PASSWORD] = "mySpassword";

	char buffer[MAX_MESSAGE_LENGTH];
	int result;

	result = Protocol_EncodeSignUp(userName, password, buffer);

	printf("buffer(%d)\n", result);
	write(1 , buffer , result);


	ServerReceiveMessage_t* message;
	message = malloc (sizeof(ServerReceiveMessage_t));

	int msgLength;
	msgLength = Protocol_DecodeServer(buffer, result, message);

	printf("\nmsg result %d\n", msgLength);
	printf("type: %d\n", message->m_MessageType);
	printf("user: %s\n", message->m_userName);
	printf("pass: %s\n", message->m_password);

//	scanf



	return EXIT_SUCCESS;
}
