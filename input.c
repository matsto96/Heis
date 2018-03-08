//#include "channels.h"
#include "input.h"



int tabellOpp[N_FLOORS-1];
int tabellNed[N_FLOORS-1];
int tabellInne[N_FLOORS];

heisVar heisData;

void bestillingInne(void){
	int i;
	for(i = 0; i < N_FLOORS; i++){
		if(elev_get_button_signal(BUTTON_COMMAND, i) == 1){
			tabellInne[i] = 1;
		}
	}
}
void bestillingNed(void){
	int i;
	for(i = 0; i < N_FLOORS-1; i++){
		if(elev_get_button_signal(BUTTON_CALL_DOWN, i+1) == 1){
			tabellNed[i] = 1;
		}
	}
}
void bestillingOpp(void){
	int i;
	for(i = 0; i < N_FLOORS-1; i++){
		if(elev_get_button_signal(BUTTON_CALL_UP, i) == 1){
			tabellOpp[i] = 1;
		}
	}
}


		
