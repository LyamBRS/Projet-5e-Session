/**
 * @file piloteMoteurBenne.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//piloteMoteurBenne:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteMoteurBenne.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void piloteMoteurBenne_metAUn(void)
{
  digitalWrite(PILOTEMOTEURBENNE_BROCHE, HIGH);
}

void piloteMoteurBenne_metAZero(void)
{
  digitalWrite(PILOTEMOTEURBENNE_BROCHE, LOW);
}

void piloteMoteurBenne_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEMOTEURBENNE_BROCHE, Niveau);
}

void piloteMoteurBenne_initialise(void)
{
  pinMode(PILOTEMOTEURBENNE_BROCHE,OUTPUT);

#ifdef PILOTEMOTEURBENNE_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEMOTEURBENNE_BROCHE,HIGH);	
#endif

#ifdef PILOTEMOTEURBENNE_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEMOTEURBENNE_BROCHE,LOW);
#endif
}


