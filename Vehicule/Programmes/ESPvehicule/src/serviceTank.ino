/**
 * @file serviceTank.ino
 * @author Camille Fortin  CamFo (camfortin2022@gmail.com)
 * @brief Le service tank sert a controler un véhicule avec seulement deux moteur.
 *          Ce service permet au moteur d'avoir 6 (peut etre 8) état qui lui permet de
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

/**
 * @brief Fonction d'initialisation d'initialisation du service tank 
 *  qui permet au deux moteur d'être en arrêt et pret à partir  
 * 
 * @return * void 
 */
void serviceTank_initialise(void)
{
    interfaceMoteurDroit_initialise();
    interfaceMoteurGauche_initialise();
}

/**
 * @brief Fonction qui arrête les deux moteurs
 * 
 * @return * void 
 */
void serviceTank_Arret(void)
{
    interfaceMoteurDroit_Avance(0);
    interfaceMoteurGauche_Avance(0);
    interfaceMoteurDroit_Recule(0);
    interfaceMoteurGauche_Recule(0);
}

/**
 * @brief Fonction qui fait avancer les deux moteur selon la vitesse fourni.
 *  La vitesse est une valeur de 0 à 255 qui correspond au duty cycle d'un PWM 
 * 
 * @param vitesse 
 * @return * void 
 */
void serviceTank_Avance(unsigned char vitesse)
{
    interfaceMoteurDroit_Avance(vitesse);
    interfaceMoteurGauche_Avance(vitesse);
}
/**
 * @brief Fonction qui fait tourner a droite le véhicule selon la vitesse fourni. \n
 *  Un moteur est actif et l'autre en arrêt \n
 *  La vitesse est une valeur de 0 à 255 qui correspond au duty cycle d'un PWM 
 * 
 * @param vitesse 
 * @return * void 
 */
void serviceTank_tourneDroit(unsigned char vitesse)
{
    interfaceMoteurDroit_Avance(0);     // Moteur droit a 0
    interfaceMoteurGauche_Avance(vitesse);  // Moteur gauche avance
}
/**
 * @brief Fonction qui fait tourner a Gauche le véhicule selon la vitesse fourni. \n
 *  Un moteur est actif et l'autre en arrêt \n
 *  La vitesse est une valeur de 0 à 255 qui correspond au duty cycle d'un PWM 
 * 
 * @param vitesse 
 * @return * void 
 */
void serviceTank_tourneGauche(unsigned char vitesse)
{
    interfaceMoteurDroit_Avance(vitesse);  // Moteur droit avance
    interfaceMoteurGauche_Avance(0);   // Moteur gauche a 0
}
/**
 * @brief Fonction qui fait tournerle véhicule sur lui même vers la droite selon la vitesse fourni. \n
 *  Un moteur est actif dans un sens et l'autre moteur dans le sens contraire. \n
 *  La vitesse est une valeur de 0 à 255 qui correspond au duty cycle d'un PWM.
 * 
 * @param vitesse 
 * @return * void 
 */
void serviceTank_uturnDroit(unsigned char vitesse)
{
    interfaceMoteurDroit_Avance(0);
    interfaceMoteurGauche_Recule(0);
    interfaceMoteurDroit_Recule(vitesse); 
    interfaceMoteurGauche_Avance(vitesse);
}
/**
 * @brief Fonction qui fait tournerle véhicule sur lui même vers la gauche selon la vitesse fourni. \n
 *  Un moteur est actif dans un sens et l'autre moteur dans le sens contraire. \n
 *  La vitesse est une valeur de 0 à 255 qui correspond au duty cycle d'un PWM.
 * 
 * @param vitesse 
 * @return * void 
 */
void serviceTank_uturnGauche(unsigned char vitesse)
{
    interfaceMoteurDroit_Recule(0);
    interfaceMoteurGauche_Avance(0);
    interfaceMoteurDroit_Avance(vitesse);
    interfaceMoteurGauche_Recule(vitesse);
}