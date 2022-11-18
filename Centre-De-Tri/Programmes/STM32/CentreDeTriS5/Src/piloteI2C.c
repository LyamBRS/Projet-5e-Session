//piloteI2C:
//Historique: 
// 2022-11-18, Renaud Gagnon, creation

//INCLUSIONS
#include "main.h"
#include "piloteI2C.h"

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
unsigned char piloteI2C_Transmit(unsigned char ucAdresse, unsigned char ucDonnee)
{
  HAL_I2C_Master_Transmit(&hi2c1, ucAdresse, &ucDonnee, 1, 128)
}

unsigned char piloteI2C_Recieve(unsigned char ucAdresse, unsigned char *ucDonnee)
{
  HAL_I2C_Master_Receive(&hi2c1, ucAdresse, &ucDonnee, 1, 128);
}

void piloteI2C_initialise(void)
{
  //on pose que le cube a fait la configuration par defaut
}




