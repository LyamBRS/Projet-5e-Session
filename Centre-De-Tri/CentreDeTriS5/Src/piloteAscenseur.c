//piloteAscenseur:
//Historique: 
// 2022-12-12, Karl Naudin, creation

//INCLUSIONS
#include "main.h"
#include "piloteAscenseur.h"

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
void piloteAscenseurStep0_metLaSortieA(unsigned char Valeur)
{
  HAL_GPIO_WritePin(STEP0_Pin, PILOTEIOT1_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteAscenseurStep1_metLaSortieA(unsigned char Valeur)
{
  HAL_GPIO_WritePin(STEP1_Pin, PILOTEIOT1_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteAscenseurStep2_metLaSortieA(unsigned char Valeur)
{
  HAL_GPIO_WritePin(STEP2_Pin, PILOTEIOT1_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteAscenseurStep3_metLaSortieA(unsigned char Valeur)
{
  HAL_GPIO_WritePin(STEP3_Pin, PILOTEIOT1_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteAscenseur_initialise(void)
// Initialise ascenseur a une postion
{
  piloteAscenseurStep0_metLaSortieA(1);
  piloteAscenseurStep1_metLaSortieA(0);
  piloteAscenseurStep2_metLaSortieA(1);
  piloteAscenseurStep3_metLaSortieA(0);
}




