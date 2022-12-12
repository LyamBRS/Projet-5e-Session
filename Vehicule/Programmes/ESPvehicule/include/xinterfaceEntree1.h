#ifndef INTERFACEENTREE1_H
#define INTERFACEENTREE1_H

//MODULE: interfaceEntree1
//DESCRIPTION: pour s'interfacer avec l'entree 1
//L'etat de l'entree est lu periodiquement et les decisions rendues par rapport a
//son etat se basent sur un nombre minimum de lectures afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La periode de la frequence INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit etre un multiple de la periode frequence de la base de temps utilisee.
//Dit autrement, la frequence de la base de temps utilisee doit etre un multiple de
//la frequence INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2021-04-04, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREE1_VALEUR_LUE_SI_ACTIVE  1   
//#define INTERFACEENTREE1_VALEUR_LUE_SI_INACTIVE 0
//#define INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ  250
//#define INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEENTREE1_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:


#define INTERFACEENTREE1_MODULE_EN_FONCTION 1
#define INTERFACEENTREE1_MODULE_PAS_EN_FONCTION 0
#define INTERFACEENTREE1_INFORMATION_DISPONIBLE 1
#define INTERFACEENTREE1_INFORMATION_TRAITEE 0
#define INTERFACEENTREE1_INACTIVE 0
#define INTERFACEENTREE1_ACTIVE  1
#define INTERFACEENTREE1_PAS_EN_FONCTION 2

/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
} INTERFACEENTREE1;

//Fonctions publiques:
void interfaceEntree1_initialise(void);

//Variables publiques:
extern INTERFACEENTREE1 interfaceEntree1;

#endif
