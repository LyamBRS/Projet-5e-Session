/**
 * @file xpiloteMoteurBenne.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
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
void piloteMoteurBenne_metAUn(void);
void piloteMoteurBenne_metAZero(void);
void piloteMoteurBenne_metA(unsigned char Niveau);
void piloteMoteurBenne_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
