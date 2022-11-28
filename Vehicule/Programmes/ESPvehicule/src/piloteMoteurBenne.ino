/**
 * @file piloteMoteurBenne.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
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
void piloteMoteurBenne_Allume(void)
{
  digitalWrite(PILOTEMOTEURBENNEHAUT_BROCHE, LOW);
  digitalWrite(PILOTEMOTEURBENNEBAS_BROCHE, HIGH);
}

void piloteMoteurBenne_Eteint(void)
{
  digitalWrite(PILOTEMOTEURBENNEHAUT_BROCHE, LOW);
  digitalWrite(PILOTEMOTEURBENNEBAS_BROCHE, LOW);
}

void piloteMoteurBenne_initialise(void)
{
  pinMode(PILOTEMOTEURBENNEHAUT_BROCHE,OUTPUT);
  pinMode(PILOTEMOTEURBENNEBAS_BROCHE,OUTPUT);
	digitalWrite(PILOTEMOTEURBENNEHAUT_BROCHE,LOW);
  digitalWrite(PILOTEMOTEURBENNEBAS_BROCHE,LOW);

}


