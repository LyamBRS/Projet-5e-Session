/**
 * @file xmain.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief This file contains the inclusion needed for the code to wok
 *       Le main est nécessaire pour les includions global
 *      Contien les defines essentiel au fonctionnement
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
// 2022-04-11, Yves Roy: création

//inclusions globales

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles:
#define PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
#define PILOTEENTREE1_BROCHE 34
#define PILOTEIOT1_BROCHE 13
#define PILOTEIOT1_ETAT_INITIAL_A_ZERO


// Define pour pilote Feu de Position
#define PILOTEIOFEUAVANTD_BROCHE 27  // A définir
#define PILOTEIOFEUAVANTD_ETAT_INITIAL_A_ZERO
#define PILOTEIOFEUAVANTG_BROCHE 15  // A définir
#define PILOTEIOFEUAVANTG_ETAT_INITIAL_A_ZERO
#define PILOTEIOFEUARRIERED_BROCHE 12  // A définir
#define PILOTEIOFEUARRIERED_ETAT_INITIAL_A_ZERO
#define PILOTEIOFEUARRIEREG_BROCHE 33  // A définir
#define PILOTEIOFEUARRIEREG_ETAT_INITIAL_A_ZERO


// Define pour pilote Benne
#define PILOTEMOTEURBENNE_BROCHE 4  // A définir
#define PILOTEMOTEURBENNE_ETAT_INITIAL_A_ZERO



// Define pour pilotes PWM
#define PILOTEPWM_RESOLUTION 8  
#define PILOTEPWM_FREQUENCE 5000

#define  PILOTEPWMDROITHAUT_CHANNEL 0
#define  PILOTEPWMDROITHAUT_PIN 14
#define  PILOTEPWMDROITBAS_CHANNEL 1
#define  PILOTEPWMDROITBAS_PIN 32
#define  PILOTEPWMGAUCHEHAUT_CHANNEL 2
#define  PILOTEPWMGAUCHEHAUT_PIN 26
#define  PILOTEPWMGAUCHEBAS_CHANNEL 3
#define  PILOTEPWMGAUCHEBAS_PIN 25

#define PILOTEI2C1_SCL    19
#define PILOTEI2C1_SDA    18
#define PILOTEI2C1_FREQUENCE_D_HORLOGE_EN_HZ 400000

// Define pour les interfaces
#define INTERFACEENTREE1_VALEUR_LUE_SI_ACTIVE  0   
#define INTERFACEENTREE1_VALEUR_LUE_SI_INACTIVE 1
#define INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ  125
#define INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10
#define INTERFACET1_VALEUR_POUR_ALLUMER  1   
#define INTERFACET1_VALEUR_POUR_ETEINDRE 0

#define INTERFACESUIVEUR_ADRESSE 0x32  // A définir

#define INTERFACEMOTEURBENNE_VALEUR_POUR_ALLUMER 1
#define INTERFACEMOTEURBENNE_VALEUR_POUR_ETEINDRE 0

//Dependances logicielles:
#define SERVICETASKSERVER_PERIODE_EN_US (4000L)
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ ((1000000L)/SERVICETASKSERVER_PERIODE_EN_US)
#define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS 500
#define PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS 500
#define PROCESSUSMOTEURPASAPAS_TEMPS_PAR_COMMANDE_EN_MS 8

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 3
#define INTERFACEENTREE1_PHASE 0
#define PROCESSUSMOTEURPASAPAS_PHASE 1
#define PROCESSUSCLIGNOTANT_PHASE 2


#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Variables publiques:
//pas de variables publiques

//Fonctions publiques:
//pas de fonctions publiques

#endif
