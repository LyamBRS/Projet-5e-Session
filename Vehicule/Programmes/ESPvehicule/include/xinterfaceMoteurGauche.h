/**
 * @file xinterfaceMoteurGauche.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pour contrôler le moteur gauche dans les 2 sens avec un PWM
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INTERFACEMOTEURGAUCHE_H
#define INTERFACEMOTEURGAUCHE_H

//MODULE: interfaceMoteurGauche




//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles


//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceMoteurGauche_Avance(unsigned char value);
void interfaceMoteurGauche_Recule(unsigned char value);
void interfaceMoteurGauche_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
