/**
 * @file piloteIOT1.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pilote qui contrôle la broche d'un microcontrôleur en utilisant
 *  la librairie Arduino. (digitalWrite et pinMode)
 * 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//piloteIOT1:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOT1.h"

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

/**
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOT1_BROCHE du microcontrôleur 
 * 
 */
void piloteIOT1_metAUn(void)
{
  digitalWrite(PILOTEIOT1_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOT1_BROCHE du mirocontrôleur
 * 
 */
void piloteIOT1_metAZero(void)
{
  digitalWrite(PILOTEIOT1_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOT1_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOT1_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOT1_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref PILOTEIOT1_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOT1_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOT1_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOT1_initialise(void)
{
  pinMode(PILOTEIOT1_BROCHE,OUTPUT);

#ifdef PILOTEIOT1_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOT1_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOT1_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOT1_BROCHE,LOW);
#endif
}
