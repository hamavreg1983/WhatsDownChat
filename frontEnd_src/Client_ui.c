/*
 * Client_ui.c
 *
 *  Created on: Jul 13, 2017
 *      Author: pavel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Client_ui.h"
#include "logicFE.h"
#define IP "127.0.0.1"
#define PORT 4848

struct Client_UI
{
	Logic_FE_t* m_logicFE;
};

/*********************************************/
static int Menu();
void SignupFunction(Client_UI* _ui);
void LoginFunction(Client_UI* _ui);
void LogoutFunction(Client_UI* _ui);
void DisconnectFunction(Client_UI* _ui);
void DeleteUserFunction(Client_UI* _ui);
void CreateNewGroupFunction(Client_UI* _ui);
void JoinGruopFunction(Client_UI* _ui);
void LeaveGroupFunction(Client_UI* _ui);
void GetAllGruopFunction(Client_UI* _ui);

/************************************************/
Client_UI* UI_Create(Logic_FE_t* _frontEnd)
{

	if (!_frontEnd)
	{
		return NULL;
	}

	Client_UI* newClient = calloc(1,sizeof(Client_UI));
	/* TODO test malloc passed */

	newClient->m_logicFE = _frontEnd;

	return newClient;
}

void Ui_Run(Client_UI* _ui)
{
	int res;
	    system("clear");
	    printf("Program start \n ");
	    printf("The program is initialized \n");
	while(res)
	{

		res = Menu();
		switch (res)
		{
	        case 0:
	                printf("Exiting The Program\n");
	                break;
	        case 1:
	        		SignupFunction(_ui);
	                break;
	        case 2:
					LoginFunction(_ui);
					break;
	        case 3:
	        		LogoutFunction(_ui);
	        		break;
	        case 4:
	        		DisconnectFunction(_ui);
	        		break;
	        case 5:
	        		DeleteUserFunction(_ui);
	        		break;
	        case 6:
	        		CreateNewGroupFunction(_ui);
	        		break;
	        case 7:
	        		JoinGruopFunction(_ui);
	        		break;
	        case 8:
	        		LeaveGroupFunction(_ui);
	        		break;
	        case 9:
	        		GetAllGruopFunction(_ui);
					break;
	        default:
	                    printf("Wrong Selection Please Select Again\n");
	                    system("clear");
	                    break;
		}
	}

}
/*
void Ui_Destroy(Client_Ui);
*/

static int Menu()
{
	size_t sel =1;
	printf("\n Please select option \n");
	printf("\n Sign up to server --------------------> 1  \n");
	printf("\n Login to server ----------------------> 2  \n");
	printf("\n Log out from server ------------------> 3  \n");
	printf("\n Disconnect from server ---------------> 4  \n");
	printf("\n Delete user --------------------------> 5  \n");
	printf("\n Create new group ---------------------> 6  \n");
	printf("\n Join to group ------------------------> 7  \n");
	printf("\n Leave group --------------------------> 8  \n");
	printf("\n Get all groups -----------------------> 9  \n");
	printf("\n To Exit Press-------------------------> 0  \n");
	scanf("%u",&sel);
	system("clear");

return sel;
}

void SignupFunction(Client_UI* _ui)
{
	char userName[15]= {0}; /* TODO change hardcoded numer */
	char password[15]={0};
	system("clear");
	do
	{
		printf("Welcome to sign up to whatsDown Chat app \n ");
		printf("please insert user name \n");
		scanf("%s",userName);
		printf("please insert password \n");
		scanf("%s",password);
		if(!strlen(userName) || !strlen(password))
		{
			printf("one of the arguments wrong \n");
		}
	}while(!strlen(userName) || !strlen(password));


}
void LoginFunction(Client_UI* _ui)
{

}
void LogoutFunction(Client_UI* _ui)
{

}
void DisconnectFunction(Client_UI* _ui)
{

}
void DeleteUserFunction(Client_UI* _ui)
{

}
void CreateNewGroupFunction(Client_UI* _ui)
{

}
void JoinGruopFunction(Client_UI* _ui)
{

}
void LeaveGroupFunction(Client_UI* _ui)
{

}
void GetAllGruopFunction(Client_UI* _ui)
{

}
