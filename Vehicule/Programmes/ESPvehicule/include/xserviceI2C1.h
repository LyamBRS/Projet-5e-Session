/**
 * @file xserviceI2C1.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief pour mettre en place un service de gestion de l'acces au port I2C
 * L'acces au port I2C1 est permis lorsque serviceI2C1_acces = SERVICEI2C1_ACCES_PERMIS et
 * il ne l'est pas lorsque serviceI2C1_acces = SERVICEI2C1_ACCES_INTERDIT
 * Un module obtient l'usage exclusif du port I2C en mettant serviceI2C_acces a
 * SERVICEI2C1_INTERDIT et il libere le port en mettant serviceI2C_acces a
 * SERVICEI2C1_PERMIS.
 * Le module qui a un acces exclusif au port I2C1 doit faire appel aux fonctions
 * du module piloteI2C1 pour communiquer I2C et liberer le service une fois
 * ses transactions terminees.
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SERVICEI2C1_H
#define SERVICEI2C1_H

//MODULE: serviceI2C1

//HISTORIQUE:
// 2021-11-22, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
/**
 * @brief Définition pour l'accès au port I2C
 * 
 */
#define SERVICEI2C1_ACCES_PERMIS 1
/**
 * @brief Définition pour l'accès au port I2C
 * 
 */
#define SERVICEI2C1_ACCES_INTERDIT 0

//Fonctions publiques:
/**
 * @brief Fonction d'initialisation du pilote I2C
 * 
 */
void serviceI2C1_initialise(void);

//Variables publiques pour l'accès au port I2C
extern unsigned char serviceI2C1_acces;

#endif
