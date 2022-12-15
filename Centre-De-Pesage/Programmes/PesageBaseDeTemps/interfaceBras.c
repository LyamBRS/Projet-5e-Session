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

#include "main.h"
#include "interfaceBras.h"
#include "piloteSerieUSB.h"

/**
 * @brief Tableau de charactère pour mettre la réponse d'initialisation du bras
 * 
 */
char reponseinit[3000];

/**
 * @brief Fonciton de l'interface Bras qui permet de lui envoyé une commande
 *  avec le \ref piloteSerieUSB.h
 * 
 * @param Commande Le tableau de charactère qui contient la commande a envoyé 
 * @param Longueur La longueur du tableau de charactère qui est passé en paramètre
 * @return int: pour savoir si il y a eu un erreur dans la transmition
 */
int interfaceBras_ecritUneCommande(char *Commande, unsigned char Longueur)
{
int retour;
  retour = piloteSerieUSB_ecrit(Commande, Longueur);
  if (retour != (int)Longueur)
  {
    return -1;
  }
  piloteSerieUSB_attendLaFinDeLEcriture();
  return retour;
}
/**
 * @brief Fonciton de l'interface Bras qui permet lire une commande envoyé 
 *  par le bras avec le \ref piloteSerieUSB.h
 * 
 * @param Reponse Un pointeur sur le tableau de charactère ou va etre stocker la réponse
 * @param LongueurMaximale Longeur maximal en characère de la réponse
 * @return int: pour savoir si il y a eu un erreur dans la réception
 */
int interfaceBras_recoitUneReponse(char *Reponse, unsigned int LongueurMaximale)
{
  return piloteSerieUSB_lit(Reponse, LongueurMaximale);  
}

/**
 * @brief Fonction qui initilise le pilote USB pour la communication avec le bras
 * 
 * @return int 
 */
int interfaceBras_initialise(void)
{
    if(piloteSerieUSB_initialise() < 0)
    {
      return -1;
    }
    return 0;
}