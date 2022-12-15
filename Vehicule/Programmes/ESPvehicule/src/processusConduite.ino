/**
 * @file processusConduite.ino
 * @author Camille Fortin  CamFo (camfortin2022@gmail.com)
 * 
 * @brief Le processus Conduite est une phase du service base de temps qui est appeler 
 *  à chaques périodes de la base de temps. Cela permet de démarrer une requête de conduite
 *  depuis un autre processus quand il est nécessaire. Le processus conduite a pour but de
 *  suivre la ligne noir installé au sol pour le projet de 5e session de TSO. Il utilise le \ref
 *  xserviceTank.h ainsi que \ref xinterfaceSuiveur.h pour conduire le vehicule et détecter 
 *  l'arrivé a destination.
 *  
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
#include "xprocessusBenne.h"

//Definitions privees


//Definitions de variables privees:
/**
 * @brief Variable qui sert a faire des délais dans le State Machine
 *  puisque le programme fonctionne avec une base de temps
 */
unsigned long processusConduite_compteur;
/**
 * @brief Variable qui stock la valeur lu par le suiveur de ligne 
 */
unsigned char suiveurValue;

//Definitions de fonctions privees:
void processusConduite_attendUneRequete(void);
void processusConduite_Gere(void);
void processusConduite_ArriveTri(void);
void processusConduite_ArrivePesage(void);


// FONCTION DU PROCESSUS 

/// @brief Méthode qui attend une requete pour suive la ligne
/// @param  void
void processusConduite_attendUneRequete(void)
{ 
  if(processusConduite.requete != PROCESSUSCONDUITE_REQUETE_ACTIVE)
  {
    return;
  }
  processusConduite.etatDuModule = PROCESSUSCONDUITE_MODULE_EN_DEPLACEMENT;
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_Gere;
  
}

/// @brief Gere la lecture du suiveur et la direction dans lequel aller
/// @param  void
void processusConduite_Gere(void)
{
  suiveurValue = interfaceSuiveur_litOctet();
  switch (suiveurValue)
  {
  case 0xE1:  //1110 0001 0xE1 Grosse gauche (1111 1110) 0xFE
    serviceTank_uturnGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
    break;
  case 0xE6:  //1110 0110 0xE6 Gauche  (1111 1001)  0xF9
    serviceTank_tourneGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
    break;
  case 0xE2:  //1110 0010 0xE2 Gauche  (1111 1101) 0xFD
    serviceTank_tourneGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
    break;
  case 0xE3:  //1110 0011 0xE2 Gauche  (1111 1101) 0xFD
    serviceTank_tourneGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
    break;
  case 0xE4:  //1110 0100 0xE4 Avant (1111 1011)  0xFB
    serviceTank_Avance(PROCESSUSCONDUITE_VITESSESTANDARD);  // On Avance
    break;
  case 0xE8:  //1110 1000 0xE8 Droite (1111 0111) 0xF7
    serviceTank_tourneDroit(PROCESSUSCONDUITE_VITESSESTANDARD);
    break;
  case 0xEC:  //1110 1100 0xEC Droite  (1110 0111) 0xE7
    serviceTank_tourneDroit(PROCESSUSCONDUITE_VITESSESTANDARD);
    break;
  case 0xF8:  //1111 1000 0xE8 Droite (1111 0111) 0xF7
    serviceTank_tourneDroit(PROCESSUSCONDUITE_VITESSESTANDARD);
    break;
  case 0xF0:  //1111 0000 0xF0 Grosse droite (1110 1111) 0xEF
    serviceTank_uturnDroit(PROCESSUSCONDUITE_VITESSESTANDARD);
    break; 
  case 0xFF: // 1111 1111 Si les 5 Capteur voit du NOIR, Le véhicule est arrivé au centre de pesage
    
    // On doit ajouter un test de dernier etat
    if(processusConduite.dernierArrive == PROCESSUSCONDUITE_DERNIERETAT_TRI)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_ArrivePesage;
    }
    break;
  case 0xF1:  //1111 0001 Valeur pour indiquer l'arrivé au centre de tri

    // On doit ajouter un test de dernier etat
    if(processusConduite.dernierArrive == PROCESSUSCONDUITE_DERNIERETAT_PESAGE)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_ArriveTri;
    }
    break;
  }
}

/// @brief Méthode qui arrête le véhicule et qui attend une requête
/// @param  void
void processusConduite_ArriveTri(void)
{
  serviceTank_Arret();
  processusConduite.dernierArrive = PROCESSUSCONDUITE_DERNIERETAT_TRI;
  processusConduite.etatDuModule = PROCESSUSCONDUITE_MODULE_ARRIVE_TRI;
  processusConduite.requete = PROCESSUSCONDUITE_REQUETE_TRAITE;
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_attendUneRequete;
  return;
}

/// @brief Méthode qui arrête le véhicule et qui attend une requête
/// @param  void
void processusConduite_ArrivePesage(void)
{
  serviceTank_Arret();
  processusConduite.dernierArrive = PROCESSUSCONDUITE_DERNIERETAT_PESAGE;
  processusConduite.etatDuModule = PROCESSUSCONDUITE_MODULE_ARRIVE_PESAGE;
  processusConduite.requete = PROCESSUSCONDUITE_REQUETE_TRAITE;
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_attendUneRequete;
  return;
}

/// @brief Fonction d'initialisation du Processus Conduite 
/// @param  void
void processusConduite_initialise(void)
{
  serviceTank_Arret();
  processusConduite.dernierArrive = PROCESSUSCONDUITE_DERNIERETAT_PESAGE;
  processusConduite.etatDuModule = PROCESSUSCONDUITE_MODULE_PAS_EN_FONCTION;
  processusConduite.requete = PROCESSUSCONDUITE_REQUETE_TRAITE;
  serviceBaseDeTemps_execute[PROCESSUSCONDUITE_PHASE] = processusConduite_attendUneRequete;
}