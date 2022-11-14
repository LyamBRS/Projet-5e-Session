/**
 * @file piloteIOFeuArriereG.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//piloteIOFeuArriereG:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOFeuArriereG.h"

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
void piloteIOFeuArriereG_metAUn(void)
{
  digitalWrite(PILOTEIOFEUARRIEREG_BROCHE, HIGH);
}

void piloteIOFeuArriereG_metAZero(void)
{
  digitalWrite(PILOTEIOFEUARRIEREG_BROCHE, LOW);
}

void piloteIOFeuArriereG_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOFEUARRIEREG_BROCHE, Niveau);
}

void piloteIOFeuArriereG_initialise(void)
{
  pinMode(PILOTEIOFEUARRIEREG_BROCHE,OUTPUT);

#ifdef PILOTEIOFEUAVANTD_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOFEUARRIEREG_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOFEUAVANTD_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOFEUARRIEREG_BROCHE,LOW);
#endif
}
