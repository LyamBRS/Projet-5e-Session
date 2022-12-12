/**
 * @file xmain.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * 
 * @brief Le fichier xmain.h est nécessaire pour les includions global qui
 *   contien les defines essentiel au fonctionnement du véhicule 
 *  fesant partie du projet de 5e session de TSO. Le processeur utilisé
 *  pour la gestion du véhicule est un ESP32. Voir le document de projet
 *  pour plus d'information sur le fonctionnement du véhicule. 
 *      
 *  Le programme suivant fonctionne avec une base de temps et des machine d'état.
 *  Le processus principale du programme est le \ref xprocessusVehicule.h 
 * 
 *   
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: ESP véhicule Projet 5e Session
//DESCRIPTION: programme qui sert de base pour l'introduction au HTML, Javascript, etc

//HISTORIQUE:
/* Historique du programme gèrer par git et publier sur github au lien suivant
*
*       https://github.com/LyamBRS/Projet-5e-Session.git 
*/
  
//  *** INFORMATION PUBLIQUE ***


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles:

/**
 * @brief Définition pour choisir le mode de lecture de PIN
 * 
 */
#define PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
/**
 * @brief Définition qui undique le numéro de broche du ESP32 utilisé par l'entrée1
 * 
 */
#define PILOTEENTREE1_BROCHE 34
/**
 * @brief Définition qui assigne le bon numéro de broche du ESP32 au témoin 1
 * 
 */
#define PILOTEIOT1_BROCHE 13
/**
 * @brief Définition qui permet de modifier un état initiale au témoin 1
 * 
 */
#define PILOTEIOT1_ETAT_INITIAL_A_ZERO

//*** Define pour pilote Feu de Position ***//

#define PILOTEIOFEUAVANTD_BROCHE 27  // A définir
#define PILOTEIOFEUAVANTD_ETAT_INITIAL_A_ZERO
#define PILOTEIOFEUAVANTG_BROCHE 15  // A définir 
#define PILOTEIOFEUAVANTG_ETAT_INITIAL_A_ZERO
#define PILOTEIOFEUARRIERED_BROCHE 12  // A définir
#define PILOTEIOFEUARRIERED_ETAT_INITIAL_A_ZERO
#define PILOTEIOFEUARRIEREG_BROCHE 33  // A définir
#define PILOTEIOFEUARRIEREG_ETAT_INITIAL_A_ZERO

//*** Define pour pilote Benne ***//
/**
 * @brief Définition qui assigne le bon numéro de broche du ESP32 au 
 *  HAUT du pont en H du moteur de la benne. Le moteur peut être alimenté
 *  dans les deux sens pour tourner dans le sens horaire ou antihoraire
 * 
 */
#define PILOTEMOTEURBENNEHAUT_BROCHE 4
/**
 * @brief Définition qui assigne le bon numéro de broche du ESP32 au 
 *  BAS du pont en H du moteur de la benne. Le moteur peut être alimenté
 *  dans les deux sens pour tourner dans le sens horaire ou antihoraire
 * 
 */
#define PILOTEMOTEURBENNEBAS_BROCHE 21
/**
 * @brief Définition qui permet de modifier un état initiale au moteur de la benne 
 *   \ref PILOTEMOTEURBENNE_ETAT_INITIAL_A_ZERO éteint le moteur \n
 *   \ref PILOTEMOTEURBENNE_ETAT_INITIAL_A_UN allume le moteur  
 * 
 */
#define PILOTEMOTEURBENNE_ETAT_INITIAL_A_ZERO

//*** Define pour pilotes PWM ***//
/**
 * @brief Défini le nombre de bits utilisé pour la résolution du PWM
 *  
 */
#define PILOTEPWM_RESOLUTION 8  
/**
 * @brief Défini la fréquence du PWM en Hz
 * 
 */
#define PILOTEPWM_FREQUENCE 5000
/**
 * @brief Définition qui assigne un channel PWM a son pilote respectif
 * 
 */
#define  PILOTEPWMDROITHAUT_CHANNEL 0
/**
 * @brief Défini le numéro de broche du ESP32 a au \ref xpilotePWMDroitHaut.h
 */
#define  PILOTEPWMDROITHAUT_PIN 14
/**
 * @brief Définition qui assigne un channel PWM a son pilote respectif
 * 
 */
#define  PILOTEPWMDROITBAS_CHANNEL 1
/**
 * @brief Défini le numéro de broche du ESP32 a au \ref xpilotePWMDroitBas.h
 */
#define  PILOTEPWMDROITBAS_PIN 32
/**
 * @brief Définition qui assigne un channel PWM a son pilote respectif
 * 
 */
#define  PILOTEPWMGAUCHEHAUT_CHANNEL 2
/**
 * @brief Défini le numéro de broche du ESP32 a au \ref xpilotePWMGaucheHaut.h
 */
#define  PILOTEPWMGAUCHEHAUT_PIN 26
/**
 * @brief Définition qui assigne un channel PWM a son pilote respectif
 * 
 */
#define  PILOTEPWMGAUCHEBAS_CHANNEL 3
/**
 * @brief Défini le numéro de broche du ESP32 a au \ref xpilotePWMGaucheBas.h
 */
#define  PILOTEPWMGAUCHEBAS_PIN 25

/*** DEFINITION DU PILOTE I2C ***/
/**
 * @brief Définition qui assigne le bon numéro de broche à la ligne SCL du \ref xpiloteI2C1.h
*/
#define PILOTEI2C1_SCL    22
/**
 * @brief Définition qui assigne le bon numéro de broche à la ligne SDA du \ref xpiloteI2C1.h
*/
#define PILOTEI2C1_SDA    23
/**
 * @brief Défini la fréquence en Hz de l'horloge I2C
 * 
 */
#define PILOTEI2C1_FREQUENCE_D_HORLOGE_EN_HZ 400000

//*** Define pour les interfaces ***//

/**
 * @brief Défini la valeur lu quand l'entré 1 est active (quand la switch est pesé)
 */
#define INTERFACEENTREE1_VALEUR_LUE_SI_ACTIVE  0   
/**
 * @brief Défini la valeur lu quand l'entré 1 est inactive (quand la switch est relaché)
 */
#define INTERFACEENTREE1_VALEUR_LUE_SI_INACTIVE 1
/**
 * @brief Défini la fréquence en Hz des lectures de l'entré 1 
 * 
 */
#define INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ  125
/**
 * @brief Défini le nombre de lectures de l'entré avant d'avoir une valeur fiable
 * 
 */
#define INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

/** Définition pour le témoin 1 **/
/**
 * @brief Valeur pour allumer le témoin 1
 */
#define INTERFACET1_VALEUR_POUR_ALLUMER  1
/**
 * @brief Valeur pour éteindre le témoin 1
 */
#define INTERFACET1_VALEUR_POUR_ETEINDRE 0


/** Définition pour le suiveur de ligne **/
/**
 * @brief Adresse I2C du PCF8574 utilisé par le suiveur de ligne installé sur le camion
*/
#define INTERFACESUIVEUR_ADRESSE 0x3A

/** Définition pour le moteur de la Benne **/
/**
 * @brief Valeur pour allumer le moteur de la benne
*/
#define INTERFACEMOTEURBENNE_VALEUR_POUR_ALLUMER 1
/**
 * @brief Valeur pour éteindre le moteur de la benne
*/
#define INTERFACEMOTEURBENNE_VALEUR_POUR_ETEINDRE 0


/***  DÉFINITION NÉCESSAIRE À LA BASE DE TEMPS  ***/
/**
 * @brief Période en microsecondes à laquelle le TaskServer exécute sa fonction 
 *  qui fait apelle au service Base de temps pour gêrer plusieur tache a la fois
 * 
 */
#define SERVICETASKSERVER_PERIODE_EN_US (1000L)
/**
 * @brief Fréquence en Hz de la base de temps
 * 
 */
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ 1000
/**
 * @brief Nombre de phase dans une période de la base de temps (1 si pas utilisé)
 */
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1
/**
 * @brief Nombre de phase de la base de temps \ref xserviceBaseDeTemps.h
 * 
 */
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 7

// Phase 0 et 1 sont utilisé et défini par ServiceCommunication.h

/**
 * @brief Numéro de phase la lecture de l'Entrée 1 
 */
#define INTERFACEENTREE1_PHASE 4
/**
 * @brief Numéro de phase du processus de gestion de la benne
 */
#define PROCESSUSBENNE_PHASE 5
/**
 * @brief Numéro de phase du processus clignotant
 */
#define PROCESSUSCLIGNOTANT_PHASE 2
/**
 * @brief Numéro de phase du processus Conduite 
 */
#define PROCESSUSCONDUITE_PHASE 3
/**
 * @brief Numéro de phase du processus principale de gestion du véhicule 
 */
#define PROCESSUSVEHICULE_PHASE 6

#define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS 500
#define PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS 500

/***  Définition du processus Conduite  ***/

/**
 * @brief Vitesse standard des moteur du véhicule correspond a un PWM sur le nombre 
 *  de bits défini par \ref PILOTEPWM_RESOLUTION 
 */
#define PROCESSUSCONDUITE_VITESSESTANDARD 200
/**
 * @brief Définition pour contrôler les requetes du \ref xprocessusConduite.h \n
 *  Utilisé par la structure \ref processusConduite
 */
#define PROCESSUSCONDUITE_REQUETE_ACTIVE 1
/**
 * @brief Définition pour contrôler les requetes du \ref xprocessusConduite.h \n
 *  Utilisé par la structure \ref processusConduite
 * 
 */
#define PROCESSUSCONDUITE_REQUETE_TRAITE 0
/**
 * @brief Définition utilisé pour savoir l'état du module.
 *  Utilisé par la structure \ref processusConduite
 */
#define PROCESSUSCONDUITE_MODULE_PAS_EN_FONCTION 0
/**
 * @brief Définition utilisé pour savoir l'état du module.
 *  Utilisé par la structure \ref processusConduite
 */
#define PROCESSUSCONDUITE_MODULE_EN_DEPLACEMENT 1
/**
 * @brief Définition utilisé pour savoir l'état du module. 
 *  Utilisé par la structure \ref processusConduite
 */
#define PROCESSUSCONDUITE_MODULE_ARRIVE_TRI 2
/**
 * @brief Définition utilisé pour savoir l'état du module.
 *  Utilisé par la structure \ref processusConduite
 */
#define PROCESSUSCONDUITE_MODULE_ARRIVE_PESAGE 3
/**
 * @brief Définition utilisé pour savoir le dernier état du module
 *  Utilisé par la structure \ref processusConduite
 */
#define PROCESSUSCONDUITE_DERNIERETAT_PESAGE 8
/**
 * @brief Définition utilisé pour savoir le dernier état du module
 *  Utilisé par la structure \ref processusConduite
 */
#define PROCESSUSCONDUITE_DERNIERETAT_TRI 9



/***  Définition pour le Processus gestion de la Benne  ***/
/**
 * @brief Définition pour contrôler les requetes du \ref xprocessusBenne.h 
 * 
 */
#define PROCESSUSBENNE_REQUETE_ACTIVE 1
/**
 * @brief Définition pour contrôler les requetes du \ref xprocessusBenne.h 
 * 
 */
#define PROCESSUSBENNE_REQUETE_TRAITE 0
/**
 * @brief Définition utilisé pour savoir l'état du module 
 */
#define PROCESSUSBENNE_MODULE_EN_FONCTION 1
/**
 * @brief Définition utilisé pour savoir l'état du module 
 */
#define PROCESSUSBENNE_MODULE_PAS_EN_FONCTION 0

#endif