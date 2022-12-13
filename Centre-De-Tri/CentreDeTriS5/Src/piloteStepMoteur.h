#ifndef PILOTESTEPMOTEUR_H
#define PILOTESTEPMOTEUR_H

//MODULE: piloteIOB1
//DESCRIPTION: pour lire l'entree IOB1
//HISTORIQUE:
// 2018-09-08, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
#define PILOTESTEPMOTEUR_STEP0
#define PILOTESTEPMOTEUR_STEP1
#define PILOTESTEPMOTEUR_STEP2
#define PILOTESTEPMOTEUR_STEP3
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOB1_PORT B1_GPIO_Port
//#define PILOTEIOB1_ENTREE  B1_Pin    

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de d�pendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteStepMoteur_initialise(void);
void piloteStepMoteur_EcritSortie(unsigned char ucStep);

//Variables publiques:
//pas de variables publiques

#endif
