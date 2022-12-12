/**
 * @file piloteEntree1.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pilote qui permet la lecture d'une broche d'un microcontrôleur 
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

/// @brief Fonction qui permet de savoir l'état logique d'une BROCHE d'un micocontrôleur
/// @param Aucun \ref PILOTEENTREE1_BROCHE est une définition dans \ref xmain.h  
/// @return Valeur de la PIN de 1 ou 0 sur un unsigned char  
unsigned char piloteEntree1_lit(void)
{
  return digitalRead(PILOTEENTREE1_BROCHE);
}
/// @brief Foncion qui initialise la lecture de la Broche du microcontrôleur
/// @param Aucun \ref PILOTEENTREE1_BROCHE est une définition dans \ref xmain.h  
void piloteEntree1_initialise(void)
{
#ifdef PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
	pinMode(PILOTEENTREE1_BROCHE,INPUT_PULLUP);
#endif

#ifdef PILOTEENTREE1_MODE_FLOTTANT_SANS_PULL_UP
	pinMode(PILOTEENTREE1_BROCHE);
#endif
}
