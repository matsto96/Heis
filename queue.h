#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

#include "channels.h"
#include "elev.h"
#include "logikk.h"
#include "input.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum tilstand_type { 
	    IDLE = 0, 
	    AAPNE_DOER = 1, 
	    HEIS_OPP = 2,
	    HEIS_NED = 3,
	    STOPP = 4,
	    OBSTRUKSJON = 5
	} logikk_tilstand_type;

logikk_tilstand_type nesteTilstandGittHeisOpp(int etasje);
logikk_tilstand_type nesteTilstandGittHeisNed(int etasje);
logikk_tilstand_type nesteTilstandGittIdle(int etasje);
logikk_tilstand_type nesteTilstandGittAapneDoer(int etasje, retning forrigeTilstand);
void brems(retning forrigeTilstand);


#endif
