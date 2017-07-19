/*
 * usersHandle.h
 *
 *  @dateJul 15, 2017
 *  @authoryuval
 */

#ifndef USERSHANDLE_H_
#define USERSHANDLE_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct UsersHandle UsersHandle_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief create and setup
 * @return a pointer to the struct
 */
UsersHandle_t* UsersHandle_Create();

/**
 * @brief cleanup after the processing
 * @param _usersHandel the pointer to the struct
 */
void UsersHandle_Destroy(UsersHandle_t* _usersHandel);

/**
 * @brief add a user to the the DS.
 * @param _usersHandel  the pointer to the struct
 * @param _userName the new user username.
 * @param _password the new user password.
 * @param _nickname the new user display name in chats. NOT IMPLEMENTED
 * @param _premission the level of premission the user has. which group can he join.  NOT IMPLEMENTED
 * @param _socketNum the identifier of the user for this session.
 * @return TRUE for success. FALSE for fail. might fail if username taken, null inputs and more.
 */
int UsersHandle_AddNewUser(UsersHandle_t* _usersHandel, char* _userName, char* _password, char* _nickname, uint _premission, int _socketNum);

/**
 * @brief remove the recorde of a user from the ds
 * @param _usersHandel the pointer to the struct
 * @param _userName the user username identifier.
 * @return TRUE for success. FALSE for fail. might fail if username taken, null inputs and more.
 */
bool UsersHandle_RemoveUser(UsersHandle_t* _usersHandel, char* _userName);

/**
 * @brief how many users in ds. NOT IMPLEMENTED
 * @param _usersHandel the pointer to the struct
 * @return the number of users. negative values for errors.
 */
int UsersHandle_CountUsers(UsersHandle_t* _usersHandel);

/**
 * @brief checks if the user already exist
 * @param _usersHandel the pointer to the struct
 * @param _userName the user username identifier.
 * @return bool answer. error return FALSE
 */
bool UsersHandle_IsUserExist(UsersHandle_t* _usersHandel, char* _userName);

/**
 * @brief check if for a certain user, this is the password. used for login.
 * @param _usersHandel the pointer to the struct
 * @param _userName the user username identifier.
 * @param _password the password to check against
 * @return bool answer. error return FALSE
 */
bool UsersHandle_IsUserPasswordMatch(UsersHandle_t* _usersHandel, const char* _userName, const char* _password);


#endif /* USERSHANDLE_H_ */
