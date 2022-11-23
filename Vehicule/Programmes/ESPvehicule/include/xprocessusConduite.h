#ifndef PROCESSUSCONDUITE_H
#define PROCESSUSCONDUITE_H

//MODULE: processusClignotant
//DESCRIPTION: implemente la gestion d'un clignotant.

//HISTORIQUE:
// 2018-09-09, Yves Roy, creation
// 2022-04-11, Yves Roy, reutilisation pour ESP32 247-527

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSCONDUITE_TEMPS_ALLUME_EN_MS  500
//#define PROCESSUSCONDUITE_TEMPS_ETEINT_EN_MS  500
//#define PROCESSUSCONDUITE_PHASE 0


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void processusConduite_initialise(void);

//Variables publiques:

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char requete;
} PROCESSUSCONDUITE;

PROCESSUSCONDUITE processusConduite;

#endif
