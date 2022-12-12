/**
 * @file processusVehicule.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Processus qui gere le véhicule du projet de 5eme session de TSO.
 *  Le \ref xprocessusVehicule.h gere les requetes de transport de rondelles 
 *  envoyé par les autres modules du projet. Il utilise le \ref ServiceCommunication.h
 *  ainsi que sa structure \ref ModuleData pour savoir quand conduire les rondelles.
 *  
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
  /// @brief permet de savoir état du module: En fonction ou pas
  unsigned char etatDuModule;
  /// @brief permet de savoir si il y a des informations disponible 
  unsigned char information;
  /// @brief Permet d'activer une requête et de savoir quand elle est traité
  unsigned char requete;
} PROCESSUSVEHICULE;
/**
 * @brief Structure publique permettant de gere l'état du module ainsi que ses requêtes
 */
PROCESSUSVEHICULE processusVehicule;

#endif 
