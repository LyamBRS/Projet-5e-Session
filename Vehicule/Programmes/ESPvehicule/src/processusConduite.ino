/**
 * @file processusConduite.ino
 * @author Camille Fortin  CamFo (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//INCLUSIONS
#include "xmain.h"

#include "piloteUDP.h"

#include "serviceTank.h"
#include "xserviceBaseDeTemps.h"
#include "xprocessusConduite.h"


//Definitions privees


//Definitions de variables privees:
unsigned long processusConduite_compteur;

//Definitions de fonctions privees:
void processusConduite_attendUneRequete(void);
void processusConduite_Reperage(void);
void processusConduite_Gere(void);

void processusConduite_Avance(void);
void processusConduite_UturnDroit(void);
void processusConduite_UturnGauche(void);
void processusConduite_tourneDroit(void);
void processusConduite_tourneGauche(void);

void processusConduite_Arrive(void);
void processusConduite_Positionnement(void);

//Definitions de variables publiques:
PROCESSUSCONDUITE processusConduite;

// Fontion d'état du processus conduite
void processusConduite_attendUneRequete(void)
{ 
  if(processusConduite.requete != PROCESSUSCONDUITE_REQUETEACTIVE)
  {
    return;
  }
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Gere;
}


void processusConduite_initialise(void)
{
  serviceTank_initialise();
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_attendUneRequete;
}
void processusConduite_Gere(void)
{

  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Avance;
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_UturnDroit;
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_UturnGauche;
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_tourneDroit;
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_tourneGauche;


  // if suiveur voit 4 témoin il considere arrivé a destination
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Arrive;
}
