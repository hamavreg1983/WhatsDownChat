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
#include "ClientWhatDownApp.h"

#define MAX_MSG_SIZE 1024



int main(int argc, char* argv[])
{
	int user;
	uint serverPort = 7254;  		/* Default value */
	char serverIP[16] = "192.168.0.17"; /* Default value */
	char msg[MAX_MSG_SIZE];			/* Default value */
	void* buffer[MAX_MSG_SIZE];

	if (argc == 3)
	{
		strcpy(serverIP , argv[1]);
		serverPort = atoi(argv[2]) ;
	}
	else
	{
		printf("\n please select user to conect: \n");
		printf("1 for T is in the house tomer \n");
		printf("2 for the man whit 100 ids guy \n");
		printf("3 for Manager Manager yuval \n");
		printf("4 for pavel  \n");
		scanf("%d",&user);

		switch(user)
		{
		case 1:
		{
			strcpy(serverIP , "192.168.0.37");
			serverPort = 3000 ;
			break;
		}
		case 2:
		{
			strcpy(serverIP , "192.168.0.67");
			serverPort = 7984 ;
			break;

		}
		case 3:
		{
			strcpy(serverIP , "192.168.0.48");
			serverPort = 4848 ;
			break;
		}
		case 4:
			strcpy(serverIP , "192.168.0.17");
			serverPort = 7254 ;
			break;
		}
	}

	WhatDownClientApp_t* appClient = WhatDownClientApp_Create(serverIP, serverPort);
	if (!appClient)
	{
		printf("Error\n");
		return GEN_ERROR;
	}

	WhatDownClientApp_Run(appClient);

	WhatDownClientApp_Destroy(appClient);

	printf("\n--END--\n");
}


