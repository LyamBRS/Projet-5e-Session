#ifndef PILOTEIOFILROSE_H
#define PILOTEIOFILROSE_H

//MODULE: piloteIOFilRose
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-10-18, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOFILROSE_BROCHE 13
//#define PILOTEIOFILROSE_ETAT_INITIAL_A_UN
//#define PILOTEIOFILROSE_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteIOFilRose_metAUn(void);
void piloteIOFilRose_metAZero(void);
void piloteIOFilRose_metA(unsigned char Niveau);
void piloteIOFilRose_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
