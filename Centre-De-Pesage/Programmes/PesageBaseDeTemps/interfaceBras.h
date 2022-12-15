/**
 * @file interfaceBras.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * 
 * @brief Interface qui utilise le \ref piloteSerieUSB.h pour parler en Gcode
 *  avec le bras robot du projet de 5eme Session de TSO.
 * 
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef INTERFACEBRAS_H
#define INTERFACEBRAS_H

//PROGRAMME: 247-616 L-0002
//DESCRIPTION: Programme qui permet de tester le module interfaceMalyan
//Le programme permet de tester la communication avec une imprimante 3d
//de type MALYAN M200.
//Appuyer sur la touche:
//6: fait tourner le ventilateur (commande M106)
//7: arrête le ventilateur (commande M107)
//x: x transmet une commande inconnue (commande x000)
//Q: termine le programme
//Si la commande est complétée, l'imprimante retourne:
//  ok N0 P15 B15\n
//Si la commande est inconnue, l'imprimante retourne:
//  echo:Unknown command: "x000"\n
//  ok N0 P15 B15\n
//Pour plus de détails a propos de la configuration du port USB/Serie:
//https://en.wikibooks.org/wiki/Serial_Programming/termios

//HISTORIQUE:
// 2018-10-11, Yves Roy: creation
// 2020-09-06, Yves Roy: reception amelioree

//DEFINITIONS REQUISES PAR LE PROGRAMME:

//Dependances materielles:
//pas de dependances materielles

//Dependances logicielles:

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
/**
 * @brief Fonciton de l'interface Bras qui permet de lui envoyé une commande
 *  avec le \ref piloteSerieUSB.h
 * 
 * @param Commande Le tableau de charactère qui contient la commande a envoyé 
 * @param Longueur La longueur du tableau de charactère qui est passé en paramètre
 * @return int: pour savoir si il y a eu un erreur dans la transmition
 */
int interfaceBras_ecritUneCommande(char *Commande, unsigned char Longueur);
/**
 * @brief Fonciton de l'interface Bras qui permet lire une commande envoyé 
 *  par le bras avec le \ref piloteSerieUSB.h
 * 
 * @param Reponse Un pointeur sur le tableau de charactère ou va etre stocker la réponse
 * @param LongueurMaximale Longeur maximal en characère de la réponse
 * @return int: pour savoir si il y a eu un erreur dans la réception
 */
int interfaceBras_recoitUneReponse(char *Reponse, unsigned int LongueurMaximale);
/**
 * @brief Fonction qui initilise le pilote USB pour la communication avec le bras
 * 
 * @return int 
 */
int interfaceBras_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
