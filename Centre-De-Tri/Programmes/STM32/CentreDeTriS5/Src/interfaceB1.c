//interfaceB1:
//Historique: 
// 2018-09-24, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteIOB1.h"
#include "serviceBaseDeTemps.h"
#include "interfaceB1.h"

//Definitions privees
#define INTERFACEB1_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ/INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ)
#define INTERFACEB1_COMPTE_INITIAL (\
  INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceB1_gere(void);

//Definitions de variables privees:
unsigned int compteurAvantLecture;
unsigned int compteurAntiRebond;

//Definitions de fonctions privees:
void interfaceB1_gere(void)
{
  compteurAvantLecture++;
  if (compteurAvantLecture < INTERFACEB1_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  compteurAvantLecture = 0;
  if (piloteIOB1_litLEntree() == INTERFACEB1_VALEUR_LUE_SI_APPUYE)
  {
    if (compteurAntiRebond == INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    compteurAntiRebond++;
    if (compteurAntiRebond < INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }    
    interfaceB1.etatDuModule = MODULE_EN_FONCTION;
    interfaceB1.etatDuBouton = INTERFACEB1_APPUYE;
    interfaceB1.information = INFORMATION_DISPONIBLE;       
    return;
  }
  if (compteurAntiRebond == 0)
  {
    return; 
  }
  compteurAntiRebond--;
  if (compteurAntiRebond > 0)
  {
    return;
  }
  interfaceB1.etatDuModule = MODULE_EN_FONCTION;  
  interfaceB1.etatDuBouton = INTERFACEB1_RELACHE;
  interfaceB1.information = INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEB1 interfaceB1;

//Definitions de fonctions publiques:
void interfaceB1_initialise(void)
{
  interfaceB1.etatDuModule = MODULE_PAS_EN_FONCTION;
  interfaceB1.information = INFORMATION_TRAITEE;
  interfaceB1.etatDuBouton = INTERFACEB1_INCONNU;
  compteurAvantLecture = 0;
  compteurAntiRebond = INTERFACEB1_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEB1_PHASE] = interfaceB1_gere;
}
