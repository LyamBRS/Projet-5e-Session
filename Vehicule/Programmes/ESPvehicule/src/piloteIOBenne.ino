/**
 * @file piloteIOBenne.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//piloteIOBenne:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOBenne.h"

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
void piloteIOBenne_metAUn(void)
{
  digitalWrite(PILOTEIOBENNE_BROCHE, HIGH);
}

void piloteIOBenne_metAZero(void)
{
  digitalWrite(PILOTEIOBENNE_BROCHE, LOW);
}

void piloteIOBenne_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOBENNE_BROCHE, Niveau);
}

void piloteIOBenne_initialise(void)
{
  pinMode(PILOTEIOBENNE_BROCHE,OUTPUT);

#ifdef PILOTEIOBENNE_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOBENNE_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOBENNE_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOBENNE_BROCHE,LOW);
#endif
}


