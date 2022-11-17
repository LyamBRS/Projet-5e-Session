/**
 * @file interfaceMoteurBenne.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "xmain.h"
#include "xpiloteMoteurBenne.h"
#include "xinterfaceMoteurBenne.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceMoteurBenne_allume(void)
{
  piloteMoteurBenne_metA(INTERFACEMOTEURBENNE_VALEUR_POUR_ALLUMER);
}

void interfaceMoteurBenne_eteint(void)
{
  piloteMoteurBenne_metA(INTERFACEMOTEURBENNE_VALEUR_POUR_ETEINDRE);
}

void interfaceMoteurBenne_initialise(void)
{
  piloteMoteurBenne_metA(INTERFACEMOTEURBENNE_VALEUR_POUR_ETEINDRE);
}
