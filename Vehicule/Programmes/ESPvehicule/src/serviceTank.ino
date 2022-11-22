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

void serviceTank_initialise(void)
{
    interfaceMoteurDroit_initialise();
    interfaceMoteurGauche_initialise();

}
void serviceTank_arret(void)
{
    interfaceMoteurDroit_Avance(0);
    interfaceMoteurGauche_Avance(0);
}

void serviceTank_tourneDroit(unsigned char vitesse)
{
    interfaceMoteurDroit_Avance(0);     // Moteur droit a 0
    interfaceMoteurGauche_Avance(vitesse);  // Moteur gauche avant max
}

void serviceTank_tourneGauche(unsigned char vitesse)
{
    interfaceMoteurDroit_Avance(vitesse);  // Moteur droit avant max
    interfaceMoteurGauche_Avance(0);   // Moteur gauche a 0
}
void serviceTank_uturnDroit(unsigned char vitesse)
{
    interfaceMoteurDroit_Recule(vitesse); 
    interfaceMoteurGauche_Avance(vitesse);
}
void serviceTank_uturnGauche(unsigned char vitesse)
{
    interfaceMoteurDroit_Avance(vitesse);
    interfaceMoteurGauche_Recule(vitesse);
}