/**
 * @file interfaceT1.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Interface qui contrôle la del su Board Adafruit ESP32 feather
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOT1.h"
#include "xinterfaceT1.h"

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
void interfaceT1_allume(void)
{
  piloteIOT1_metA(INTERFACET1_VALEUR_POUR_ALLUMER);
}

void interfaceT1_eteint(void)
{
  piloteIOT1_metA(INTERFACET1_VALEUR_POUR_ETEINDRE);
}

void interfaceT1_initialise(void)
{
  piloteIOT1_metA(INTERFACET1_VALEUR_POUR_ETEINDRE);
}
