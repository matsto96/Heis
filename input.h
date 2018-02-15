#ifndef __INCLUDE_INPUT_H__
#define __INCLUDE_INPUT_H__
#include "elev.h"
#include <stdlib.h>

//Tabeller for registrering av ordre ute i retning opp og ned, samt ordre inne ifra heiskupéen.
extern int etasjeUteNedTabell[N_FLOORS-1];
extern int etasjeUteOppTabell[N_FLOORS-1];
extern int etasjeInneTabell[N_FLOORS];

// Brukes for å definere hvilken av tilstandene idle, heis_opp og heis_ned heisen sist var i.
typedef enum retning_heis{
	IRO = 0,
	BEVEG_OPP = 1,
	BEVEG_NED = 2
}retning;

typedef struct _heisVar{	//Heisvariabler
	retning heisRetning;
	int forrigeEtasje;	// Forrige passert etasje.
	int stopp;		// Tester om man går fra case-stopp->case-stopp.
	int doerAapenTidTaker;
} heisVar;

extern heisVar heisData;


//Oppdaterer tabellen for bestillinger inne ifra heiskupéen.
void etasjeBestillingInne(void);


//Oppdaterer tabellen for bestillinger ute i retning ned.
void etasjeBestillingUteNed(void);


//Oppdaterer tabellen for bestillinger ute i retning opp.
void etasjeBestillingUteOpp(void);



#endif
