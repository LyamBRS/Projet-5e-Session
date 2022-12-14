/**
 * @file interfaceMoteurBenne.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief  Interface qui permet d'éteindre et d'allumer le moteur de la benne
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
/**
 * @brief Fonction qui allume le moteur de la benne
 * 
 */
void interfaceMoteurBenne_allume(void)
{
  piloteMoteurBenne_Allume();
}
/**
 * @brief Fonction qui éteint le moteur de la benne
 * 
 */
void interfaceMoteurBenne_eteint(void)
{
  piloteMoteurBenne_Eteint();
}
/**
 * @brief Fonction qui initialise le moteur de la benne en 
 *  arret pret à partir 
 * 
 */
void interfaceMoteurBenne_initialise(void)
{
  piloteMoteurBenne_initialise();
}
