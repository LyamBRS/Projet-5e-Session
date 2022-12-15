/**
 * @file serviceBaseDeTemps.c
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief  pour mettre en place un service d'appels periodiques de fonctions
 *  pointees par un tableau de pointeurs de fonctions. Le service met en place
 *  une base de temps qui reposent sur l'emploi du \ref piloteTimer.h
 * 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "main.h"
#include "piloteTimer.h"
#include "serviceBaseDeTemps.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void serviceBaseDeTemps_neFaitRien(void);
void serviceBaseDeTemps_gere(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:

void serviceBaseDeTemps_neFaitRien(void)
{
  
}

void serviceBaseDeTemps_gere(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
  {
    serviceBaseDeTemps_execute[i]();
  }
}
    
//Definitions de variables publiques:

/**
 * @brief Tableau de pointeur de fonction qui peuvent être assigné par leur processus respectif.
 *  Ce tableau est au centre du fonctionnement de la base de temps. Pour plus d'explication voir 
 *  le fichier de définition de la base de temps \ref xserviceBaseDeTemps.h
 * 
 */
void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

void (*serviceBaseDeTemps_executeDansLoop[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP])(void);

//Definitions de fonctions publiques:
void serviceBaseDeTemps_gereDansLoop(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP; i++)
  {
    serviceBaseDeTemps_executeDansLoop[i]();
  }
}
void serviceBaseDeTemps_initialise(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
  {
    serviceBaseDeTemps_execute[i] = serviceBaseDeTemps_neFaitRien;
  }
  piloteTimer_execute = serviceBaseDeTemps_gere;

  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP; i++)
  {
    serviceBaseDeTemps_executeDansLoop[i] = serviceBaseDeTemps_neFaitRien;
  }
}
