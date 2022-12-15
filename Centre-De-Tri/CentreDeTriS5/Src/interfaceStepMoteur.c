/**
 * @file interfaceStepMoteur.c
 * @author Renaud Gagnon
 * @brief Fichier contenant le code qui permet d'utiliser l'ascenceur du centre de tri. 
 * Ce fichier a été créer pour remplacer les fichier d'interface de l'ascenseur de Karl parce-que ceux-ci ne fonctionnent pas.
 * @version 0.1
 * @date 2022-12-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "main.h"
#include "piloteStepMoteur.h"
#include "interfaceStepMoteur.h"
#include "serviceBaseDeTemps.h"
//Definitions privees
#define INTERFACEASCENSEUR_VITESSE 20
#define NB_STEP_BAS 1200
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
unsigned int overallStep;
unsigned char positionVoulue;
unsigned char position = 0;
bool jam = 0;
  bool tabStepMoteur [4][8]={{1,1,0,0,0,0,0,1},
                             {0,1,1,1,0,0,0,0},
                             {0,0,0,1,1,1,0,0},
                             {0,0,0,0,0,1,1,1}};

/**
 * @brief 
 * 
 */
void interfaceStepMoteur_gere(void)
{
  
  /*
  static unsigned int compteTemps = 0;
  static unsigned int compteStepAscenseur = 0;
  compteTemps++;
  if (compteTemps >= INTERFACEASCENSEUR_VITESSE)
  {
    if (positionVoulue == INTERFACESTEPMOTEUR_POSITION_BASSE && overallStep!= NB_STEP_BAS)overallStep++;
    compteTemps = 0;
    if (tabStepMoteur[0][overallStep%8])piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP0, PILOTESTEPMOTEUR_ACTIVE);
    else piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP0, PILOTESTEPMOTEUR_DESACTIVE);

    if (tabStepMoteur[1][overallStep%8])piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP1, PILOTESTEPMOTEUR_ACTIVE);
    else piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP1, PILOTESTEPMOTEUR_DESACTIVE);

    if (tabStepMoteur[2][overallStep%8])piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP2, PILOTESTEPMOTEUR_ACTIVE);
    else piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP2, PILOTESTEPMOTEUR_DESACTIVE);

    if (tabStepMoteur[3][overallStep%8])piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP3, PILOTESTEPMOTEUR_ACTIVE);
    else piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP3, PILOTESTEPMOTEUR_DESACTIVE); 
    if (positionVoulue == INTERFACESTEPMOTEUR_POSITION_BASSE && overallStep == NB_STEP_BAS)
    {
      positionVoulue = 0;
    }
  }
  if (positionVoulue == INTERFACESTEPMOTEUR_POSITION_BASSE && overallStep == NB_STEP_BAS)position = INTERFACESTEPMOTEUR_POSITION_BASSE;
  */
 if (jam)
 {
     piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP0, PILOTESTEPMOTEUR_DESACTIVE);
 piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP1, PILOTESTEPMOTEUR_DESACTIVE);
 piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP2, PILOTESTEPMOTEUR_DESACTIVE);
 piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP3, PILOTESTEPMOTEUR_DESACTIVE);
 }

 else{
     piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP0, PILOTESTEPMOTEUR_ACTIVE);
 piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP1, PILOTESTEPMOTEUR_DESACTIVE);
 piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP2, PILOTESTEPMOTEUR_DESACTIVE);
 piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP3, PILOTESTEPMOTEUR_DESACTIVE);
 }
}

void interfaceStepMoteur_home(void)
{
  
  static unsigned int compteTemps = 0;
  static unsigned int compteStepAscenseur = 0;
  compteTemps++;
  if (compteTemps >= INTERFACEASCENSEUR_VITESSE)
  {
    compteTemps = 0;
    if (tabStepMoteur[3][compteStepAscenseur])piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP0, PILOTESTEPMOTEUR_ACTIVE);
    else piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP0, PILOTESTEPMOTEUR_DESACTIVE);

    if (tabStepMoteur[2][compteStepAscenseur])piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP1, PILOTESTEPMOTEUR_ACTIVE);
    else piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP1, PILOTESTEPMOTEUR_DESACTIVE);

    if (tabStepMoteur[1][compteStepAscenseur])piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP2, PILOTESTEPMOTEUR_ACTIVE);
    else piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP2, PILOTESTEPMOTEUR_DESACTIVE);

    if (tabStepMoteur[0][compteStepAscenseur])piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP3, PILOTESTEPMOTEUR_ACTIVE);
    else piloteStepMoteur_EcritSortie(PILOTESTEPMOTEUR_STEP3, PILOTESTEPMOTEUR_DESACTIVE);
    compteStepAscenseur++;
    if (compteStepAscenseur > 7)compteStepAscenseur = 0;
  }
  if (HAL_GPIO_ReadPin(SW_ASC_GPIO_Port, SW_ASC_Pin) == 0)
  {
    overallStep = 0;
    position = INTERFACESTEPMOTEUR_POSITION_HAUTE;
    serviceBaseDeTemps_execute[INTERFACESTEPMOTEUR_GERE] = interfaceStepMoteur_gere;
  }
}
void interfaceStepMoteur_requete(unsigned char requete)
{
  if (requete == INTERFACESTEPMOTEUR_POSITION_BASSE)
  {
    jam = 1;
    serviceBaseDeTemps_execute[INTERFACESTEPMOTEUR_GERE] = interfaceStepMoteur_gere;
  }
  if (requete == INTERFACESTEPMOTEUR_POSITION_HAUTE)
  {
    jam = 0;
    serviceBaseDeTemps_execute[INTERFACESTEPMOTEUR_GERE] = interfaceStepMoteur_home;
  }
}

unsigned char interfaceStepMoteur_getPos(void)
{
  return position;
}

void interfaceStepMoteur_initialise(void)
{
  positionVoulue = 0;
  serviceBaseDeTemps_execute[INTERFACESTEPMOTEUR_GERE] = interfaceStepMoteur_home;
}




