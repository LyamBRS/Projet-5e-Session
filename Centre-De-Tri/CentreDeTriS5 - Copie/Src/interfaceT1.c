//interfaceT1:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteIOT1.h"
#include "interfaceT1.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceT1_allume(void)
{
  piloteIOT1_metLaSortieA(INTERFACET1_VALEUR_POUR_ALLUMER);
}

void interfaceT1_eteint(void)
{
  piloteIOT1_metLaSortieA(INTERFACET1_VALEUR_POUR_ETEINDRE);
}

void interfaceT1_initialise(void)
{
  piloteIOT1_metLaSortieA(INTERFACET1_VALEUR_POUR_ETEINDRE);
}


