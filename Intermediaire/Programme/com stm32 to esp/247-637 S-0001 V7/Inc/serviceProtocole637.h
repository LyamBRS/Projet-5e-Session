#ifndef SERVICEPROTOCOLE637_H
#define SERVICEPROTOCOLE637_H

//MODULE: serviceProtocole637
//DESCRIPTION: implemente le protocole qui permet d'interagir avec un ensemble
//de developpement Dallase avec le logiciel 247-637 S-0006 en
//utilisant un pointeur de fonctions du module serviceBaseDeTemps

//HISTORIQUE:
// 2018-10-28, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define SERVICEPROTOCOLE637_PAS_D_ERREURS 0
#define SERVICEPROTOCOLE637_ERREUR_EN_ATTENTE 1
#define SERVICEPROTOCOLE637_ERREUR_TEMPS_DEPASSE 2
#define SERVICEPROTOCOLE637_ERREUR_LONGUEUR_NULLE 3
#define SERVICEPROTOCOLE637_ERREUR_LONGUEUR_TROP_GRANDE 4
#define SERVICEPROTOCOLE637_ERREUR_INSERTION_NON_NULLE 5
#define SERVICEPROTOCOLE637_ERREUR_MAUVAIS_CHECKSUM 6


typedef struct
{
  unsigned char etatDuModuleDeReception;  
  unsigned char information;
  //unsigned char octetsRecus[SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char octetsRecus[SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char requete;
  unsigned char nombreATransmettre;
  unsigned char octetsATransmettre[SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char nombreARecevoir;
  unsigned char statut;
} SERVICEPROTOCOLE637;

//Fonctions publiques:
void serviceProtocole637_initialise(void);

//Variables publiques:
extern SERVICEPROTOCOLE637 serviceProtocole637;


#endif
