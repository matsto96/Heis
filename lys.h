#ifndef __INCLUDE_LYS_H__
#define __INCLUDE_LYS_H__

//Skrur på bestillingslys inne i heiskupéen.
void lysInne(void);


//Skrur på bestillingslys for å indikere heiskall uteifra i heisretning ned.
void lysUteNed(void);


//Skrur på bestillingslys for å indikere heiskall uteifra i heisretning opp.
void lysUteOpp(void);


//Setter på lysene til etasjeindikator.
void indikatorLysUte(void);


/**
Skrur av/på stopplys.
@param 1=på,  0=av.
*/
void stoppLys(int lys);


#endif
