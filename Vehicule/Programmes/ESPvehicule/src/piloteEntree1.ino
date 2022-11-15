/**
 * @file piloteEntree1.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pilote de la limite switch de la benne du véhicule
 * 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntree1.h"

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
unsigned char piloteEntree1_lit(void)
{
  return digitalRead(PILOTEENTREE1_BROCHE);
}

void piloteEntree1_initialise(void)
{
#ifdef PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
	pinMode(PILOTEENTREE1_BROCHE,INPUT_PULLUP);
#endif

#ifdef PILOTEENTREE1_MODE_FLOTTANT_SANS_PULL_UP
	pinMode(PILOTEENTREE1_BROCHE);
#endif
}
