#ifndef PILOTEIOT4_H
#define PILOTEIOT4_H

//MODULE: piloteIOT4
//DESCRIPTION: pour commander la sortie IOT4
//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT4_PORT LD5_GPIO_Port
//#define PILOTEIOT4_SORTIE  LD5_Pin

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteIOT4_initialise(void);
void piloteIOT4_metLaSortieA(unsigned char Valeur);

//Variables publiques:
// pas de variables publiques

#endif
