/**
 * @file xpiloteMoteurBenne.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief  Pilote d'une drive moteur connecté au ESP32 du véhicule qui permet de
 *  vider le contenue de la benne
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef piloteMoteurBenne_H
#define piloteMoteurBenne_H

//MODULE: piloteMoteurBenne
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define piloteMoteurBenne_BROCHE 13
//#define piloteMoteurBenne_ETAT_INITIAL_A_UN
//#define piloteMoteurBenne_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:

/**
 * @brief Fonction qui allume le moteur de la benne 
 * 
 */
void piloteMoteurBenne_Allume(void);
/**
 * @brief Fonction qui éteint le moteur de la benne
 * 
 */
void piloteMoteurBenne_Eteint(void);
/**
 * @brief Fonction qui initialise les broche du ESP32 en  
 *  sortie pour pouvoir contrôler la benne. 
 * 
 */
void piloteMoteurBenne_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
