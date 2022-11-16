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


void initialise(void)
{
    pilotePWMDroitBas_initialise();
    pilotePWMDroitHaut_initialise();
}