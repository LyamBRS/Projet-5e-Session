/**
 * @file processusPesage.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * 
 * @brief Le processus Pesage gêre l'entièreté des tâche a effectué avec 
 *  le centre de pesage. Il est une phase du service base de temps qui est appeler 
 *  à chaques périodes de la base de temps. Il correspond au diagramme d'état 
 * 
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Processus Detection.h
#ifndef PROCESSUSPESAGE_H
#define PROCESSUSPESAGE_H


/**
 * @brief Fonction publique d'initialisation du Processus Pesage
 *  
 */
void processusPesage_initialise(void);

//Structutre Publique pour l'acces au module
typedef struct
{
  /**
   * @brief Permet de savoir l'état du module:  \n
   *  \ref PROCESSUSCONDUITE_MODULE_EN_FONCTION \n
   *  \ref PROCESSUSCONDUITE_MODULE_PAS_EN_FONCTION
   */
  unsigned char etatDuModule;
  /// @brief permet de savoir si il y a des informations disponible 
  unsigned char information;
  /// @brief Permet d'activer une requête et de savoir quand elle est traité
  unsigned char requete;
  /// @brief Permet de savoir si on est en Métric ou en Impérial
  unsigned char unite;
  int weight;
} PROCESSUSPESAGE;

/**
 * @brief Structure publique permettant de gere l'état du module ainsi que ses requêtes
 */
PROCESSUSPESAGE processusPesage;



#endif