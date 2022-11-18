#ifndef INTERFACET2_H
#define INTERFACET2_H

//MODULE: interfaceT1
//DESCRIPTION: pour interagir avec un temoin lumineux T2 relie a un STM32F407. 

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACET2_VALEUR_POUR_ALLUMER  1   
//#define INTERFACET2_VALEUR_POUR_ETEINDRE 0

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceT2_allume(void);
void interfaceT2_eteint(void);
void interfaceT2_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
