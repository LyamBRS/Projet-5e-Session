#ifndef PILOTECAN_H
#define PILOTECAN_H

//MODULE: piloteCAN
//DESCRIPTION: 
//Ce programme suppose que la librairie can-utils est installée
//Ce module permet d'ouvrir une interface et de la fermer avant de quitter
//Il faut ouvrir une interface avant de faire appel à CAN_Initialise
//Le programme qui utilise le module piloteCAN doit de gérer la fermeture
//de l'interface à l'aide de la fonction CAN_CloseInterface.

//Ce module utilise la définition CAN_VIRTUAL_INTERFACE pour savoir s'il doit utiliser vcan0
//Ce module utilise la définition CAN_REAL_INTERFACE pour savoir s'il doit utiliser can0


//======================================================== HISTORY // 
// 2021-10-28, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pour utiliser vcan0 pour des tests locaux
//#define CAN_VIRTUAL_INTERFACE 
//pour utiliser can0 connecté à un réseau CAN
//#define CAN_REAL_INTERFACE
//pour utiliser can0 pour recevoir ce qu'on transmet
//#define CAN_REAL_WITH_LOOPBACK

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define CAN_RECEIVING_ADDRESS 0x123 (0 pour tout recevoir)
//#define CAN_RECEIVING_MASK 0x000007FFU (0 pour ne pas filtrer)


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define CAN_WORKING 0
#define CAN_UNAVAILABLE 1
#define CAN_MESSAGE_WITH_DATA 1
#define CAN_MESSAGE_EMPTY 0

//Fonctions publiques:
void CAN_OpenInterface(void);
void CAN_CloseInterface(void);
int CAN_Transmit(unsigned long Address, unsigned char *transmitBuffer, unsigned char NumberToSend);
int CAN_ReceiveMessage(unsigned long *Address, unsigned char *receiveBuffer, unsigned char *amountOfBytesReceived);
int CAN_TypeOfReceivedMessage(void);
int CAN_Initialise(void);

//Variables publiques:
extern int CAN_ModuleState;

#endif
