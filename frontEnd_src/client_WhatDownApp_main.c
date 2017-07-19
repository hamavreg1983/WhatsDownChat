/**
 *  @file client_WhatDown_main.c
 *
 *  @date Jul 4, 2017
 *  @author Yuval Hamberg
 *
 *  @brief user call for whatDown chat app. mostly getting to connect to the right server.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "ClientWhatDownApp.h"

#define MAX_MSG_SIZE 1024
#define IP_LENGTH 16
#define PORT_LENGTH 6

static int GetUserInput(char* _buffer , uint _maxLength);

int main(int argc, char* argv[])
{
	int user;
	uint serverPort = 0;
	char serverIP[IP_LENGTH] = { 0 };
	char portString[PORT_LENGTH] = { 0 };
	WhatDownClientApp_t* appClient;

	if (argc == 3)
	{
		strcpy(serverIP , argv[1]);
		serverPort = atoi(argv[2]) ;
	}
	else
	{
		printf("\n please select user to conect: \n");
		printf("0 Exit \n");
		printf("1 Tomer \n");
		printf("2 Guy \n");
		printf("3 Yuval \n");
		printf("4 Pavel  \n");
		printf("5 loopBack  \n");
		printf("9 type an address  \n");
		scanf("%d",&user);

			switch(user)
			{
			case 0:
				return(0);
				break;
			case 1:
				strcpy(serverIP , "192.168.0.37");
				serverPort = 3000 ;
				break;
			case 2:
				strcpy(serverIP , "192.168.0.67");
				serverPort = 7984 ;
				break;

			case 3:
				strcpy(serverIP , "192.168.0.48");
				serverPort = 4848 ;
				break;
			case 4:
				strcpy(serverIP , "192.168.0.17");
				serverPort = 7254 ;
				break;
			case 5:
				strcpy(serverIP , "127.0.0.1");
				serverPort = 4848 ;
				break;
			case 9:
				printf("Type IP: ");
				GetUserInput(serverIP , IP_LENGTH);
				printf("Type port: ");
				GetUserInput(portString , PORT_LENGTH);
				serverPort = atoi(portString) ;
				break;
			default:
				printf("wrong choose");
				exit(1);
				break;
			}
	}

	appClient = WhatDownClientApp_Create(serverIP, serverPort);
	if (!appClient)
	{
		printf("Error\n");
		return GEN_ERROR;
	}

	WhatDownClientApp_Run(appClient);

	WhatDownClientApp_Destroy(appClient);

	printf("\n--END--\n");
	return 0;
}


static int GetUserInput(char* _buffer , uint _maxLength)
{
	if (!_buffer)
	{
		return 0;
	}

	do {
		fgets(_buffer, _maxLength , stdin); 		/* safer. no overflow */
		_buffer[strcspn(_buffer, "\n")] = 0; 		/* remove trailing \n */
	} while (_buffer[0] == '\0');

	sanity_check(_buffer, _maxLength, '_'); 		/* remove illegal unsafe char */

	return strlen(_buffer);
}
