/**
 * @file main.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Le programme a pour but de contôler un bras robot et une balance 
 *  avec un beaglebone Blue tout en communiquant les information de ses tâches
 *  au autre module du projet de 5eme session de TSO. La communication se fait 
 *  a l'aide d'un réseau CAN et est gêrer par le \ref ServiceCommunication.h 
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MAIN_H
#define MAIN_H

//HISTORIQUE:
/* Historique du programme gèrer par git et publier sur github au lien suivant
*
*       https://github.com/LyamBRS/Projet-5e-Session.git 
*/

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

//DEFINITIONS REQUISES PAR LE PROGRAMME:

//Dependances materielles:
//pas de dependances materielles

//Dependances logicielles:

/**
 * @brief Définition du baudrate utilisé par \ref piloteSerieUSB.h
 *  nécessite un b au début pour le fonctionnement avec linux  
 */
#define PILOTESERIEUSB_BAUDRATE_AVEC_B_AU_DEBUT   B115200
/**
 * @brief Définition du baudrate utilisé par \ref piloteUSBbal.h
 *  nécessite un b au début pour le fonctionnement avec linux 
 */
#define PILOTEUSBBAL_BAUDRATE_AVEC_B_AU_DEBUT   B9600


//*********** Definition pour le piloteCAN ***************//

//pour utiliser vcan0 pour des tests locaux
//#define PILOTECAN_INTERFACE_VIRTUELLE 
//pour utiliser can0 connecté à un réseau CAN
#define PILOTECAN_INTERFACE_REELLE
//pour utiliser can0 pour recevoir ce qu'on transmet
//#define PILOTECAN_INTERFACE_REELLE_AVEC_LOOPBACK

/**
 * @brief Définition de l'adresse de réception sur le réseau CAN
 *  un 0 fais en sorte que le module recoit tous les trame envoyé sur le CAN
 * 
 */
#define PILOTECAN_ADRESSE_EN_RECEPTION 0x00
/**
 * @brief Définition du masque de l'adresse de réception CAN 
 * 
 */
#define PILOTECAN_MASQUE_EN_RECEPTION 0x00000U
/**
 * @brief Définition de l'adresse de transmition sur le réseau CAN qui
 *   est utilisé par le centre de pesage (décidé par le protocole de com)
 * 
 */
#define PILOIECAN_ADRESSE_EN_TRANSMITION 0x401


//*********** Définition pour le processus detection ***************//

/**
 * @brief Valeur du compteur pour les attentes dans le processus détection
 *  pour attendre la réponse de l'initialisation du bras
 * 
 */
#define PROCESSUSDETECTION_COMPTEPOURREPONSE_INIT 2000
/**
 * @brief Valeur du compteur pour les attentes dans le processus détection
 *  pour attendre la réponse de l'initialisation du bras 
 * 
 */
#define PROCESSUSDETECTION_COMPTEPOURREPONSE_CMD 300

/**
 * @brief Hauteur qui correspond à la coordonné z du bras robot 
 *  lors de la détection d'une rondelle
 * 
 */
#define PROCESSUSDETECTION_HAUTEUR_DE_SCAN 90

/**
 * @brief Définition pour contrôler les requetes du \ref processusDetection.h \n
 *  Utilisé par la structure \ref processusDetection
 */
#define PROCESSUSDETECTION_REQUETE_ACTIVE 1
/**
 * @brief Définition pour contrôler les requetes du \ref processusDetection.h \n
 *  Utilisé par la structure \ref processusDetection
 */
#define PROCESSUSDETECTION_REQUETE_TRAITE 0
/**
 * @brief Définition utilisé pour savoir l'état du module.
 *  Utilisé par la structure \ref processusDetection
 */
#define PROCESSUSDETECTION_MODULE_EN_FONCTION 1
/**
 * @brief Définition utilisé pour savoir l'état du module.
 *  Utilisé par la structure \ref processusDetection
 */
#define PROCESSUSDETECTION_MODULE_PAS_EN_FONCTION 0
/**
 * @brief Définition utilisé pour avoir de l'information du \ref processusDetection.h
 *  Utilisé par la structure \ref processusDetection
 *  Pour savoir si il y a un cube au pas
 */
#define PROCESSUSDETECTION_INFORMATION_CUBEDETECTED 1
/**
 * @brief Définition utilisé pour avoir de l'information du \ref processusDetection.h
 *  Utilisé par la structure \ref processusDetection
 *  Pour savoir si il y a un cube au pas
 */
#define PROCESSUSDETECTION_INFORMATION_CUBENOTDETECTED 0
/**
 * @brief Définition utilisé pour avoir de l'information du \ref processusDetection.h
 *  Utilisé par la structure \ref processusDetection
 *  Pour savoir si il y a un cube au pas
 */
#define PROCESSUSDETECTION_INFORMATION_CUBEUNUSED 2


//*********** Définition pour le processus Pesage ***************//

/**
 * @brief Définition pour savoir si on est en gramme ou en Oz
 */
#define PROCESSUSPESAGE_UNITE_OZ 'o'
/**
 * @brief Définition pour savoir si on est en gramme ou en Oz
 */
#define PROCESSUSPESAGE_UNITE_G 'g'

/**
 * @brief Définition pour contrôler les requetes du \ref processusPesage.h \n
 *  Utilisé par la structure \ref processusPesage
 */
#define PROCESSUSPESAGE_REQUETE_ACTIVE 1
/**
 * @brief Définition pour contrôler les requetes du \ref processusPesage.h \n
 *  Utilisé par la structure \ref processusPesage
 */
#define PROCESSUSPESAGE_REQUETE_TRAITE 0

/**
 * @brief Définition utilisé pour savoir l'état du module.
 *  Utilisé par la structure \ref processusPesage
 */
#define PROCESSUSPESAGE_MODULE_EN_FONCTION 1
/**
 * @brief Définition utilisé pour savoir l'état du module.
 *  Utilisé par la structure \ref processusPesage
 */
#define PROCESSUSPESAGE_MODULE_PAS_EN_FONCTION 0



//*********** Définition pour la Base De Temps ***************//

/**
 * @brief Définition pour la période du pilote Timer. C'est le temps 
 *  entre chaque apelle de sa fonction handler qui elle meme appelle le
 *  \ref serviceBaseDeTemps.h 
 */
#define PILOTETIMER_PERIODE_EN_MS 5
/**
 * @brief Période de la base de temps en Milisecondes.
 */
#define SERVICEBASEDETEMPS_PERIODE_EN_MS PILOTETIMER_PERIODE_EN_MS
/**
 * @brief Fréquence de la base de temps en Hz. Doit être recalculé si la
 *  période du pilote timer \ref PILOTETIMER_PERIODE_EN_MS est changé.
 */
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ 200

/**
 * @brief Nombre de phase de la base de temps \ref serviceBaseDeTemps.h
 * 
 */
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 5
/**
 * @brief Numéro de la phase du processus Détection  
 * 
 */
#define PROCESSUSDETECTION_PHASE 0
/**
 * @brief Numéro de la phase du processus Pesage 
 * 
 */
#define PROCESSUSPESAGE_PHASE 1

// Service communication phase 2 et 3

/**
 * @brief  Numéro de la phase du processus de Gestion de COM
 * 
 */
#define PROCESSUSGESTIONCOM_PHASE 4
/**
 * @brief Nombre de phase dans une période de la base de temps (1 si pas utilisé)
 */
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:

int main(void);

//Variables publiques:
//pas de variables publiques

#endif
