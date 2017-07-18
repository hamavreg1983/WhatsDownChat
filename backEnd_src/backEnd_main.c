/**
 *  @file backEnd_main.c
 *
 *  @date Jul 4, 2017
 *  @author Yuval Hamberg
 *  @copyright MIT
 *
 *  @brief user call for whatDown chat app. server (back end) side.
 */

#include "defines.h"
#include "whatDownBackEndApp.h"

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

	/* WhatDownBackEndApp_Stop(chatApp); */
	WhatDownBackEndApp_Destroy(chatApp);

	printf("\n---END---\n");

	return EXIT_SUCCESS;
}


