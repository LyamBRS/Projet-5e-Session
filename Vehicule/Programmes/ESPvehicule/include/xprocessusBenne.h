/**
 * @file xprocessusBenne.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * 
 * @brief Le processus Benne est un State Machine qui gêre les requêtes 
 *  de déchargement de la benne et sa calibrartion.
 * 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PROCESSUSBENNE_H
#define PROCESSUSBENNE_H

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

/**
 * @brief Fonction qui initialise le State Machine du processus Benne.
 *  
 */
void processusBenne_initialise(void);

//Variables publiques:

typedef struct
{
  /**
   * @brief Variable fesant partie de la structure \ref processusBenne
   *  servant a savoir l'état du module: \n 
   *  \ref PROCESSUSBENNE_MODULE_PAS_EN_FONCTION \n
   *  \ref PROCESSUSBENNE_MODULE_EN_FONCTION
   */
  unsigned char etatDuModule;  
  /**
   * @brief Variable fesant partie de la structure \ref processusBenne
   *  servant a savoir si il y a de l'information disponnible.
   */
  unsigned char information;
  /**
   * @brief Variable fesant partie de la structure \ref processusBenne
   *  servant a contrôler les requêtes de déchargement de la benne: \n 
   *  \ref PROCESSUSBENNE_REQUETE_TRAITE \n
   *  \ref PROCESSUSBENNE_REQUETE_ACTIVE
   */
  unsigned char requete;
} PROCESSUSBENNE;

/**
 * @brief Structure publique qui permet d'avoir des informations sur
 *   le processus Benne et d'activer des requêtes.
 * 
 */
PROCESSUSBENNE processusBenne;

#endif
