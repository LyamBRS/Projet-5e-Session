//interfaceT3:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteIOT3.h"
#include "interfaceT3.h"

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
void interfaceT3_allume(void)
{
  piloteIOT3_metLaSortieA(INTERFACET3_VALEUR_POUR_ALLUMER);
}

void interfaceT3_eteint(void)
{
  piloteIOT3_metLaSortieA(INTERFACET3_VALEUR_POUR_ETEINDRE);
}

void interfaceT3_initialise(void)
{
  piloteIOT3_metLaSortieA(INTERFACET3_VALEUR_POUR_ETEINDRE);
}
