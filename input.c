//#include "channels.h"
#include "input.h"



int etasjeUteNedTabell[N_FLOORS-1];
int etasjeUteOppTabell[N_FLOORS-1];
int etasjeInneTabell[N_FLOORS];

heisVar heisData;

void etasjeBestillingInne(void){
	int i;
	for(i = 0; i < N_FLOORS; i++){
		if(elev_get_button_signal(BUTTON_COMMAND, i) == 1){
			etasjeInneTabell[i] = 1;
		}
	}
}
void etasjeBestillingUteNed(void){
	int i;
	for(i = 0; i < N_FLOORS-1; i++){
		if(elev_get_button_signal(BUTTON_CALL_DOWN, i+1) == 1){
			etasjeUteNedTabell[i] = 1;
		}
	}
}
void etasjeBestillingUteOpp(void){
	int i;
	for(i = 0; i < N_FLOORS-1; i++){
		if(elev_get_button_signal(BUTTON_CALL_UP, i) == 1){
			etasjeUteOppTabell[i] = 1;
		}
	}
}


		
