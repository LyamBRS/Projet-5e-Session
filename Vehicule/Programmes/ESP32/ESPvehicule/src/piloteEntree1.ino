//piloteEntree1:
//Historique: 
// 2021-04-04, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntree1.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
unsigned char piloteEntree1_lit(void)
{
  return digitalRead(PILOTEENTREE1_BROCHE);
}

void piloteEntree1_initialise(void)
{
#ifdef PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
	pinMode(PILOTEENTREE1_BROCHE,INPUT_PULLUP);
#endif

#ifdef PILOTEENTREE1_MODE_FLOTTANT_SANS_PULL_UP
	pinMode(PILOTEENTREE1_BROCHE);
#endif
}
