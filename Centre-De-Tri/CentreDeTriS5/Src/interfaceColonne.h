#ifndef INTERFACECOLONNE_H
#define INTERFACECOLONNE_H

//MODULE: processusClignotant
//DESCRIPTION: implemente la gestion d'un clignotant en utilise un pointeur de
//fonctions fourni par serviceBaseDeTemps.

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
#define INTERFACECOLONNE_ROUGE 1
#define INTERFACECOLONNE_VERT 2
#define INTERFACECOLONNE_JAUNE 3
    
//Declarations de fonctions privees:


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceColonne_allume(unsigned char couleur);
void interfaceColonne_eteint(unsigned char couleur);
void interfaceColonne_clignote(unsigned char couleur);
void interfaceColonne_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif


