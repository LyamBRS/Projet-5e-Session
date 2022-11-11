#ifndef PILOTEIOFILBLEU_H
#define PILOTEIOFILBLEU_H

//MODULE: piloteIOFilBleu
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-10-18, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOFILBLEU_BROCHE 13
//#define PILOTEIOFILBLEU_ETAT_INITIAL_A_UN
//#define PILOTEIOFILBLEU_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteIOFilBleu_metAUn(void);
void piloteIOFilBleu_metAZero(void);
void piloteIOFilBleu_metA(unsigned char Niveau);
void piloteIOFilBleu_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
