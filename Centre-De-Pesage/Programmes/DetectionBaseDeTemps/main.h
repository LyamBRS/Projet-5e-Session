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


//define nécessaire 
#define PROCESSUSDETECTION_COMPTEPOURREPONSE_INIT 2000
#define PROCESSUSDETECTION_COMPTEPOURREPONSE_CMD 200

#define PROCESSUSDETECTION_HAUTEUR_DE_SCAN 95
#define PROCESSUSDETECTION_HAUTEUR_RONDELLE -25


#define PILOTETIMER_PERIODE_EN_MS 10
// Define Pour le service Base de Temps
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 2 // A modifier
#define PROCESSUSDETECTION_PHASE 0
#define PROCESSUSBRAS_PHASE 1
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
