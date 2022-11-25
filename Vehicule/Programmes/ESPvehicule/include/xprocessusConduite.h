/**
 * @file xprocessusConduite.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PROCESSUSCONDUITE_H
#define PROCESSUSCONDUITE_H


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void processusConduite_initialise(void);

//Variables publiques:

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char requete;
} PROCESSUSCONDUITE;

PROCESSUSCONDUITE processusConduite;

#endif
