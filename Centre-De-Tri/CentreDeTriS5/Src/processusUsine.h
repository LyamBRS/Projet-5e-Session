/**
 * @file processusUsine.h
 * @author Renaud Gagnon
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PROCESSUSUSINE_H
#define PROCESSUSUSINE_H

#include "main.h"

//HISTORIQUE:
// 2018-10-28, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSBOUTONCONNECTE_TEMPS_MAXIMAL_POUR_RECEVOIR_EN_MS 100
//#define PROCESSUSBOUTONCONNECTE_PHASE 0


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:

void processusUsine_gere (void);
void processusUsine_initialise(void);
void processusUsine_operation (void);
void processusUsine_attente (void);
void processusUsine_arret (void);
void processusUsine_tests (void);
//Variables publiques:
//pas de variables publiques

#endif
