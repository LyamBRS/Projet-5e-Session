#ifndef PILOTEIOT2_H
#define PILOTEIOT2_H

//MODULE: piloteIOT2
//DESCRIPTION: pour commander la sortie IOT2
//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT2_PORT  LD6_GPIO_Port
//#define PILOTEIOT2_SORTIE  LD3_Pin

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteIOT2_initialise(void);
void piloteIOT2_metLaSortieA(unsigned char Valeur);

//Variables publiques:
// pas de variables publiques

#endif
