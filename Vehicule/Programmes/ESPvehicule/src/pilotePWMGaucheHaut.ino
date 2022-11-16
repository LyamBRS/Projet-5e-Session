/**
 * @file pilotePWMGaucheHaut.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//pilotePWMGaucheHaut:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpilotePWMGaucheHaut.h"

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

void pilotePWMGaucheHaut_setPWM(unsigned char dutyCycle)
{
  ledcWrite(PILOTEPWMGAUCHEHAUT_CHANNEL, dutyCycle);
}

void pilotePWMGaucheHaut_initialise(void)
{
  ledcSetup(PILOTEPWMGAUCHEHAUT_CHANNEL, PILOTEPWM_FREQUENCE, PILOTEPWM_RESOLUTION);
  ledcAttachPin(PILOTEPWMGAUCHEHAUT_PIN, PILOTEPWMGAUCHEHAUT_CHANNEL);
  ledcWrite(PILOTEPWMGAUCHEHAUT_CHANNEL, 0); // Pour éteindre le moteur à l'initialisation
}


