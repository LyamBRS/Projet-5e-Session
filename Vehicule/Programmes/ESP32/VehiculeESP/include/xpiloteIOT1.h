#ifndef PILOTEIOT1_H
#define PILOTEIOT1_H

//MODULE: piloteIOT1
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT1_BROCHE 13
//#define PILOTEIOT1_ETAT_INITIAL_A_UN
//#define PILOTEIOT1_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteIOT1_metAUn(void);
void piloteIOT1_metAZero(void);
void piloteIOT1_metA(unsigned char Niveau);
void piloteIOT1_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
