/**
 * @file interfaceMoteurDroit.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "xmain.h"
#include "xpilotePWMDroitBas.h"
#include "xpilotePWMDroitHaut.h"
#include "xinterfaceMoteurDroit.h"

void interfaceMoteurDroit_Avance(unsigned char value)
{
    pilotePWMDroitBas_setPWM(value);  // Pour Avancer avec le moteur
    pilotePWMDroitHaut_setPWM(0);
}

void interfaceMoteurDroit_Recule(unsigned char value)
{
    pilotePWMDroitHaut_setPWM(value); // Pour Reculer avec le moteur
    pilotePWMDroitBas_setPWM(0);
}

void interfaceMoteurDroit_initialise(void)
{
    pilotePWMDroitBas_initialise();
    pilotePWMDroitHaut_initialise();
}