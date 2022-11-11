//interfaceULN2003:
//Historique: 
// 2022-10-18, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteIOFilBleu.h"
#include "xpiloteIOFilRose.h"
#include "xpiloteIOFilJaune.h"
#include "xpiloteIOFilOrange.h"
#include "xinterfaceULN2003.h"

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
void interfaceULN2003_appliqueLesNiveaux(unsigned char IN1, unsigned char IN2, unsigned char IN3, unsigned char IN4)
{
  piloteIOFilBleu_metA(IN1);
  piloteIOFilRose_metA(IN2);
  piloteIOFilJaune_metA(IN3);
  piloteIOFilOrange_metA(IN4);
}

void interfaceULN2003_initialise(void)
{
  interfaceULN2003_appliqueLesNiveaux(0, 0, 0, 0);
}
