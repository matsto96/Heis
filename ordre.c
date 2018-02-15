#include "ordre.h"
int i;
int a;
	logikk_tilstand_type nesteTilstand;



logikk_tilstand_type returnereNesteTilstandGittOrdreOgIdle(int etasje){
		for(i = 0; i < etasje; i++){
			if(etasjeInneTabell[i] == 1 || etasjeUteOppTabell[i] == 1){
				return nesteTilstand = HEIS_NED;
			}
		}
		for(i = 0; i < (etasje-1); i++){
			if(etasjeUteNedTabell[i] == 1){
				return nesteTilstand = HEIS_NED;
			}
		}
		for(i = N_FLOORS-1; i > etasje; i--){
			if(etasjeInneTabell[i] == 1){
				return nesteTilstand = HEIS_OPP;
			}
		}
		for(i = N_FLOORS-2; i >= etasje; i--){
			if(etasjeUteNedTabell[i] == 1){
				return nesteTilstand = HEIS_OPP;
			}
		}
		for(i = N_FLOORS-2; i > etasje; i--){
			if(etasjeUteOppTabell[i] == 1){
				return nesteTilstand = HEIS_OPP;
			}
		}
		if(etasjeInneTabell[etasje] || etasjeUteNedTabell[etasje-1] ||etasjeUteOppTabell[etasje]){
			return nesteTilstand = AAPNE_DOER;
		}
	return IDLE;
}

logikk_tilstand_type returnereNesteTilstandGittOrdreOgHeisOpp(int etasje){

	for(i = etasje; i <= N_FLOORS-1; i++){
		if(etasjeInneTabell[i] || etasjeUteOppTabell[i]) {
			if(etasje==i){
				brems(BEVEG_OPP);
				return nesteTilstand=AAPNE_DOER;
			}
			else{
				return nesteTilstand=HEIS_OPP;
			}
		}
	}
	for(i = N_FLOORS-2; i+1 >= etasje; i--){
		if(etasjeUteNedTabell[i]){
			if(i+1==etasje){
				brems(BEVEG_OPP);
				return nesteTilstand=AAPNE_DOER;
			}
			else{
				return nesteTilstand=HEIS_OPP;
			}
		}
	}
	return HEIS_OPP;
}	
logikk_tilstand_type returnereNesteTilstandGittOrdreOgHeisNed(int etasje){
	for(i = etasje; i >= 0; i--){
		if(etasjeInneTabell[i] || etasjeUteNedTabell[i-1]) {
			if(i==etasje){
				brems(BEVEG_NED);
				return nesteTilstand=AAPNE_DOER;
			}
			else{
				return nesteTilstand=HEIS_NED;
			}
		}
	}
	for(i = 0; i <= etasje; i++){
		if(etasjeUteOppTabell[i]){
			if(i==etasje){
				brems(BEVEG_NED);
				return nesteTilstand=AAPNE_DOER;
			}
			else{
				return nesteTilstand=HEIS_NED;
			}
		}
	}
	return HEIS_NED;
}
logikk_tilstand_type returnereNesteTilstandGittOrdreOgAapneDoer(int etasje, retning forrigeTilstand){
	switch(forrigeTilstand){
		case IRO: 
			for(i = 0; i < N_FLOORS; i++){
				if(etasjeInneTabell[i] == 1){
					if(i < etasje){
						return nesteTilstand=HEIS_NED;
					}
					else if(i > etasje){
						return nesteTilstand=HEIS_OPP;
					}
					else{
						return nesteTilstand = AAPNE_DOER;
					}
				}
			}
		break;
		case BEVEG_OPP: 
			for(i = N_FLOORS-1; i > etasje; i--){
				if(etasjeInneTabell[i] == 1){
					return nesteTilstand=HEIS_OPP;
				}
			}
			for(i = N_FLOORS-2; i > etasje; i--){
				if(etasjeUteOppTabell[i] == 1){
					return nesteTilstand=HEIS_OPP;
				}
			}
			for(i = N_FLOORS-2; i >= 0; i--){
				if(etasjeUteNedTabell[i] == 1){
					if(i > etasje-1){
						return nesteTilstand=HEIS_OPP;
					}
					else if(i < etasje-1){
						return nesteTilstand=HEIS_NED;
					}
				}
			}
			for(i = 0; i < etasje; i++){
				if(etasjeInneTabell[i] == 1){
					return nesteTilstand=HEIS_NED;
				}
			}
			for(i = 0; i < etasje; i++){
				if(etasjeUteOppTabell[i] == 1){
					return nesteTilstand=HEIS_NED;
				}
			}
		break;
		case BEVEG_NED: 
			for(i = 0; i < etasje; i++){
				if(etasjeInneTabell[i] == 1){
					return nesteTilstand=HEIS_NED;
				}
			}
			for(i = 0; i < etasje-1; i++){
				if(etasjeUteNedTabell[i] == 1){
					return nesteTilstand=HEIS_NED;
				}
			}
			for(i = 0; i < N_FLOORS-1; i++){
				if(etasjeUteOppTabell[i] == 1){
					if(i < etasje){
						return nesteTilstand=HEIS_NED;
					}
					else if(i > etasje){
						return nesteTilstand=HEIS_OPP;
					}
				}
			}
			for(i = N_FLOORS-1; i > etasje; i--){
				if(etasjeInneTabell[i] == 1){
					return nesteTilstand=HEIS_OPP;
				}
			}
			for(i = N_FLOORS-2; i > etasje-1; i--){
				if(etasjeUteNedTabell[i] == 1){
					return nesteTilstand=HEIS_OPP;
				}
			}
		break;

	}
	return IDLE;
}

void brems(retning forrigeTilstand){
	if(forrigeTilstand == BEVEG_OPP){
		for(i=0; i<100;i++){
					elev_set_speed(0);
				}
	}
	else if(forrigeTilstand == BEVEG_NED){
		for(i=0; i<100;i++){
					elev_set_speed(0);
				}
	}
}
