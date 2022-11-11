//processusMoteurPasAPas:
//Historique: 
// 2022-04-11, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xinterfaceT1.h"
#include "xserviceBaseDeTemps.h"
#include "xprocessusMoteurPasAPas.h"

//Definitions privees
#define PROCESSUSMOTEURPASAPAS_COMPTE_PAR_COMMANDE (\
  PROCESSUSMOTEURPASAPAS_TEMPS_PAR_COMMANDE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)
  
//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
char processusMoteurPasAPas_compteur;
char processusMoteurPasAPas_indice;
char processusMoteurPasAPas_pasEnCours;
unsigned char processusMoteurPasAPas_filBleu[]   = {1, 1, 0, 0, 0, 0, 0, 1};
unsigned char processusMoteurPasAPas_filRose[]   = {0, 1, 1, 1, 0, 0, 0, 0};
unsigned char processusMoteurPasAPas_filJaune[]  = {0, 0, 0, 1, 1, 0, 0, 0};
unsigned char processusMoteurPasAPas_filOrange[] = {0, 0, 0, 0, 0, 1, 1, 1};

//Definitions de fonctions privees:
void processusMoteurPasAPas_gere(void);

//Definitions de variables publiques:
PROCESSUSMOTEURPASAPAS processusMoteurPasAPas;

//Definitions de fonctions publiques:
void processusMoteurPasAPas_gere(void)
{
  if (processusMoteurPasAPas.requete == PROCESSUSMOTEURPASAPAS_REQUETE_ACTIVE)
  {
    processusMoteurPasAPas_pasEnCours = processusMoteurPasAPas.pasRequis;
    processusMoteurPasAPas.requete = PROCESSUSMOTEURPASAPAS_REQUETE_TRAITEE;
  }
  processusMoteurPasAPas_compteur ++;
  if (processusMoteurPasAPas_compteur < PROCESSUSMOTEURPASAPAS_COMPTE_PAR_COMMANDE)
  {
    return;
  }
  processusMoteurPasAPas_indice += processusMoteurPasAPas_pasEnCours;
  processusMoteurPasAPas_indice &= 0x07; //conserve de 0 a 7
  interfaceULN2003_appliqueLesNiveaux(
      processusMoteurPasAPas_filBleu[processusMoteurPasAPas_indice], processusMoteurPasAPas_filRose[processusMoteurPasAPas_indice],
      processusMoteurPasAPas_filJaune[processusMoteurPasAPas_indice], processusMoteurPasAPas_filOrange[processusMoteurPasAPas_indice]);
}

void processusMoteurPasAPas_initialise(void)
{
  processusMoteurPasAPas_compteur = 0;
  processusMoteurPasAPas_indice = 0;
  processusMoteurPasAPas_pasEnCours = PROCESSUSMOTEURPASAPAS_ARRET;
  processusMoteurPasAPas.requete = PROCESSUSMOTEURPASAPAS_REQUETE_TRAITEE;
  processusMoteurPasAPas.pasRequis = PROCESSUSMOTEURPASAPAS_ARRET;
  interfaceULN2003_appliqueLesNiveaux(0, 0, 0, 0); //note: les premiers pas ne sont pas certain
  serviceBaseDeTemps_execute[PROCESSUSMOTEURPASAPAS_PHASE] = processusMoteurPasAPas_gere;
}
