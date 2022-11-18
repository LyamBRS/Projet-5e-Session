#ifndef PILOTEIOT1_H
#define PILOTEIOT1_H

//MODULE: piloteIOT1
//DESCRIPTION: pour commander la sortie IOT1
//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT1_PORT  LD6_GPIO_Port
//#define PILOTEIOT1_SORTIE  LD6_Pin

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteIOT1_initialise(void);
void piloteIOT1_metLaSortieA(unsigned char Valeur);

//Variables publiques:
// pas de variables publiques

#endif
