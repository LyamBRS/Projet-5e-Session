//interfaceT2:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteIOT2.h"
#include "interfaceT2.h"

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
void interfaceT2_allume(void)
{
  piloteIOT2_metLaSortieA(INTERFACET2_VALEUR_POUR_ALLUMER);
}

void interfaceT2_eteint(void)
{
  piloteIOT2_metLaSortieA(INTERFACET2_VALEUR_POUR_ETEINDRE);
}

void interfaceT2_initialise(void)
{
  piloteIOT2_metLaSortieA(INTERFACET2_VALEUR_POUR_ETEINDRE);
}


