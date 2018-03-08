// REPLACE THIS FILE WITH YOUR OWN CODE.
// READ ELEV.H FOR INFORMATION ON HOW TO USE THE ELEVATOR FUNCTIONS.

#include "elev.h"
#include "input.h"
#include "logikk.h"
#include "queue.h"
#include <stdio.h>
#include <time.h>


int main()
{
    // Initialize hardware
    if (!elev_init()) {
        printf(__FILE__ ": Unable to initialize elevator hardware\n");
        return 1;
    }  
    while (1) {
	startHeis();
    }
	
	

    return 0;
}

