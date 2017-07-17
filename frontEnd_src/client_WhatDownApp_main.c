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
	uint serverPort = 4848;  		/* Default value */
	char serverIP[16] = "127.0.0.1"; /* Default value */
	char msg[MAX_MSG_SIZE];			/* Default value */
	void* buffer[MAX_MSG_SIZE];

	if (argc == 3)
	{
		strcpy(serverIP , argv[1]);
		serverPort = atoi(argv[2]) ;
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


