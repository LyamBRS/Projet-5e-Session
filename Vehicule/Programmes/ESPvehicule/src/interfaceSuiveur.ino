/**
 * @file interfaceSuiveur.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "xmain.h"
#include "xpiloteI2C1.h"



//Fonctions publiques:
unsigned char interfaceSuiveur_litOctet(void)
{
    return piloteI2C1_lisUnOctet(INTERFACESUIVEUR_ADRESSE);
}

void interfaceSuiveur_initialise(void)
{
    piloteI2C1_initialise();
}
