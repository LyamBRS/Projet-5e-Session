/**
 * @file xpiloteI2C1.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief  Fichier conteneant le code du pilote I2C fonctionnant avec 
 *    un ESP32. Le pilote utilise la librairie \ref Wire.h fourni avec 
 *    l'environnement arduino. 
 * 
 * @version 0.1
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PILOTEI2C1_H
#define PILOTEI2C1_H

//MODULE: piloteI2C1
//DESCRIPTION: pour permettre l'emploi d'un port I2C

// 2021-07-08, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEI2C1_SCL    19  //22 pour adafruit
//#define PILOTEI2C1_SDA    18  //21 pour adafruit
//#define PILOTEI2C1_FREQUENCE_D_HORLOGE_EN_HZ 400000

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:

/// @brief Fonction qui lit un octect précédament envoyé sur le port I2C 
/// @param Adresse Adresse I2C
/// @return La valeur lu sur le port I2C
unsigned char piloteI2C1_lisUnOctet(unsigned char Adresse);

/// @brief Fonction qui ecris un Octet sur le port I2C
/// @param Adresse 
/// @param Octet 
void piloteI2C1_ecritUnOctet(unsigned char Adresse, char Octet);

/// @brief Fonction qui lit un entier (unsigned int) recu sur le port I2C
/// @param Adresse 
/// @return Un entier recu sur le port I2C (unsigned int)
unsigned int piloteI2C1_lisUnEntier(unsigned char Adresse);

/// @brief Fonction qui écrit un entier (unsigned int) sur le port I2C
/// @param Adresse 
/// @param Entier 
void piloteI2C1_ecritUnEntier(unsigned char Adresse, unsigned int Entier);

/// @brief Fonction qui lit un registre d'un microcontrôleur avec le port I2C
/// @param Adresse Adresse I2C
/// @param Registre Adresse du registre à lire 
/// @param ValeurLue L'adresse de la variable ou mettre la valeur du registre lu
void piloteI2C1_litUnRegistre(unsigned char Adresse, unsigned char Registre, char *ValeurLue);

/// @brief Fonction qui écrit dans un registre d'un microcontrôleur avec le port I2C
/// @param Adresse Adresse I2C
/// @param Registre Adresse du registre à lire 
/// @param Octet Valeur qu'on veut envoyé dans le registre 
void piloteI2C1_ecritUnOctetDansUnRegistre(unsigned char Adresse, unsigned char Registre, char Octet);

/// @brief Fonction qui permet de lire automatiquement plusieurs registre d'un microcontrôleur 
/// @param Adresse Adresse I2C
/// @param Registre Première adresse des registre à lire 
/// @param Nombre Nombre de registre qui doivent être lu
/// @param ValeursLues L'adresse du tableau ou mettre les valeurs des registres lu
void piloteI2C1_litAutomatiquementDesRegistres(unsigned char Adresse, unsigned char Registre, unsigned char Nombre, char *ValeursLues);

/// @brief Fonction qui initialise le port I2C
/// @param  Aucun
void piloteI2C1_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
