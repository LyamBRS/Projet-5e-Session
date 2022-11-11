#ifndef PROCESSUSMOTEURPASAPAS_H
#define PROCESSUSMOTEURPASAPAS_H

//MODULE: processusMoteurPasAPas
//DESCRIPTION: implemente la gestion d'un clignotant.

//HISTORIQUE:
// 2022-10-18, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSMOTEURPASAPAS_TEMPS_PAR_COMMANDE_EN_MS 8
//#define PROCESSUSMOTEURPASAPAS_PHASE 0


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSMOTEURPASAPAS_REQUETE_ACTIVE 1
#define PROCESSUSMOTEURPASAPAS_REQUETE_TRAITEE 0
#define PROCESSUSMOTEURPASAPAS_ARRET 0
#define PROCESSUSMOTEURPASAPAS_SENS_HORAIRE_PAR_DEMI_PAS 1
#define PROCESSUSMOTEURPASAPAS_SENS_HORAIRE_PAR_PAS 2
#define PROCESSUSMOTEURPASAPAS_SENS_ANTI_HORAIRE_PAR_DEMI_PAS -1
#define PROCESSUSMOTEURPASAPAS_SENS_ANTI_HORAIRE_PAR_PAS -2

typedef struct
{
  unsigned char requete;
  char pasRequis;
}PROCESSUSMOTEURPASAPAS;

//Fonctions publiques:
void processusMoteurPasAPas_initialise(void);

//Variables publiques:
extern PROCESSUSMOTEURPASAPAS processusMoteurPasAPas;

#endif
