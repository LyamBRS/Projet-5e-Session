//interfaceT4:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteIOT4.h"
#include "interfaceT4.h"

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
void interfaceT4_allume(void)
{
  piloteIOT4_metLaSortieA(INTERFACET4_VALEUR_POUR_ALLUMER);
}

void interfaceT4_eteint(void)
{
  piloteIOT4_metLaSortieA(INTERFACET4_VALEUR_POUR_ETEINDRE);
}

void interfaceT4_initialise(void)
{
  piloteIOT4_metLaSortieA(INTERFACET4_VALEUR_POUR_ETEINDRE);
}
