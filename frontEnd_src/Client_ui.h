/*
 * client_ui.h
 *
 *  Created on: Jul 13, 2017
 *      Author: pavel
 */

#ifndef CLIENT_UI_H_
#define CLIENT_UI_H_

#include "defines.h"

typedef struct Client_UI Client_UI;
typedef struct Logic_FE Logic_FE_t;

Client_UI* UI_Create(Logic_FE_t* _frontEnd);

void Ui_Run(Client_UI* _ui);

void Ui_Destroy(Client_UI);

#endif /* CLIENT_UI_H_ */
