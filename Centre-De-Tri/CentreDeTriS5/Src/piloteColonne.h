#ifndef PILOTECOLONNE_H
#define PILOTECOLONNE_H

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
#define PILOTECOLONNE_ROUGE 1
#define PILOTECOLONNE_VERT 2
#define PILOTECOLONNE_JAUNE 3

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteColonne_initialise(void);
void piloteColonne_allume(unsigned char couleur);
void piloteColonne_eteint(unsigned char couleur);

//Variables publiques:
// pas de variables publiques

#endif
