/**
 * @file xinterfaceMoteurBenne.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Interface qui permet d'éteindre et d'allumer le moteur de la benne
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INTERFACEMoteurBenne_H
#define INTERFACEMoteurBenne_H

//MODULE: interfaceMoteurBenne
//DESCRIPTION: pour s'interfacer avec le moteur de la benne du véhicule.

//HISTORIQUE:
// 2018-09-08, Yves Roy, creation
// 2022-04-11, reutilisation avec le ESP32 en 247-527

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEMoteurBenne_VALEUR_POUR_ALLUMER  1   
//#define INTERFACEMoteurBenne_VALEUR_POUR_ETEINDRE 0

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
/**
 * @brief Fonction qui allume le moteur de la benne
 * 
 */
void interfaceMoteurBenne_allume(void);
/**
 * @brief Fonction qui éteint le moteur de la benne
 * 
 */
void interfaceMoteurBenne_eteint(void);
/**
 * @brief Fonction qui initialise le moteur de la benne en 
 *  arret pret à partir 
 * 
 */
void interfaceMoteurBenne_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
