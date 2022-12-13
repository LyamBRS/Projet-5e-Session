#ifndef PILOTEIOB1_H
#define PILOTEIOB1_H

//MODULE: piloteIOB1
//DESCRIPTION: pour lire l'entree IOB1
//HISTORIQUE:
// 2018-09-08, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOB1_PORT B1_GPIO_Port
//#define PILOTEIOB1_ENTREE  B1_Pin    

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteIOB1_initialise(void);
unsigned char piloteIOB1_litLEntree(void);

//Variables publiques:
//pas de variables publiques

#endif
