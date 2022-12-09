#ifndef INTERFACEASCENSEUR_H
#define INTERFACEASCENSEUR_H

//MODULE: interfaceAscenseur
//DESCRIPTION: pour interagir avec ascenseur relie a un STM32F407. 

//HISTORIQUE:
// 2022-12-08, Karl Naudin, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceAscenseur_BaseDeTemps(unsigned char *ucLisBaseTempsAscenseur);
void interfaceAscenseur_Descend(void);
void interfaceAscenseur_Monte(void);
//Variables publiques:
//pas de variables publiques

#endif