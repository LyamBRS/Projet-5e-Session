#ifndef PILOTEIOT3_H
#define PILOTEIOT3_H

//MODULE: piloteIOT3
//DESCRIPTION: pour commander la sortie IOT3
//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT3_PORT LD4_GPIO_Port
//#define PILOTEIOT3_SORTIE  LD4_Pin

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteIOT3_initialise(void);
void piloteIOT3_metLaSortieA(unsigned char Valeur);

//Variables publiques:
// pas de variables publiques

#endif
