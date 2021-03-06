/*
 * Client_ui.c
 *
 *  @date Jul 13, 2017
 *  @authorpavel
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
static int MenuUser();
int SignupFunction(Client_UI* _ui);
int LoginFunction(Client_UI* _ui);
void LogoutFunction(Client_UI* _ui);
void DisconnectFunction(Client_UI* _ui);
void DeleteUserFunction(Client_UI* _ui);
void CreateNewGroupFunction(Client_UI* _ui);
void JoinGruopFunction(Client_UI* _ui);
void LeaveGroupFunction(Client_UI* _ui);
void GetAllGruopFunction(Client_UI* _ui);
static int MenuLogic(Client_UI* _ui, int _userSelected);

static int GetUserInput(char* _buffer , uint _maxLength);
static bool PrintBackEndResponse(BackEndStatus _statusServer);

/************************************************/
Client_UI* UI_Create(Logic_FE_t* _frontEnd)
{
	Client_UI* newClient;
	if (!_frontEnd)
	{
		return NULL;
	}

	newClient = calloc(1,sizeof(Client_UI));
	if (!newClient)
	{
		return NULL;
	}

	newClient->m_logicFE = _frontEnd;

	return newClient;
}

void Ui_Run(Client_UI* _ui)
{
	int rslt = FALSE;

	system("clear");
	printf("Program start \n ");
	printf("The program is initialized \n");

	printf("\n");
	printf("   _    _      _                             _                       \n");
	printf("  | |  | |    | |                           | |                      \n");
	printf("  | |  | | ___| | ___ ___  _ __ ___   ___   | |_ ___                 \n");
	printf("  | |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\  | __/ _ \\                \n");
	printf("  \\  /\\  /  __/ | (_| (_) | | | | | |  __/  | || (_) |               \n");
	printf("   \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|   \\__\\___/                \n");
	printf("                                                                     \n");
	printf("                                                                     \n");
	printf("   _    _ _           _  ______                     ___              \n");
	printf("  | |  | | |         | | |  _  \\                   / _ \\             \n");
	printf("  | |  | | |__   __ _| |_| | | |_____      ___ __ / /_\\ \\_ __  _ __  \n");
	printf("  | |/\\| | '_ \\ / _` | __| | | / _ \\ \\ /\\ / / '_ \\|  _  | '_ \\| '_ \\ \n");
	printf("  \\  /\\  / | | | (_| | |_| |/ / (_) \\ V  V /| | | | | | | |_) | |_) |\n");
	printf("   \\/  \\/|_| |_|\\__,_|\\__|___/ \\___/ \\_/\\_/ |_| |_\\_| |_/ .__/| .__/ \n");
	printf("                                                        | |   | |    \n");
	printf("                                                        |_|   |_|    \n\n");


	while (rslt == 0)
	{
		rslt = MenuUser();
		if (rslt == 0)
		{
			return;
		}

		rslt = MenuLogic(_ui, rslt);
	}

	while (TRUE)
	{
		rslt = Menu();
		rslt = MenuLogic(_ui, rslt);

		if (rslt == 0)
		{
			return;
		}
	}

	return;
}
/*
TODO ? void Ui_Destroy(Client_Ui);
*/
static int MenuUser()
{
	char choose[2];
	size_t sel = 1;

	do {
		printf("\n Please select option \n");
		printf(" Sign up to server --------------------> 1  \n");
		printf(" Login to server ----------------------> 2  \n");
		printf(" To Exit Press-------------------------> 0  \n");

		GetUserInput(choose, 2);
		sel = atoi(choose);
		system("clear");
	} while (sel < 0 || sel > 2);

	return sel;
}

static int Menu()
{
	char choose[2];
	size_t sel = 1;

	while (TRUE)
	{
		printf("\n Please select option \n");
		printf(" Log out from server ------------------> 3  \n");
		printf(" Disconnect from server ---------------> 4  \n");
		printf(" Delete user --------------------------> 5  \n");
		printf(" Create new group ---------------------> 6  \n");
		printf(" Join to group ------------------------> 7  \n");
		printf(" Leave group --------------------------> 8  \n");
		printf(" Show all groups ----------------------> 9  \n");
		printf(" To Exit Press-------------------------> 0  \n");
		GetUserInput(choose, 2);
		sel = atoi(choose);

		system("clear");
		if (sel != 1 && sel != 2)
		{
			break;
		}
	}

return sel;
}

static int MenuLogic(Client_UI* _ui, int _userSelected)
{
	int res = TRUE; /* set to 1 so would enter the loop */
	system("clear");
	printf("Program start \n ");
	printf("The program is initialized \n");

		switch (_userSelected)
		{
			case 0:
				printf("Exiting The Program\n");
				res = 0;
				break;

			case 1:
				res = SignupFunction(_ui);
				break;

			case 2:
				res = LoginFunction(_ui);
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
	return res;
}

int SignupFunction(Client_UI* _ui)
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

	return (statusServer == BackEnd_SUCCESS) ? TRUE : FALSE;
}

int LoginFunction(Client_UI* _ui)
{
	char userName[MAX_GROUP_NAME]= {0};
	char password[MAX_GROUP_NAME]= {0};
	int result;
	BackEndStatus statusServer;

	system("clear");
	do
	{
		printf("Welcome to login screen for whatsDown Chat app \n");
		do {
			printf("please insert username \n");
			result = GetUserInput(userName, MAX_USERNAME);
		} while ( result <= 0 );

		do {
			printf("please insert password \n");
			result = GetUserInput(password, MAX_PASSWORD);
		} while ( result <= 0  );

	} while(!strlen(userName) || !strlen(password));

	/* tunr to login */
	statusServer = LogicFE_Login(_ui->m_logicFE, userName, password);
	PrintBackEndResponse(statusServer);
	return (statusServer == BackEnd_SUCCESS) ? TRUE : FALSE;
}

void LogoutFunction(Client_UI* _ui)
{
	printf("\nNot implemented.\n");
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

	printf("Create new chat group \n");
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
	char groupName[MAX_GROUP_NAME]= {0};
	int result;
	BackEndStatus statusServer;

	system("clear");

	printf("Join a existing chat group \n");

	/* TODO call show all groups */

	do {
		printf("please insert group's Name \n");
		result = GetUserInput(groupName, MAX_GROUP_NAME);
	} while ( result <= 0 );

	statusServer = LogicFE_JoinGroup(_ui->m_logicFE, groupName);
	PrintBackEndResponse(statusServer);

	return;
}

void LeaveGroupFunction(Client_UI* _ui)
{

}
void GetAllGruopFunction(Client_UI* _ui)
{
	char groupName[1024]= {0};
	uint numOfGroups;
	uint i , k;
	BackEndStatus statusServer;

	system("clear");

	printf("Fetching all groups... \n");

	statusServer = LogicFE_GetAllGroupsName(_ui->m_logicFE, groupName, &numOfGroups, 1024);

	PrintBackEndResponse(statusServer);
	printf("Groups Name \n");

	k = 0;
	for (i = 0; i < numOfGroups; ++i)
	{
		if (groupName[k] != '\0')
		{
			k += printf("\t%s\n", groupName + k);
			k -= 2;
		}
		k++;
	}
	printf("Groups Name Ended\n");

	return;
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


