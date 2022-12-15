#ifndef INTERFACET4_H
#define INTERFACET4_H

//MODULE: interfaceT4
//DESCRIPTION: pour interagir avec un temoin lumineux T4 relie a un STM32F407. 

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACET4_VALEUR_POUR_ALLUMER  1   
//#define INTERFACET4_VALEUR_POUR_ETEINDRE 0

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceT4_allume(void);
void interfaceT4_eteint(void);
void interfaceT4_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
