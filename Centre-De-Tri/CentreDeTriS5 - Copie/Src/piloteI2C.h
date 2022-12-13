#ifndef PILOTEI2C_H
#define PILOTEI2C_H

#include "main.h"
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
//pas de d�pendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteI2C_Transmit(unsigned char ucAdresse, unsigned char ucDonnee);
void piloteI2C_Receive(unsigned char ucAdresse, unsigned char *ucDonnee);
void piloteI2C_initialise(void);


//Variables publiques:
//pas de variables publiques

#endif
