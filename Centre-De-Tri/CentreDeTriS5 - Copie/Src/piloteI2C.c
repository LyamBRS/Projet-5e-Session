//piloteI2C:
//Historique: 
// 2022-11-18, Renaud Gagnon, creation

//INCLUSIONS
#include "main.h"
#include "piloteI2C.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
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
void piloteI2C_Transmit(unsigned char ucAdresse, uint8_t ucDonnee)
{
  HAL_I2C_Master_Transmit(&hi2c1, ucAdresse, &ucDonnee, 1, 200);
}

void piloteI2C_Receive(unsigned char ucAdresse, uint8_t *ucDonnee)
{
  HAL_I2C_Master_Receive(&hi2c1, ucAdresse, ucDonnee, 1, 200);
}

void piloteI2C_initialise(void)
{
  //on pose que le cube a fait la configuration par defaut
}




