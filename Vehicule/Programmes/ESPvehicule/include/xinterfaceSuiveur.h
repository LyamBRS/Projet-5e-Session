/**
 * @file xinterfaceSuiveur.h
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
#ifndef INTERFACESUIVEUR_H
#define INTERFACESUIVEUR_H


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles


//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:


/**
 * @brief Fonction qui lit le suiveur de ligne et retourne la valeur lu en unsigned char
 * 
 * @return unsigned char 
 */
unsigned char interfaceSuiveur_litOctet(void);
/**
 * @brief Initilaise la communication I2C avec le suiveur de ligne 
 * 
 */
void interfaceSuiveur_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
