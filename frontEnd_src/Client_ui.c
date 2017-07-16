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
#include "Protocol.h"
#include "defines.h"

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

static int GetUserInput(char* _buffer , uint _maxLength);
static bool PrintBackEndResponse(BackEndStatus _statusServer);

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
	int res = TRUE; /* set to 1 so would enter the loop */
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
	char choose[2];
	size_t sel = 1;
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
	GetUserInput(choose, 2);
	sel = atoi(choose);
	system("clear");

return sel;
}

void SignupFunction(Client_UI* _ui)
{
	char userName[MAX_GROUP_NAME]= {0};
	char password[MAX_GROUP_NAME]= {0};
	int result;
	BackEndStatus statusServer;

	system("clear");
	do
	{
		printf("Welcome to sign up to whatsDown Chat app \n");
		do {
			printf("please insert username \n");
			result = GetUserInput(userName, MAX_USERNAME);
		} while ( result <= 0 );

		do {
			printf("please insert password \n");
			result = GetUserInput(password, MAX_PASSWORD);
		} while ( result <= 0  );

	} while(!strlen(userName) || !strlen(password));

	statusServer = LogicFE_Signup(_ui->m_logicFE, userName, password);
	PrintBackEndResponse(statusServer);

	return;
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
	char groupName[MAX_GROUP_NAME]= {0};
	int result;
	BackEndStatus statusServer;

	system("clear");

	printf("Welcome to sign up to whatsDown Chat app \n");
	do {
		printf("please insert new Group's Name \n");
		result = GetUserInput(groupName, MAX_GROUP_NAME);
	} while ( result <= 0 );

	statusServer = LogicFE_CreateGroup(_ui->m_logicFE, groupName);
	PrintBackEndResponse(statusServer);

	return;
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

static int GetUserInput(char* _buffer , uint _maxLength)
{
	if (!_buffer)
	{
		return 0;
	}

	do {
		fgets(_buffer, _maxLength , stdin); 		/* safer. no overflow */
	} while (_buffer[0] == '\0');

	_buffer[strcspn(_buffer, "\n")] = 0; 		/* remove trailing \n */
	sanity_check(_buffer, _maxLength, '_'); 	/* remove illegal unsafe char */

	return strlen(_buffer);
}

static bool PrintBackEndResponse(BackEndStatus _statusServer)
{
	switch (_statusServer) {
		case BackEnd_SUCCESS:
			printf("Success!\n");
			break;
		case BackEnd_SYSTEM_FAIL:
			printf("SYSTEM_FAIL!\n");
			break;
		case BackEnd_UNKNOWN_ERROR:
			printf("UNKNOWN_ERROR!\n");
			break;
		case BackEnd_USER_NAME_TAKEN:
			printf("USER_NAME_TAKEN!\n");
			break;
		case BackEnd_USER_NAME_INVALID:
			printf("USER_NAME_INVALID!\n");
			break;
		case BackEnd_USER_NOT_FOUND:
			printf("USER_NOT_FOUND!\n");
			break;
		case BackEnd_PASSWORD_INVALID:
			printf("PASSWORD_INVALID!\n");
			break;
		case BackEnd_GROUP_NAME_TAKEN:
			printf("GROUP_NAME_TAKEN!\n");
			break;
		case BackEnd_GROUP_NAME_INVALID:
			printf("GROUP_NAME_INVALID!\n");
			break;
		case BackEnd_GROUP_DO_NOT_EXIST:
			printf("GROUP_DO_NOT_EXIST!\n");
			break;
		case BackEnd_MORE_INFO_INCOMING:
			printf("MORE_INFO_INCOMING!\n");
			break;
		case BackEnd_NO_FREE_IP:
			printf("NO_FREE_IP!\n");
			break;
		case BackEnd_CLIENT_DISCONNECTED:
			printf("CLIENT_DISCONNECTED!\n");
			break;
		case BackEnd_REQUST_UNKNOWN:
			printf("REQUST_UNKNOWN!\n");
			break;
		default:
			printf("UNKNOWN RESPONDS! (%d)\n", _statusServer);
			return FALSE;
			break;
	}
	return TRUE;
}


