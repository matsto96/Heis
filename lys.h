#ifndef __INCLUDE_LYS_H__
#define __INCLUDE_LYS_H__

//Skrur på bestillingslys inne i heiskupéen.
void etasjelysInne(void);


//Skrur på bestillingslys for å indikere heiskall uteifra i heisretning ned.
void etasjelysUteNed(void);


//Skrur på bestillingslys for å indikere heiskall uteifra i heisretning opp.
void etasjelysUteOpp(void);


//Setter på lysene til etasjeindikator.
void etasjeIndikatorUte(void);


/**
Skrur av/på stopplys.
@param 1=på,  0=av.
*/
void stoppLys(int lys);


#endif
