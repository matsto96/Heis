#include "logikk.h"

int etasje;
int temp_etasje;
logikk_tilstand_type naaTilstand = IDLE;
logikk_tilstand_type nesteTilstand = IDLE;

void startHeis(void){
	int i;
	//For å forhindre at et heiskall i heisens nåværende etasje skal resultere i at ordren blir registret, slettet og registrert igjen i det 		tidsintervallet knappen holdes inne. (Siden programmet kjøres mange ganger i det tidsintervallet knappen holdes inne i et knapptrykk)
	if(!(heisData.doerAapenTidTaker >= time(NULL) && heisData.doerAapenTidTaker+1 > time(NULL))){
		lysInne();
		lysNed();
		lysOpp();
		etasjeLys();
	}
	switch(naaTilstand){
		case IDLE:
		  temp_etasje=elev_get_floor_sensor_signal();
			if(elev_get_floor_sensor_signal() != -1){
				etasje = temp_etasje;
				nesteTilstand = nesteTilstandGittIdle(etasje);
			}
			else if(elev_get_floor_sensor_signal() == -1){
				elev_set_motor_direction(DIRN_DOWN);
				while(1){
					if(elev_get_floor_sensor_signal() != -1){
						brems(BEVEG_OPP);
						elev_set_motor_direction(DIRN_STOP);
						break;
					}
				}
				nesteTilstand = IDLE;
			}
			break;
		case AAPNE_DOER:
			if(heisData.doerAapenTidTaker + 3 == time(NULL)){
				temp_etasje=elev_get_floor_sensor_signal();
				if(elev_get_floor_sensor_signal() != -1){
					etasje = temp_etasje;
		        	nesteTilstand = nesteTilstandGittAapneDoer(etasje, heisData.heisRetning);
				}
			}
			else{
				nesteTilstand = AAPNE_DOER;
			}
			break;

		case HEIS_OPP:
			temp_etasje=elev_get_floor_sensor_signal();
			if(elev_get_floor_sensor_signal() != -1){
				etasje = temp_etasje;
				nesteTilstand = nesteTilstandGittHeisOpp(etasje);
			}
			else{
				nesteTilstand = HEIS_OPP;
			}
			break;
		case HEIS_NED:
			if(elev_get_floor_sensor_signal() != -1){
				etasje = elev_get_floor_sensor_signal();
				nesteTilstand = nesteTilstandGittHeisNed(etasje);
			}
			else{
				nesteTilstand = HEIS_NED;
			}
			break;
		case STOPP:
			for(i = 0; i < N_FLOORS; i++){
				if(elev_get_floor_sensor_signal() != -1){
				nesteTilstand = AAPNE_DOER;
						break;
				}
				else if(tabellInne[i] == 1){
					if(i < heisData.forrigeEtasje){
						nesteTilstand = HEIS_NED;
						break;
					}
					else if(i > heisData.forrigeEtasje){
						nesteTilstand = HEIS_OPP;
						break;
					}
					else if(i == heisData.forrigeEtasje && heisData.heisRetning == 0){
						nesteTilstand = AAPNE_DOER;
						break;
					}
					else if(i == heisData.forrigeEtasje && heisData.heisRetning == 1){
						nesteTilstand = HEIS_NED;
						break;
					}
					else if(i == heisData.forrigeEtasje && heisData.heisRetning == 2){
						nesteTilstand = HEIS_OPP;
						break;
					}

					else{
						nesteTilstand = STOPP;
					}
				}
            }
			break;
		case OBSTRUKSJON:  //Så lenge bryteren er kommentert ut, vil ikke dette caset forekomme
			elev_set_motor_direction(DIRN_STOP);
			if(elev_get_obstruction_signal()){
				nesteTilstand = OBSTRUKSJON;
			}
			else{
				nesteTilstand = AAPNE_DOER;
			}
			break;	
		default  : 
			printf( "What is your grade anyway?" );
			break;
	}

	
	//if(elev_get_obstruction_signal()){ 			Ved ønske om obstruksjonsbryter, kan dette tillegges her
	//	nesteTilstand = OBSTRUKSJON;
	//}
	if(elev_get_stop_signal()){
		nesteTilstand = STOPP;
	}
	switch(nesteTilstand){
		case IDLE:
			naaTilstand = IDLE;
			heisData.heisRetning = IRO;
			heisData.doerAapenTidTaker = 0;
			elev_set_door_open_lamp(0);
			break;
		case AAPNE_DOER:
			if(heisData.doerAapenTidTaker == 0){
				heisData.doerAapenTidTaker = time(NULL);
				elev_set_motor_direction(DIRN_STOP);
				if(heisData.forrigeEtasje < N_FLOORS && heisData.forrigeEtasje > 0){
					tabellNed[heisData.forrigeEtasje-1] = 0;
				}
				if(heisData.forrigeEtasje < N_FLOORS-1 && heisData.forrigeEtasje >= 0){
					tabellOpp[heisData.forrigeEtasje] = 0;
				}
				tabellInne[heisData.forrigeEtasje] = 0;
			}
//			else if(elev_get_obstruction_signal()){
//				naaTilstand = OBSTRUKSJON;
//				break;
	//		}
			elev_set_door_open_lamp(1);
			naaTilstand = AAPNE_DOER;
			break;
		case HEIS_OPP:
			elev_set_motor_direction(DIRN_UP);
			naaTilstand = HEIS_OPP;
			heisData.heisRetning = BEVEG_OPP;	
			heisData.stopp = 0;
			heisData.doerAapenTidTaker = 0;
			elev_set_door_open_lamp(0);
			break;
		case HEIS_NED:
			elev_set_motor_direction(DIRN_DOWN);
			naaTilstand = HEIS_NED;
			heisData.heisRetning = BEVEG_NED;
			heisData.stopp = 0;
			heisData.doerAapenTidTaker = 0;	
			elev_set_door_open_lamp(0);	
			break;
		case STOPP:
			while(elev_get_stop_signal()){

                          
			elev_set_motor_direction(DIRN_STOP);		
			if(heisData.stopp == 0){
				stoppLys(1);
				heisData.stopp = 1;
					}
			
				for(i = 0; i < N_FLOORS; i++){
					tabellInne[i] = 0;
				}
				for(i = 0; i < N_FLOORS-1; i++){
					tabellNed[i] = 0;
					tabellOpp[i] = 0;
				}
				
			//}
}
            		stoppLys(0);
            		naaTilstand = STOPP;
			
			break;
			
		case OBSTRUKSJON: 		//Så lenge bryteren er kommentert ut, vil ikke dette caset forekomme
			bestillingOpp();
			bestillingNed();
			bestillingInne();
			lysInne();
			lysOpp();
			lysNed();
			heisData.doerAapenTidTaker = time(NULL);
			naaTilstand = OBSTRUKSJON;
			break;
		default  : 
			printf( "What is your grade anyway?" );
			break;
	}
}
