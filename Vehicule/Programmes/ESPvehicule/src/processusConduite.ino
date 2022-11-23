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
#include "xinterfaceSuiveur.h"

#include "serviceTank.h"
#include "xserviceBaseDeTemps.h"
#include "xprocessusConduite.h"


//Definitions privees


//Definitions de variables privees:
unsigned long processusConduite_compteur;
unsigned char suiveurValue;

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


// Fontion d'état du processus conduite
void processusConduite_attendUneRequete(void)
{ 
  if(processusConduite.requete != PROCESSUSCONDUITE_REQUETEACTIVE)
  {
    return;
  }
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Gere;
}

void processusConduite_Gere(void)
{
  suiveurValue = interfaceSuiveur_litOctet();
  
  switch (suiveurValue)
  {
  case 0xE1:  //1110 0001 0xE1 Grosse gauche (1111 1110) 0xFE
    serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_UturnGauche;
    break;
  case 0xE6:  //1110 0110 0xE6 Gauche  (1111 1001)  0xF9
    serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_tourneGauche;
    break;
  case 0xE2:  //1110 0010 0xE2 Gauche  (1111 1101) 0xFD
    serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_tourneGauche;
    break;
  case 0xE4:  //1110 0100 0xE4 Avant (1111 1011)  0xFB
    serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Avance; // ON AVANCE 
    break;
  case 0xE8:  //1110 1000 0xE8 Droite (1111 0111) 0xF7
    serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_tourneDroit;
    break;
  case 0xEC:  //1110 1100 0xEC Droite  (1110 0111) 0xE7
    serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_tourneDroit;
    break;
  case 0xF0:  //1111 0000 0xF0 Grosse droite (1110 1111) 0xEF
    serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_UturnDroit; // 
    break; 
  case 0xFF:
    serviceTank_Arret();
    break;        
  }

  // if suiveur voit 4 témoin il considere arrivé a destination
  //serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Arrive;
}

void processusConduite_Avance(void)
{
  serviceTank_Avance(PROCESSUSCONDUITE_VITESSESTANDARD);
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Gere;
}

void processusConduite_UturnDroit(void)
{
  serviceTank_uturnDroit(PROCESSUSCONDUITE_VITESSESTANDARD);
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Gere;
}

void processusConduite_UturnGauche(void)
{
  serviceTank_uturnGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Gere;
}

void processusConduite_tourneDroit(void)
{
  serviceTank_uturnDroit(PROCESSUSCONDUITE_VITESSESTANDARD);
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Gere;
}

void processusConduite_tourneGauche(void)
{
  serviceTank_tourneGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Gere;
}


/// @brief Fonction d'initialisation du Processus Conduite 
/// @param  
void processusConduite_initialise(void)
{
  serviceTank_initialise();
  serviceTank_Arret();
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_attendUneRequete;
}