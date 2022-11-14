/**
 * @file xpiloteIOBenne.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef piloteIOBenne_H
#define piloteIOBenne_H

//MODULE: piloteIOBenne
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define piloteIOBenne_BROCHE 13
//#define piloteIOBenne_ETAT_INITIAL_A_UN
//#define piloteIOBenne_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteIOBenne_metAUn(void);
void piloteIOBenne_metAZero(void);
void piloteIOBenne_metA(unsigned char Niveau);
void piloteIOBenne_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
