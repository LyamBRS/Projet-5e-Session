/**
 * @file piloteIOFeuAvantG.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Fichier pilote qui sert au contrôle du clignotant avant Gauche
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//piloteIOFeuAvantG:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOFeuAvantG.h"

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
void piloteIOFeuAvantG_metAUn(void)
{
  digitalWrite(PILOTEIOFEUAVANTG_BROCHE, HIGH);
}

void piloteIOFeuAvantG_metAZero(void)
{
  digitalWrite(PILOTEIOFEUAVANTG_BROCHE, LOW);
}

void piloteIOFeuAvantG_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOFEUAVANTG_BROCHE, Niveau);
}

void piloteIOFeuAvantG_initialise(void)
{
  pinMode(PILOTEIOFEUAVANTG_BROCHE,OUTPUT);

#ifdef PILOTEIOFEUAVANTD_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOFEUAVANTG_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOFEUAVANTD_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOFEUAVANTG_BROCHE,LOW);
#endif
}
