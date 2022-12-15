/**
 * @file interfaceColonne.h
 * @author Renaud Gagnon
 * @brief 
 * @version 0.1
 * @date 2022-12-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef INTERFACECOLONNE_H
#define INTERFACECOLONNE_H

//MODULE: processusClignotant
//DESCRIPTION: implemente la gestion d'un clignotant en utilise un pointeur de
//fonctions fourni par serviceBaseDeTemps.

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
/**
 * @brief Sert a désigner aux fonction que l'on veut modifier l'état de la lumière rouge.
 * 
 */
#define INTERFACECOLONNE_ROUGE 1

/**
 * @brief Sert a désigner aux fonction que l'on veut modifier l'état de la lumière verte.
 * 
 */
#define INTERFACECOLONNE_VERT 2
/**
 * @brief Sert a désigner aux fonction que l'on veut modifier l'état de la lumière jaune.
 * 
 */
#define INTERFACECOLONNE_JAUNE 3
    
//Declarations de fonctions privees:


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
/**
 * @brief Permet de changer l'état de la lumière voulue à ALLUME.
 * 
 * @param couleur correspondra a la lumière que l'on veut allumer: \ref INTERFACECOLONNE_ROUGE , \ref INTERFACECOLONNE_VERT ou \ref INTERFACECOLONNE_JAUNE.
 */
void interfaceColonne_allume(unsigned char couleur);

/**
 * @brief Permet de changer l'état de la lumière voulue à ETEINT.
 * 
 * @param couleur correspondra a la lumière que l'on veut éteindre: \ref INTERFACECOLONNE_ROUGE , \ref INTERFACECOLONNE_VERT ou \ref INTERFACECOLONNE_JAUNE.
 */
void interfaceColonne_eteint(unsigned char couleur);

/**
 * @brief Permet de changer l'état de la lumière voulue à CLIGNOTER.
 * 
 * @param couleur correspondra a la lumière que l'on veut faire clignoter: \ref INTERFACECOLONNE_ROUGE , \ref INTERFACECOLONNE_VERT ou \ref INTERFACECOLONNE_JAUNE.
 */
void interfaceColonne_clignote(unsigned char couleur);

/**
 * @brief Initialise le module interfaceColonne.
 * 
 */
void interfaceColonne_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif


