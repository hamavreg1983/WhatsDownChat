/*
 * whatDownBackEndApp.h
 *
 *  Created on: Jul 15, 2017
 *      Author: yuval
 */

#ifndef WHATDOWNBACKENDAPP_H_
#define WHATDOWNBACKENDAPP_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define SERVER_PORT 4848
#define SERVER_IP NULL
#define SERVER_MAX_CONNECTION 1000
#define SERVER_TIMOUT_MS 60000

<<<<<<< HEAD
#define CHAT_FIRSET_IP "225.1.1.1"
#define CHAT_MAX_NUM_IP 100
#define CHAT_PORT 2255

=======
>>>>>>> refs/remotes/origin/master
/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct WhatDownBackEndApp WhatDownBackEndApp_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

WhatDownBackEndApp_t* WhatDownBackEndApp_Create();

void WhatDownBackEndApp_Destroy(WhatDownBackEndApp_t* _appBE);

bool WhatDownBackEndApp_Run(WhatDownBackEndApp_t* _appBE);

bool WhatDownBackEndApp_Stop(WhatDownBackEndApp_t* _appBE);




#endif /* WHATDOWNBACKENDAPP_H_ */
