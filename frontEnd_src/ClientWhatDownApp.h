/*
 * ClientWhatDownApp.h
 *
 *  Created on: Jul 16, 2017
 *      Author: uv
 */

#ifndef CLIENTWHATDOWNAPP_H_
#define CLIENTWHATDOWNAPP_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define NDBUG /* remove for debug */

/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct WhatDownClientApp WhatDownClientApp_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

WhatDownClientApp_t* WhatDownClientApp_Create(const char* _serverIP, uint _serverPort);

void WhatDownClientApp_Destroy(WhatDownClientApp_t* _appBE);

bool WhatDownClientApp_Run(WhatDownClientApp_t* _appBE);

bool WhatDownClientApp_Stop(WhatDownClientApp_t* _appBE);


#endif /* CLIENTWHATDOWNAPP_H_ */
