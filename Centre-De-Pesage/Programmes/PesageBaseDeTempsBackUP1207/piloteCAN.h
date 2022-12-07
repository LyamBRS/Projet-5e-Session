#ifndef PILOTECAN_H
#define PILOTECAN_H

//MODULE: piloteCAN
//DESCRIPTION: 
//Ce programme suppose que la librairie can-utils est installée
//Ce module permet d'ouvrir une interface et de la fermer avant de quitter
//Il faut ouvrir une interface avant de faire appel à piloteCAN_initialise
//Le programme qui utilise le module piloteCAN doit de gérer la fermeture
//de l'interface à l'aide de la fonction piloteCAN_fermeUneInterface.

//Ce module utilise la définition PILOTECAN_INTERFACE_VIRTUELLE pour savoir s'il doit utiliser vcan0
//Ce module utilise la définition PILOTECAN_INTERFACE_REELLE pour savoir s'il doit utiliser can0


//HISTORIQUE:
// 2021-10-28, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pour utiliser vcan0 pour des tests locaux
//#define PILOTECAN_INTERFACE_VIRTUELLE 
//pour utiliser can0 connecté à un réseau CAN
//#define PILOTECAN_INTERFACE_REELLE
//pour utiliser can0 pour recevoir ce qu'on transmet
//#define PILOTECAN_INTERFACE_REELLE_AVEC_LOOPBACK

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTECAN_ADRESSE_EN_RECEPTION 0x123 (0 pour tout recevoir)
//#define PILOTECAN_MASQUE_EN_RECEPTION 0x000007FFU (0 pour ne pas filtrer)


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PILOTECAN_EN_FONCTION 0
#define PILOTECAN_PAS_EN_FONCTION 1
#define PILOTECAN_MESSAGE_AVEC_DONNEES 1
#define PILOTECAN_MESSAGE_SANS_DONNEES 0

//Fonctions publiques:
void piloteCAN_ouvreUneInterface(void);
void piloteCAN_fermeUneInterface(void);
int piloteCAN_transmet(unsigned long Adresse, unsigned char *TamponDeTransmission, unsigned char NombreATransmettre);
int piloteCAN_recoitUnMessage(unsigned long *Adresse, unsigned char *TamponDeReception, unsigned char *NombreRecu);
int piloteCAN_typeDeMessageRecu(void);
int piloteCAN_initialise(void);

//Variables publiques:
extern int piloteCAN_etatDuModule;

typedef struct
{
  unsigned char replyBuffer[8]; //buffer to send packet
  unsigned char readBuffer[8];  //buffer to hold incoming packet

} stPILOTECAN;


stPILOTECAN piloteCAN;



#endif
