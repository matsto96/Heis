#include "elev.h"
#include "input.h"

#include <stdlib.h>

void lysInne(void){
	bestillingInne();
	int i;
	for(i = 0; i < N_FLOORS; i++){
		if(inneTabell[i] == 1){
			elev_set_button_lamp(BUTTON_COMMAND, i, 1);
		}
		else{
			elev_set_button_lamp(BUTTON_COMMAND, i, 0);
		}
	}
}
void etasjelysUteNed(void){
	bestillingUteNed();
	int i;
	for(i = 0; i < N_FLOORS-1; i++){
		if(uteNedTabell[i] == 1){
			elev_set_button_lamp(BUTTON_CALL_DOWN, i+1, 1);
		}
		else{
			elev_set_button_lamp(BUTTON_CALL_DOWN, i+1, 0);
		}
	}
}
void etasjelysUteOpp(void){
	bestillingUteOpp();
	int i;
	for(i = 0; i < N_FLOORS-1; i++){
		if(uteOppTabell[i] == 1){
			elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
		}
		else{
			elev_set_button_lamp(BUTTON_CALL_UP, i, 0);
		}
	}
}
void etasjeIndikatorUte(void){
	int etasje = elev_get_floor_sensor_signal();
	if(etasje >= 0 && etasje < N_FLOORS){
		elev_set_floor_indicator(etasje);
		heisData.forrigeEtasje = etasje;
	}
}
void stoppLys(int lys){
	elev_set_stop_lamp(lys);
}

