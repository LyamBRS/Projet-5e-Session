//serviceBaseDeTemps:
//Historique: 
// 2021-04-04, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xserviceTaskServer.h"
#include "xserviceBaseDeTemps.h"

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
  serviceTaskServer_execute = serviceBaseDeTemps_gere;

  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP; i++)
  {
    serviceBaseDeTemps_executeDansLoop[i] = serviceBaseDeTemps_neFaitRien;
  }
}
