#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: 247-616 L-0002
//DESCRIPTION: 

//Pour plus de détails a propos de la configuration du port USB/Serie:
//https://en.wikibooks.org/wiki/Serial_Programming/termios

//HISTORIQUE:
// 2018-10-11, Yves Roy: creation
// 2020-09-06, Yves Roy: reception amelioree


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
#define PILOTESERIEUSB_BAUDRATE_AVEC_B_AU_DEBUT   B115200
#define PILOTEUSBBAL_BAUDRATE_AVEC_B_AU_DEBUT   B9600
// Definition pour le piloteCAN 
//pour utiliser vcan0 pour des tests locaux
//#define PILOTECAN_INTERFACE_VIRTUELLE 
//pour utiliser can0 connecté à un réseau CAN
#define PILOTECAN_INTERFACE_REELLE
//pour utiliser can0 pour recevoir ce qu'on transmet
//#define PILOTECAN_INTERFACE_REELLE_AVEC_LOOPBACK
#define PILOTECAN_ADRESSE_EN_RECEPTION 0x00 //(0 pour tout recevoir)
#define PILOTECAN_MASQUE_EN_RECEPTION 0x00000U //(0 pour ne pas filtrer)
#define PILOIECAN_ADRESSE_EN_TRANSMITION 0x401

//define nécessaire pour le processus detection
#define PROCESSUSDETECTION_COMPTEPOURREPONSE_INIT 2000
#define PROCESSUSDETECTION_COMPTEPOURREPONSE_CMD 200

#define PROCESSUSDETECTION_HAUTEUR_DE_SCAN 90
#define PROCESSUSDETECTION_HAUTEUR_RONDELLE -25
#define PROCESSUSDETECTION_REQUETE_ACTIVE 1
#define PROCESSUSDETECTION_REQUETE_TRAITE 0
#define PROCESSUSDETECTION_MODULE_EN_FONCTION 1
#define PROCESSUSDETECTION_MODULE_PAS_EN_FONCTION 0


// define nécessaire au processus Pesage
#define PROCESSUSPESAGE_REQUETE_ACTIVE 1
#define PROCESSUSPESAGE_REQUETE_TRAITE 0
#define PROCESSUSPESAGE_MODULE_EN_FONCTION 1
#define PROCESSUSPESAGE_MODULE_PAS_EN_FONCTION 0


#define PILOTETIMER_PERIODE_EN_MS 5
#define SERVICEBASEDETEMPS_PERIODE_EN_MS PILOTETIMER_PERIODE_EN_MS
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ 200  // ATTENTION A CHANGER EN MEME TEMPS QUE LA PERIODE
// Define Pour le service Base de Temps
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 4 // A modifier
#define PROCESSUSDETECTION_PHASE 0
#define PROCESSUSPESAGE_PHASE 1
// Service communication phase 2 et 3

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1




//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
int main(void);

//Variables publiques:
//pas de variables publiques

#endif
