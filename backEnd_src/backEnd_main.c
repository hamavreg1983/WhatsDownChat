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
#include "whatDownBackEndApp.h"
//#include "Protocol.h"
//#include "tcp.h"



int main(int argc, char* argv[])
{

	printf("\nstart Server\n\n");


	WhatDownBackEndApp_t* chatApp;
	chatApp = WhatDownBackEndApp_Create();
	if (!chatApp)
	{
		return GEN_ERROR;
	}

	WhatDownBackEndApp_Run(chatApp);

	printf("\n---END---\n");

	return EXIT_SUCCESS;
}


