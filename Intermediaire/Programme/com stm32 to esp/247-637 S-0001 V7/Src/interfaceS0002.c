//interfaceS0002:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteUSART2.h"
#include "serviceBaseDeTemps.h"
#include "interfaceS0002.h"

//Definitions privees
//pas de définitions privees

//Declarations de fonctions privees:
unsigned char interfaceS0002_valideLaReception(void);
void interfaceS0002_gereLaReception(void);
void interfaceS0002_gereLaTransmission(void);

//Definitions de variables privees:
//pas de variables privees
  
//Definitions de fonctions privees:
unsigned char interfaceS0002_valideLaReception(void)
{
  if (interfaceS0002.octetRecu == INTERFACES0002_RELACHE)
  {
    return INTERFACES0002_PAS_D_ERREUR;
  }
  if (interfaceS0002.octetRecu == INTERFACES0002_APPUYE)
  {
    return INTERFACES0002_PAS_D_ERREUR;
  }
  return INTERFACES0002_ERREUR;
}
void interfaceS0002_gereLaReception(void)
{
  if (piloteUSART2_octetDisponible() == PILOTEUSART2_PAS_DISPONIBLE)
  {
    return;
  }
  interfaceS0002.octetRecu = piloteUSART2_litUnOctetRecu();
  piloteUSART2_confirmeLaReception();
  interfaceS0002.erreur = interfaceS0002_valideLaReception();
  interfaceS0002.information = INFORMATION_DISPONIBLE;
}

void interfaceS0002_gereLaTransmission(void)
{
  if (interfaceS0002.requete == REQUETE_TRAITEE)
  {
    return;
  }
  piloteUSART2_confirmeLaFinDeTransmission();
  piloteUSART2_transmet(INTERFACES0002_OCTET_A_TRANSMETTRE);
  interfaceS0002.requete = REQUETE_TRAITEE;
}

//Definitions de variables publiques:
INTERFACES0002 interfaceS0002;

//Definitions de fonctions publiques:
void interfaceS0002_initialise(void)
{
  interfaceS0002.information = INFORMATION_TRAITEE;
  interfaceS0002.requete = REQUETE_TRAITEE;
  interfaceS0002.erreur = INTERFACES0002_PAS_D_ERREUR;
  serviceBaseDeTemps_execute[INTERFACES0002_PHASE_RECEPTION] =
      interfaceS0002_gereLaReception;
  serviceBaseDeTemps_execute[INTERFACES0002_PHASE_TRANSMISSION] =
      interfaceS0002_gereLaTransmission;
}
