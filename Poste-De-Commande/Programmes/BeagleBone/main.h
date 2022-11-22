#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: testPiloteCAN
//DESCRIPTION: programme qui permet de tester le module piloteSortie1

//note:
//Pour tester le programme en mode CAN virtuel avec vcan0
//- compilez en définissant CAN_VIRTUAL_INTERFACE dans main.h
//- ouvrez un premier terminal
//- ouvrez un deuxième terminal
//- terminal 1: lancez le programme en faisant: sudo ./piloteCAN
//- terminal 2: entrez: candump vcan0 &
//- terminal 1: faite 'enter'
//- terminal 1: prenez connaissance du message qui a été transmis par le programme
//- terminal 1: vérifiez que le programme indique qu'il attend une réponse
//- terminal 2: vérifiez que le message transmis s'est affiché à l'écran
//- terminal 2: transmettez un message au programme en faisant: cansend 123#4567
//- terminal 1: vérifiez que le message transmis s'est affiché à l'écran
//- terminal 1: entrez 'Q' pour quitter
//- terminal 2: vérifiez que le programme candump s'est arrêté

//Si le programme indique "RTNETLINK answers: File exists" une fois lancé,
//entrez 'Q' pour fermer l'interface CAN correctement et relancez le programme

//======================================================== HISTORY // 
// 2021-10-28, Yves Roy: création

//--------------------------- Includes ---------------------------// globales
//pas d'inclusions globales

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles:
//pour utiliser vcan0 pour des tests locaux
//#define CAN_VIRTUAL_INTERFACE 
//pour utiliser can0 connecté à un réseau CAN
#define CAN_REAL_INTERFACE
//pour utiliser can0 pour recevoir ce qu'on transmet
//#define CAN_REAL_WITH_LOOPBACK

//Dependances logicielles:
#define CAN_RECEIVING_ADDRESS 0x123
#define CAN_RECEIVING_MASK 0x000007FFU

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
//pas de fonctions publiques

//Variables publiques:
//pas de variables publiques
#endif
