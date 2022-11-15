/**
 * @file piloteIOFeuArriereD.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Fichier pilote qui sert au contrôle du clignotant Arrière Droit
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOFeuArriereD.h"

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
void piloteIOFeuArriereD_metAUn(void)
{
  digitalWrite(PILOTEIOFEUARRIERED_BROCHE, HIGH);
}

void piloteIOFeuArriereD_metAZero(void)
{
  digitalWrite(PILOTEIOFEUARRIERED_BROCHE, LOW);
}

void piloteIOFeuArriereD_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOFEUARRIERED_BROCHE, Niveau);
}

void piloteIOFeuArriereD_initialise(void)
{
  pinMode(PILOTEIOFEUARRIERED_BROCHE,OUTPUT);

#ifdef PILOTEIOFEUAVANTD_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOFEUARRIERED_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOFEUAVANTD_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOFEUARRIERED_BROCHE,LOW);
#endif
}
