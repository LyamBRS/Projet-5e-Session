#ifndef PILOTEENTREE1_H
#define PILOTEENTREE1_H

//MODULE: piloteEntree1
//DESCRIPTION: pour permettre la lecture d'une entree
//ENVIRONNEMENT ESP32 et Arduino 
// 2021-04-04, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
//#define PILOTEENTREE1_MODE_FLOTTANT_SANS_PULL_UP
//#define PILOTEENTREE1_BROCHE 21

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteEntree1_lit(void);
void piloteEntree1_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
