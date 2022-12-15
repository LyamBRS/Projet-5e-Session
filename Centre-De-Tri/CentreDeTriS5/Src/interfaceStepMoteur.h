/**
 * @file interfaceStepMoteur.h
 * @author Renaud Gagnon
 * @brief Fichier contenant le code qui permet d'utiliser l'ascenceur du centre de tri. 
 * Ce fichier a été créer pour remplacer les fichier d'interface de l'ascenseur de Karl parce-que ceux-ci ne fonctionnent pas.
 * @version 0.1
 * @date 2022-12-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef INTERFACESTEPMOTEUR_H
#define INTERFACESTEPMOTEUR_H

//MODULE: interface step moteur
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

#define INTERFACESTEPMOTEUR_POSITION_BASSE 1
#define INTERFACESTEPMOTEUR_POSITION_HAUTE 2
//pas de definitions publiques

//Fonctions publiques:
void interfaceStepMoteur_gere(void);
void interfaceStepMoteur_requete(unsigned char requete);
void interfaceStepMoteur_initialise(void);
void interfaceStepMoteur_home(void);
unsigned char interfaceStepMoteur_getPos(void);
//Variables publiques:
//pas de variables publiques

#endif
