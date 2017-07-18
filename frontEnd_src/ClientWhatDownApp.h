/**
 *  @file ClientWhatDownApp.h
 *
 *  @date Jul 16, 2017
 *  @author Yuval Hamberg
 *
 *  @brief the front file for WhatDown Chat App front end (client side).
 */

#ifndef CLIENTWHATDOWNAPP_H_
#define CLIENTWHATDOWNAPP_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct WhatDownClientApp WhatDownClientApp_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief create and setup the module
 * @param _serverIP the server address to connect to. format of XXX.XXX.XXX.XXX
 * @param _serverPort the server port to connect to.
 * @return a pointer to the module struct
 */
WhatDownClientApp_t* WhatDownClientApp_Create(const char* _serverIP, uint _serverPort);

/**
 * @brief clean up after the processing
 * @param _appBE the pointer to the struct
 */
void WhatDownClientApp_Destroy(WhatDownClientApp_t* _appBE);

/**
 * @brief activate the components of the client. for example the ui.
 * @param _appBE the pointer to the struct
 * @return TRUE for success. FALSE for error return.
 */
bool WhatDownClientApp_Run(WhatDownClientApp_t* _appBE);

/**
 * @brief stops the client run. does not disconnect.
 * @param _appBE the pointer to the struct
 * @return TRUE for success. FALSE for error return.
 */
bool WhatDownClientApp_Stop(WhatDownClientApp_t* _appBE); /** not implamented */


#endif /* CLIENTWHATDOWNAPP_H_ */
