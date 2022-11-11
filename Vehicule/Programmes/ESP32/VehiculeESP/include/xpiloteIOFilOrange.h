#ifndef PILOTEIOFILORANGE_H
#define PILOTEIOFILORANGE_H

//MODULE: piloteIOFilOrange
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-10-18, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOFILORANGE_BROCHE 13
//#define PILOTEIOFILORANGE_ETAT_INITIAL_A_UN
//#define PILOTEIOFILORANGE_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteIOFilOrange_metAUn(void);
void piloteIOFilOrange_metAZero(void);
void piloteIOFilOrange_metA(unsigned char Niveau);
void piloteIOFilOrange_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
