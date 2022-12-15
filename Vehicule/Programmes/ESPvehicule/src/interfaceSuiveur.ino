/**
 * @file interfaceSuiveur.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * 
 * @brief L'interface Suiveur de ligne permet de communiquer en I2C avec 
 *   un PCF8574 qui sert à la lecture de la ligne.
 * 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "xmain.h"
#include "xpiloteI2C1.h"

//Fonctions publiques:

/**
 * @brief Fonction qui lit le suiveur de ligne et retourne la valeur lu en unsigned char
 * 
 * @return unsigned char 
 */
unsigned char interfaceSuiveur_litOctet(void)
{
    return piloteI2C1_lisUnOctet(INTERFACESUIVEUR_ADRESSE);
}
/**
 * @brief Initilaise la communication I2C avec le suiveur de ligne 
 * 
 */
void interfaceSuiveur_initialise(void)
{
    piloteI2C1_initialise();
}
