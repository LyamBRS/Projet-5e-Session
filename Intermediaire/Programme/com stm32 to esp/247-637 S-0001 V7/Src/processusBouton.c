//processusBoutonConnecte:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocole637.h"
#include "interfaceT2.h"
#include "interfaceT3.h"
#include "interfaceT4.h"
#include "interfaceB1.h"
#include "interfaceS0002.h"
#include "processusBouton.h"

//Definitions privees
#define PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR (\
    (unsigned int)(PROCESSUSBOUTONCONNECTE_TEMPS_MAXIMAL_POUR_RECEVOIR_EN_MS \
    *FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ / 1000.0))

//Declarations de fonctions privees:
void processusBoutonConnecte_changeT2(void);
void processusBoutonConnecte_attendApresLeBouton(void);
void processusBoutonConnecte_attendUneDemande(void);
void processusBoutonConnecte_attendUneReponse(void);

//Definitions de variables privees:
unsigned char processusBoutonConnecte_etatDeT2;
unsigned char processusBoutonConnecte_compteur;

//Definitions de fonctions privees:
//void processusBoutonConnecte_changeT2(void)
//{
//  if (processusBoutonConnecte_etatDeT2 == 0)
//  {
//    processusBoutonConnecte_etatDeT2 = 1;
//    interfaceT2_allume();
//    return;
//  }
//  processusBoutonConnecte_etatDeT2 = 0;
//  interfaceT2_eteint();  
//}
//
void processusBoutonConnecte_attendApresLeBouton(void)
{
  if (interfaceB1.etatDuModule == MODULE_PAS_EN_FONCTION) // MODULE_PAS_EN_FONCTION
  {
    interfaceT4_eteint();
    return;
  }
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneDemande;
  processusBoutonConnecte_attendUneDemande(); //on sauve une interruption    
}

void processusBoutonConnecte_attendUneDemande(void)
{
  if (interfaceB1.information == INFORMATION_TRAITEE)
  {
    
    return;
  }
  interfaceB1.information = INFORMATION_TRAITEE;
  if (interfaceB1.etatDuBouton == INTERFACEB1_RELACHE)
  {
     interfaceT4_eteint();
    return;
  }
  processusBoutonConnecte_compteur = 0;
  interfaceT4_allume();
  serviceProtocole637.requete = REQUETE_ACTIVE;
//  interfaceS0002.requete = REQUETE_ACTIVE;
//  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
//    processusBoutonConnecte_attendUneReponse;
}

//void processusBoutonConnecte_attendUneReponse(void)
//{
//  processusBoutonConnecte_compteur++;
//  if (processusBoutonConnecte_compteur ==
//      PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR)
//  {
//    processusBoutonConnecte_compteur = 0;
//    interfaceT4_eteint();
//    serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
//        processusBoutonConnecte_attendUneDemande;
//    return;
//  }
//  if (interfaceS0002.information == INFORMATION_TRAITEE)
//  {
//    return;
//  }
//  interfaceS0002.information = INFORMATION_TRAITEE;
//  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
//    processusBoutonConnecte_attendUneDemande;
// 
//  processusBoutonConnecte_changeT2();
//  if (interfaceS0002.erreur == INTERFACES0002_ERREUR)
//  {
//    interfaceT4_eteint();
//    return;
//  }
//  if (interfaceS0002.octetRecu == INTERFACES0002_RELACHE)
//  {
//    interfaceT3_eteint();
//    return;
//  }
//  interfaceT3_allume();
//}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void processusBoutonConnecte_initialise(void)
{
  processusBoutonConnecte_compteur = 0;
  processusBoutonConnecte_etatDeT2 = 1;
  interfaceT2_eteint();
  interfaceT3_eteint();
  interfaceT4_eteint();
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
      processusBoutonConnecte_attendApresLeBouton;
}
