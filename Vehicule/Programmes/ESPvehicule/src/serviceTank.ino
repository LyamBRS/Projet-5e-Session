/**
 * @file serviceTank.ino
 * @author Camille Fortin  CamFo (camfortin2022@gmail.com)
 * @brief Le service tank sert a controler un véhicule avec seulement deux moteur.
 *          Ce service permet au moteur d'avoir 6 (expert 8) état qui lui permet de
 *          se déplacer dans tout les direction possible.
 * @version 0.1
 * @date 2022-11-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "xmain.h"
#include "xinterfaceMoteurDroit.h"
#include "xinterfaceMoteurGauche.h"
#include "serviceTank.h"

void initialise(void)
{
    interfaceMoteurDroit_initialise();
    interfaceMoteurGauche_initialise();


}

