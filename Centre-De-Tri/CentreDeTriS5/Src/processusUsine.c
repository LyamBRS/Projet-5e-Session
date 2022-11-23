/**
 * @file processusUsine.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "piloteCAN1.h"
#include "processusUsine.h"
#include "piloteI2C.h"
#include "interfaceT1.h"
#include "interfaceT2.h"
#include "interfaceUsine.h"
//Definitions privees


//Declarations de fonctions privees:


//Definitions de variables privees:
unsigned char DonneesRecues [8];



//Definitions de fonctions privees:

/**
 * @brief Fonction qui gère le fonct...
 * @author Renaud Gagnon
 * @date 2022-11-18
 * @param void aucun paramètre d'entrée
 * @return void 
 * @warning
 * @example 
 */
// Références: \ref "variable" crée un lien cliquable qui mène a la variable ou a la fonction
void processusUsine_gere (void)
{
  piloteI2C_Transmit(INTERFACEUSINE_ADRESSE_PCF2_W, 0xFF);
  static int compte1sec;
  static bool flagLight;
  if (compte1sec >= 1000)
  {
    compte1sec = 0;
    if (flagLight)
    {
      interfaceT2_allume();
      //piloteI2C_Transmit(INTERFACEUSINE_ADRESSE_PCF1_W, 0xFF);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, ALLUME);
      interfaceT2_eteint();
      interfaceT1_eteint();
      flagLight = 0;
    }
    else 
    {
      interfaceT2_allume();
      //piloteI2C_Transmit(INTERFACEUSINE_ADRESSE_PCF1_W, 0xFE);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, ALLUME);
      interfaceT2_eteint();
      interfaceT1_allume();
      flagLight = 1;
    }
    
  }
  compte1sec++;

  
}



void processusUsine_initialise(void)
{
  serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_gere;
}
