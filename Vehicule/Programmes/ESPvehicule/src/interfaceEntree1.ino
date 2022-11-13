//interfaceClientWeb:
//Historique: 
// 2021-04-15, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntree1.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntree1.h"


//Definitions privees
#define INTERFACEENTREE1_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEENTREE1_COMPTE_INITIAL (\
  INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceEntree1_gere(void);

//Definitions de variables privees:
unsigned int interfaceEntree1_compteurAvantLecture;
unsigned int interfaceEntree1_compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceEntree1_gere(void)
{
  interfaceEntree1_compteurAvantLecture++;
  if (interfaceEntree1_compteurAvantLecture < INTERFACEENTREE1_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceEntree1_compteurAvantLecture = 0;
  if (piloteEntree1_lit() == INTERFACEENTREE1_VALEUR_LUE_SI_ACTIVE)
  {
    if (interfaceEntree1_compteurAntiRebond == INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceEntree1_compteurAntiRebond++;
    if (interfaceEntree1_compteurAntiRebond < INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    if (interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_ACTIVE)
    {
      return;    
    }
    interfaceEntree1.etatDuModule = INTERFACEENTREE1_MODULE_EN_FONCTION;
    interfaceEntree1.etatDeLEntree = INTERFACEENTREE1_ACTIVE;
    interfaceEntree1.information = INTERFACEENTREE1_INFORMATION_DISPONIBLE;       
    return;
  }
  if (interfaceEntree1_compteurAntiRebond == 0)
  {
    return; 
  }
  interfaceEntree1_compteurAntiRebond--;
  if (interfaceEntree1_compteurAntiRebond > 0)
  {
    return;
  }
  if (interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_INACTIVE)
  {
    return;
  }
  interfaceEntree1.etatDuModule = INTERFACEENTREE1_MODULE_EN_FONCTION;  
  interfaceEntree1.etatDeLEntree = INTERFACEENTREE1_INACTIVE;
  interfaceEntree1.information = INTERFACEENTREE1_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEENTREE1 interfaceEntree1;

//Definitions de fonctions publiques:
void interfaceEntree1_initialise(void)
{
  interfaceEntree1.etatDuModule = INTERFACEENTREE1_MODULE_PAS_EN_FONCTION;
  interfaceEntree1.information = INTERFACEENTREE1_INFORMATION_TRAITEE;
  interfaceEntree1.etatDeLEntree = INTERFACEENTREE1_PAS_EN_FONCTION;
	interfaceEntree1_compteurAvantLecture = 0;
  interfaceEntree1_compteurAntiRebond = INTERFACEENTREE1_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEENTREE1_PHASE] = interfaceEntree1_gere;
}
