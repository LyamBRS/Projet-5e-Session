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
  static unsigned char compte1sec;
  static bool flagLight;
  if (compte1sec >= 10)
  {
    compte1sec = 0;
    if (flagLight)
    {
      piloteI2C_transmet(INTERFACEUSINE_ADRESSE_PCF1_W, 0x00);
      interfaceT1_eteint();
    }
    else 
    {
      piloteI2C_transmet(INTERFACEUSINE_ADRESSE_PCF1_W, 0x80);
      interfaceT1_allume();
    }
    
  }
  compte1sec++;

  
}



void processusUsine_initialise(void)
{
  serviceBaseDeTemps_execute[PROCESSUSPASSERELLE_PHASE_RECEPTION_TRANSMISSION_GERE_NOMPASTROPLONG] = processusPasserelle_gere;
}
