//piloteIOT1:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOT1.h"

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
void piloteIOT1_metAUn(void)
{
  digitalWrite(PILOTEIOT1_BROCHE, HIGH);
}

void piloteIOT1_metAZero(void)
{
  digitalWrite(PILOTEIOT1_BROCHE, LOW);
}

void piloteIOT1_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOT1_BROCHE, Niveau);
}

void piloteIOT1_initialise(void)
{
  pinMode(PILOTEIOT1_BROCHE,OUTPUT);

#ifdef PILOTEIOT1_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOT1_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOT1_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOT1_BROCHE,LOW);
#endif
}
