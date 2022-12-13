//piloteIOB1:
//Historique: 
// 2018-09-08, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteStepMoteur.h"

//Definitions privees
//pas de d�finitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:

void piloteStepMoteur_EcritSortie(unsigned char ucStep, bool etat)
{
  switch ucStep
  {
    case PILOTESTEPMOTEUR_STEP0:
    if (etat == PILOTESTEPMOTEUR_ACTIVE)HAL_GPIO_WritePin(STEP0_GPIO_Port, STEP0_Pin, (GPIO_PinState)1);
    else HAL_GPIO_WritePin(STEP0_GPIO_Port, STEP0_Pin, (GPIO_PinState)0);
    break;
    case PILOTESTEPMOTEUR_STEP1:
    if (etat == PILOTESTEPMOTEUR_ACTIVE)HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, (GPIO_PinState)1);
    else HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, (GPIO_PinState)0);
    break;
    case PILOTESTEPMOTEUR_STEP2:
    if (etat == PILOTESTEPMOTEUR_ACTIVE)HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, (GPIO_PinState)1);
    else HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, (GPIO_PinState)0);
    break;
    case PILOTESTEPMOTEUR_STEP3:
    if (etat == PILOTESTEPMOTEUR_ACTIVE)HAL_GPIO_WritePin(STEP3_GPIO_Port, STEP3_Pin, (GPIO_PinState)1);
    else HAL_GPIO_WritePin(STEP3_GPIO_Port, STEP3_Pin, (GPIO_PinState)0);
    break;
  }
}

void piloteStepMoteur_initialise(void)
{
  //Ya rien pantoute icitte
}




