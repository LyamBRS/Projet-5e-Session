#ifndef INTERFACECAN1_H
#define INTERFACECAN1_H

//MODULE: interfaceCAN1
//DESCRIPTION: pour utiliser le CAN1
//HISTORIQUE:
// 2018-11-12, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielle
//pas de dépendances matérielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACECAN1_DISPONIBLE  1
#define INTERFACECAN1_PAS_DISPONIBLE 0
#define INTERFACECAN1_TRANSMIS 0
#define INTERFACECAN1_PAS_TRANSMIS 1
#define INTERFACECAN1_ERREUR 1
#define INTERFACECAN1_PAS_D_ERREUR 0

//Fonctions publiques:
unsigned int interfaceCAN1_messageDisponible(void);
unsigned int interfaceCAN1_messageTransmis(void);
unsigned char interfaceCAN1_litUnMessageRecu(unsigned char *DonneesRecues);
unsigned int interfaceCAN1_transmetDesDonnes(unsigned int Identification11Bits,
                                          unsigned char *Donnees,
                                          unsigned char Nombre);
unsigned int interfaceCAN1_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
