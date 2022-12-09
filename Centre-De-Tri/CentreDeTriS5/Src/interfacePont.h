#ifndef INTERFACEPONT_H
#define INTERFACEPONT_H

//MODULE: interfacePont
//DESCRIPTION: pour interagir avec le pont relie a un STM32F407. 

//HISTORIQUE:
// 2022-12-08, Karl Naudin, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void BaseDeTempsPont(unsigned char *ucLisBaseTempsPont);
bool interfacePont_Position0(void);
bool interfacePont_Position1(void);
bool interfacePont_Position2(void);
void interfacePont_initialise(void);
extern void (*interfacePont_execute)(void);
extern unsigned char ucPosition;
extern unsigned char ucResultatDeplacement;
extern unsigned char ucError;

//Variables publiques:
//pas de variables publiques

#endif
