#ifndef PILOTEUSBBAL_H
#define PILOTEUSBBAL_H

//MODULE: piloteUSBbal
//DESCRIPTION: Module qui permet d'envoyer des commandes a une imprimante 3D
//de marque Malyan (M200) et de recevoir les reponses a ces commandes.

//HISTORIQUE:
// 2018-10-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define piloteUSBbal_BAUDRATE_AVEC_B_AU_DEBUT   B115200


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
int piloteUSBbal_initialise(void);
int piloteUSBbal_termine(void);
int piloteUSBbal_ecrit(char *Source, unsigned char NombreATransmettre);
int piloteUSBbal_attendLaFinDeLEcriture(void);
int piloteUSBbal_lit(char *Destination, unsigned char NombreMaximalDeLectures);

//Variables publiques:
//pas de variables publiques

#endif
