/**
 * @file xprocessusConduite.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * 
 * @brief Le processus Conduite est une phase du service base de temps qui est appeler 
 *  à chaques périodes de la base de temps. Cela permet de démarrer une requête de conduite
 *  depuis un autre processus quand il est nécessaire. Le processus conduite a pour but de
 *  suivre la ligne noir installé au sol pour le projet de 5e session de TSO. Il utilise le \ref
 *  xserviceTank.h ainsi que \ref xinterfaceSuiveur.h pour conduire le vehicule et détecter 
 *  l'arrivé a destination.
 * 
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

/// @brief Fonction publique d'initialisation du Processus Conduite 
/// @param  void
void processusConduite_initialise(void);

//Variables publiques:

typedef struct
{ 
  /**
   * @brief Permet de savoir l'état du module:  \n
   *  \ref PROCESSUSCONDUITE_MODULE_ARRIVE_PESAGE  \n
   *  \ref PROCESSUSCONDUITE_MODULE_ARRIVE_TRI  \n
   *  \ref PROCESSUSCONDUITE_MODULE_EN_DEPLACEMENT  \n
   *  \ref PROCESSUSCONDUITE_MODULE_PAS_EN_FONCTION
   */
  unsigned char etatDuModule;  
  /// @brief permet de savoir si il y a des informations disponible 
  unsigned char information;
  /// @brief Permet d'activer une requête et de savoir quand elle est traité
  unsigned char requete;
  /// @brief Permet de savoir quel était son dernier état pour ne pas avoir d'erreur
  unsigned char dernierArrive;
} PROCESSUSCONDUITE;
/**
 * @brief Structure publique permettant de gere l'état du module ainsi que ses requêtes
 */
PROCESSUSCONDUITE processusConduite;

#endif
