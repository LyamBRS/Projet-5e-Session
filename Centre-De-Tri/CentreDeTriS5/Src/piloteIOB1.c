//piloteIOB1:
//Historique: 
// 2018-09-08, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteIOB1.h"

//Definitions privees
//pas de définitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
unsigned char piloteIOB1_litLEntree(void)
{
  return HAL_GPIO_ReadPin(PILOTEIOB1_PORT, PILOTEIOB1_ENTREE);
}

void piloteIOB1_initialise(void)
{
  //on pose que le cube a fait la configuration par defaut
}




