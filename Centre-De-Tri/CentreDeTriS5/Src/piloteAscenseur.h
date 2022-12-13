#ifndef PILOTEASCENSEUR_H
#define PILOTEASCENSEUR_H

//MODULE: piloteAscenseur
//DESCRIPTION: pour commander les sortie du triac
//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT1_PORT  LD6_GPIO_Port
//#define PILOTEIOT1_SORTIE  LD6_Pin

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de d�pendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteIOT1_initialise(void);
void piloteIOT1_metLaSortieA(unsigned char Valeur);

//Variables publiques:
// pas de variables publiques

#endif
