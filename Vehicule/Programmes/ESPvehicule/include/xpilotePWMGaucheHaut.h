/**
 * @file xpilotePWMGaucheHaut.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef pilotePWMGaucheHaut_H
#define pilotePWMGaucheHaut_H

//MODULE: pilotePWMGaucheHaut
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define pilotePWMGaucheHaut_BROCHE 13
//#define pilotePWMGaucheHaut_ETAT_INITIAL_A_UN
//#define pilotePWMGaucheHaut_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void pilotePWMGaucheHaut_setPWM(unsigned char dutyCycle);
void pilotePWMGaucheHaut_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
