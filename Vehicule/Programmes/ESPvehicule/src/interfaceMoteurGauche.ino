/**
 * @file interfaceMoteurGauche.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "xmain.h"
#include "xpilotePWMGaucheBas.h"
#include "xpilotePWMGaucheHaut.h"
#include "xinterfaceMoteurGauche.h"

void interfaceMoteurGauche_Avance(unsigned char value)
{
    pilotePWMGaucheHaut_setPWM(value);
}

void interfaceMoteurGauche_Recule(unsigned char value)
{
    pilotePWMGaucheBas_setPWM(value);
}

void interfaceMoteurGauche_initialise(void)
{
    pilotePWMGaucheBas_initialise();
    pilotePWMGaucheHaut_initialise();
}