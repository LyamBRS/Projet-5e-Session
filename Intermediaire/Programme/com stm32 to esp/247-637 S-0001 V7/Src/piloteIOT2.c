//piloteIOT2:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteIOT2.h"

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
void piloteIOT2_metLaSortieA(unsigned char Valeur)
{
  HAL_GPIO_WritePin(PILOTEIOT2_PORT, PILOTEIOT2_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteIOT2_initialise(void)
{
  HAL_GPIO_WritePin(PILOTEIOT2_PORT, PILOTEIOT2_SORTIE, GPIO_PIN_RESET);  
}




