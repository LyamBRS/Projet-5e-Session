#ifndef INTERFACES0002_H
#define INTERFACES0002_H

//MODULE: interfaceS0002
//DESCRIPTION: implemente le protocole qui permet d'interagir avec un ensemble
//de developpement Dallas programme avec le logiciel 247-637 S-0002

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACES0002_PHASE_RECEPTION 0
//#define INTERFACES0002_PHASE_TRANSMISSION 1


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACES0002_RELACHE  0x00
#define INTERFACES0002_APPUYE  0xFF
#define INTERFACES0002_OCTET_A_TRANSMETTRE 0x5A
#define INTERFACES0002_PAS_D_ERREUR 0
#define INTERFACES0002_ERREUR 1

typedef struct
{
  unsigned char information;
  unsigned char octetRecu;
  unsigned char requete;
  unsigned char erreur;
} INTERFACES0002;

//Fonctions publiques:
void interfaceS0002_initialise(void);

//Variables publiques:
extern INTERFACES0002 interfaceS0002;

#endif
