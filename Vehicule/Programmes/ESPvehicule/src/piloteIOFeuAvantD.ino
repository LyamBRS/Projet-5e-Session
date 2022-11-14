/**
 * @file piloteIOFeuAvantD.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//piloteIOFeuAvantD:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOFeuAvantD.h"

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
void piloteIOFeuAvantD_metAUn(void)
{
  digitalWrite(PILOTEIOFEUAVANTD_BROCHE, HIGH);
}

void piloteIOFeuAvantD_metAZero(void)
{
  digitalWrite(PILOTEIOFEUAVANTD_BROCHE, LOW);
}

void piloteIOFeuAvantD_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOFEUAVANTD_BROCHE, Niveau);
}

void piloteIOFeuAvantD_initialise(void)
{
  pinMode(PILOTEIOFEUAVANTD_BROCHE,OUTPUT);

#ifdef PILOTEIOFEUAVANTD_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOFEUAVANTD_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOFEUAVANTD_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOFEUAVANTD_BROCHE,LOW);
#endif
}
