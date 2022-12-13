#ifndef INTERFACEB1_H
#define INTERFACEB1_H

//MODULE: interfaceB1
//DESCRIPTION: pour s'interfacer avec le bouton B1. 
//L'etat du bouton est lu periodiquement et les decisions rendues par rapport a
//son etat se base sur un nombre minimum de lecture afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La fréquence INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit être un multiple de la fréquence de la base de temps utilisée.
//Le nombre minimum de lecture est donne par
//INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2018-09-08, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEB1_VALEUR_LUE_SI_APPUYE  1   
//#define INTERFACEB1_VALEUR_LUE_SI_RELACHE 0
//#define INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ  100
//#define INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEB1_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACEB1_RELACHE  0
#define INTERFACEB1_APPUYE  1
#define INTERFACEB1_INCONNU 2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDuBouton;
} INTERFACEB1;

//Fonctions publiques:
void interfaceB1_initialise(void);

//Variables publiques:
extern INTERFACEB1 interfaceB1;

#endif
