/**
 * @file interfaceColonne.c
 * @author Renaud Gagnon
 * @brief Ce fichier contient le code permettant de gérer la colonne lumineuse, c'est à dire, 
 * des fonctions permettant de changer l'état de chacune des lumières à \ref ALLUME \ref ETEINT ou \ref CLIGNOTE
 * @version 0.1
 * @date 2022-12-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceColonne.h"
#include "piloteColonne.h"
//Definitions privees

#define VITESSECLIGNOTANT 2000 //période en 1/2ms
#define ETEINT 0
#define ALLUME 1
#define CLIGNOTE 2


    
//Declarations de fonctions privees:
//pas de fonctions privées

/**
 * @brief État actuel de la lumière rouge.
 * 
 */
unsigned char etatRouge = ETEINT;

/**
 * @brief État actuel de la lumière verte.
 * 
 */
unsigned char etatVert = ETEINT;

/**
 * @brief État actuel de la lumière Jaune.
 * 
 */
unsigned char etatJaune = ETEINT;

//Definitions de variables privees:


//Definitions de fonctions privees:

/**
 * @brief Cette fonction est appelée par la base de temps pour gérer le clignotement de façon à ce que toutes les lumières qui clignotent soient syncronisées.
 * 
 */
void interfaceColonne_gere(void)
{
  static unsigned int interfaceColonne_compteur = 0;
  interfaceColonne_compteur++;
  if (interfaceColonne_compteur == VITESSECLIGNOTANT/2)
  {
    if (etatRouge == CLIGNOTE)piloteColonne_allume(PILOTECOLONNE_ROUGE);
    if (etatVert == CLIGNOTE)piloteColonne_allume(PILOTECOLONNE_VERT);
    if (etatJaune == CLIGNOTE)piloteColonne_allume(PILOTECOLONNE_JAUNE);
  }
    if (interfaceColonne_compteur >= VITESSECLIGNOTANT)
  {
    if (etatRouge == CLIGNOTE)piloteColonne_eteint(PILOTECOLONNE_ROUGE);
    if (etatVert == CLIGNOTE)piloteColonne_eteint(PILOTECOLONNE_VERT);
    if (etatJaune == CLIGNOTE)piloteColonne_eteint(PILOTECOLONNE_JAUNE);
    interfaceColonne_compteur = 0;
  }
  
  
}

/**
 * @brief Permet de changer l'état de la lumière voulue à ALLUME.
 * 
 * @param couleur correspondra a la lumière que l'on veut allumer: \ref INTERFACECOLONNE_ROUGE , \ref INTERFACECOLONNE_VERT ou \ref INTERFACECOLONNE_JAUNE.
 */
void interfaceColonne_allume(unsigned char couleur)
{
  switch (couleur)
  {
    case (INTERFACECOLONNE_ROUGE):
    etatRouge = ALLUME;
    piloteColonne_allume(PILOTECOLONNE_ROUGE);
    break;
    case (INTERFACECOLONNE_VERT):
    etatVert = ALLUME;
    piloteColonne_allume(PILOTECOLONNE_VERT);
    break;
    case (INTERFACECOLONNE_JAUNE):
    etatJaune = ALLUME;
    piloteColonne_allume(PILOTECOLONNE_JAUNE);
    break;
  }
}

/**
 * @brief Permet de changer l'état de la lumière voulue à ETEINT.
 * 
 * @param couleur correspondra a la lumière que l'on veut éteindre: \ref INTERFACECOLONNE_ROUGE , \ref INTERFACECOLONNE_VERT ou \ref INTERFACECOLONNE_JAUNE.
 */
void interfaceColonne_eteint(unsigned char couleur)
{
  switch (couleur)
  {
    case (INTERFACECOLONNE_ROUGE):
    etatRouge = ALLUME;
    piloteColonne_eteint(PILOTECOLONNE_ROUGE);
    break;
    case (INTERFACECOLONNE_VERT):
    etatVert = ALLUME;
    piloteColonne_eteint(PILOTECOLONNE_VERT);
    break;
    case (INTERFACECOLONNE_JAUNE):
    etatJaune = ALLUME;
    piloteColonne_eteint(PILOTECOLONNE_JAUNE);
    break;
  }
}

/**
 * @brief Permet de changer l'état de la lumière voulue à CLIGNOTE.
 * 
 * @param couleur correspondra a la lumière que l'on veut faire clignoter: \ref INTERFACECOLONNE_ROUGE , \ref INTERFACECOLONNE_VERT ou \ref INTERFACECOLONNE_JAUNE.
 */
void interfaceColonne_clignote(unsigned char couleur)
{
  switch (couleur)
  {
    case (INTERFACECOLONNE_ROUGE):
    etatRouge = CLIGNOTE;
    break;
    case (INTERFACECOLONNE_VERT):
    etatVert = CLIGNOTE;
    break;
    case (INTERFACECOLONNE_JAUNE):
    etatJaune = CLIGNOTE;
    break;
  }
}
//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:

/**
 * @brief Initialise le module interfaceColonne
 * 
 */
void interfaceColonne_initialise(void)
{
  piloteColonne_eteint(PILOTECOLONNE_ROUGE);
  piloteColonne_eteint(PILOTECOLONNE_VERT);
  piloteColonne_eteint(PILOTECOLONNE_JAUNE);
  etatRouge = ETEINT;
  etatVert = ETEINT;
  etatJaune = ETEINT;
  serviceBaseDeTemps_execute[INTERFACECOLONNE_PHASE] =
      interfaceColonne_gere;
}
