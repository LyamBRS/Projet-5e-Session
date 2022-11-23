/**
 * @file processusVehicule.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PROCESSUSVEHICULE_H
#define PROCESSUSVEHICULE_H


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles


//INFORMATION PUBLIQUE:
//Definitions publiques:


//Fonctions publiques:
void processusVehicule_initialise(void);

//Variables publiques:

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char requete;
} PROCESSUSVEHICULE;

PROCESSUSVEHICULE processusVehicule;

#endif 
