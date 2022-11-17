/**
 * @file pilotePWMDroitHaut.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//pilotePWMDroitHaut:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpilotePWMDroitHaut.h"

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

void pilotePWMDroitHaut_setPWM(unsigned char dutyCycle)
{
  ledcWrite(PILOTEPWMDROITHAUT_CHANNEL, dutyCycle);
}

void pilotePWMDroitHaut_initialise(void)
{
  ledcSetup(PILOTEPWMDROITHAUT_CHANNEL, PILOTEPWM_FREQUENCE, PILOTEPWM_RESOLUTION);
  ledcAttachPin(PILOTEPWMDROITHAUT_PIN, PILOTEPWMDROITHAUT_CHANNEL);
  ledcWrite(PILOTEPWMDROITHAUT_CHANNEL, 0); //Pour éteindre le moteur a l'initialisation
}


