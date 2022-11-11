#ifndef PILOTEIOFILJAUNE_H
#define PILOTEIOFILJAUNE_H

//MODULE: piloteIOFilJaune
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-10-18, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOFILJAUNE_BROCHE 13
//#define PILOTEIOFILJAUNE_ETAT_INITIAL_A_UN
//#define PILOTEIOFILJAUNE_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteIOFilJaune_metAUn(void);
void piloteIOFilJaune_metAZero(void);
void piloteIOFilJaune_metA(unsigned char Niveau);
void piloteIOFilJaune_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
