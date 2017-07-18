/**
 *  @file whatDownBackEndApp.h
 *
 *  @date Jul 15, 2017
 *  @author Yuval Hamberg
 *
 *  @brief the front file for WhatDown Chat App back end (server side).
 */

#ifndef WHATDOWNBACKENDAPP_H_
#define WHATDOWNBACKENDAPP_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define SERVER_PORT 4848
#define SERVER_IP NULL
#define SERVER_MAX_CONNECTION 1000
#define SERVER_TIMOUT_MS 60000

#define CHAT_FIRSET_IP "225.1.1.1"
#define CHAT_MAX_NUM_IP 100
#define CHAT_PORT 2255

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct WhatDownBackEndApp WhatDownBackEndApp_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief create and setup the app server
 * @return pointer to the struct created
 */
WhatDownBackEndApp_t* WhatDownBackEndApp_Create();

/**
 * @brief cleans up after the app
 * @param _appBE the struct
 */
void WhatDownBackEndApp_Destroy(WhatDownBackEndApp_t* _appBE);

/**
 * @brief activate the server and start waiting for request. run a infinite loop until stop is called.
 * @param _appBE the struct
 * @return TRUE when asked to stop and return. FALSE when returned out of error.
 */
bool WhatDownBackEndApp_Run(WhatDownBackEndApp_t* _appBE);

/**
 * @brief ask to stop the server. there might be a delay between request to full stop/
 * @param _appBE the struct
 * @return TRUE when asked to stop and return. FALSE when returned out of error.
 */
bool WhatDownBackEndApp_Stop(WhatDownBackEndApp_t* _appBE);




#endif /* WHATDOWNBACKENDAPP_H_ */
