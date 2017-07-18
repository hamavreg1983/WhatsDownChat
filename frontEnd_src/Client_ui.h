/**
 * @file client_ui.h
 *
 *  @date Jul 13, 2017
 *  @author Yuval Hamberg
 *
 *  @brief Deals with the User interface. part of the client.
 */

#ifndef CLIENT_UI_H_
#define CLIENT_UI_H_

#include "defines.h"


/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct Client_UI Client_UI;
typedef struct Logic_FE Logic_FE_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief create and setup the ui
 * @param _frontEnd a pointer to the FrontEnd-logic. in order to send requsts to.
 * @return a pointer to the new struct
 */
Client_UI* UI_Create(Logic_FE_t* _frontEnd);


/**
 * @brief destroy and clean up after
 * @param the pointer to the struct
 */
void Ui_Destroy(Client_UI* _ui);

/**
 * @brief start the loop of the UI
 * @param _ui the pointer to the struct
 */
void Ui_Run(Client_UI* _ui);

/**
 * @brief stop the loop of the UI. wont happen immediately.
 * @param _ui the pointer to the struct
 */
void Ui_Stop(Client_UI* _ui); /** not implemented */



#endif /* CLIENT_UI_H_ */
