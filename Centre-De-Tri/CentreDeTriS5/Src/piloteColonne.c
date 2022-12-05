//piloteIOT1:
//Historique: 
// 2022-11-29, Renaud Gagnon, creation

//INCLUSIONS
#include "main.h"
#include "piloteColonne.h"

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


void piloteColonne_initialise(void);

void piloteColonne_eteint(unsigned char couleur)
{
  switch (couleur)
  {
    case PILOTECOLONNE_ROUGE:
    HAL_GPIO_WritePin(PILOTECOLONNE_ROUGE_PORT, PILOTECOLONNE_ROUGE_SORTIE, (GPIO_PinState)0);  
    break;
    case PILOTECOLONNE_VERT:
    HAL_GPIO_WritePin(PILOTECOLONNE_VERT_PORT, PILOTECOLONNE_VERT_SORTIE, (GPIO_PinState)0);  
    break;
    case PILOTECOLONNE_JAUNE:
    HAL_GPIO_WritePin(PILOTECOLONNE_JAUNE_PORT, PILOTECOLONNE_JAUNE_SORTIE, (GPIO_PinState)0);  
    break;
  }
  
}
void piloteColonne_allume(unsigned char couleur)
{
  switch (couleur)
  {
    case PILOTECOLONNE_ROUGE:
    HAL_GPIO_WritePin(PILOTECOLONNE_ROUGE_PORT, PILOTECOLONNE_ROUGE_SORTIE, (GPIO_PinState)1);  
    break;
    case PILOTECOLONNE_VERT:
    HAL_GPIO_WritePin(PILOTECOLONNE_VERT_PORT, PILOTECOLONNE_VERT_SORTIE, (GPIO_PinState)1);  
    break;
    case PILOTECOLONNE_JAUNE:
    HAL_GPIO_WritePin(PILOTECOLONNE_JAUNE_PORT, PILOTECOLONNE_JAUNE_SORTIE, (GPIO_PinState)1);  
    break;
  }
  
}

void piloteColonne_initialise(void)
{
  //HAL_GPIO_WritePin(PILOTEIOT1_PORT, PILOTEIOT1_SORTIE, GPIO_PIN_RESET);  
}




