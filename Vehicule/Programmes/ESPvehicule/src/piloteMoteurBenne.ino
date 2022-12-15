/**
 * @file piloteMoteurBenne.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pilote d'une drive moteur connecté au ESP32 du véhicule qui permet de
 *  vider le contenue de la benne
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//piloteMoteurBenne:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteMoteurBenne.h"

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
 * @brief Fonction qui allume le moteur de la benne 
 * 
 */
void piloteMoteurBenne_Allume(void)
{
  digitalWrite(PILOTEMOTEURBENNEHAUT_BROCHE, LOW);
  digitalWrite(PILOTEMOTEURBENNEBAS_BROCHE, HIGH);
}
/**
 * @brief Fonction qui éteint le moteur de la benne
 * 
 */
void piloteMoteurBenne_Eteint(void)
{
  digitalWrite(PILOTEMOTEURBENNEHAUT_BROCHE, LOW);
  digitalWrite(PILOTEMOTEURBENNEBAS_BROCHE, LOW);
}
/**
 * @brief Fonction qui initialise les broche du ESP32 en  
 *  sortie pour pouvoir contrôler la benne. 
 * 
 */
void piloteMoteurBenne_initialise(void)
{
  pinMode(PILOTEMOTEURBENNEHAUT_BROCHE,OUTPUT);
  pinMode(PILOTEMOTEURBENNEBAS_BROCHE,OUTPUT);
	digitalWrite(PILOTEMOTEURBENNEHAUT_BROCHE,LOW);
  digitalWrite(PILOTEMOTEURBENNEBAS_BROCHE,LOW);

}


