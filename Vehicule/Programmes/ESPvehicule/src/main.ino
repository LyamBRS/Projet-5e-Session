//#############################################################################
/**
 * @file main.c
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief
 * Program file containing the code defined in xmain.h
 * Please refer to this other file for information necessary in order to make this work.
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//#############################################################################


//INCLUSIONS
#include "xmain.h"

// inlcude des pilotes
#include "xpiloteMoteurBenne.h"
#include "xpiloteIOFeuArriereD.h"
#include "xpiloteIOFeuArriereG.h"
#include "xpiloteIOFeuAvantD.h"
#include "xpiloteIOFeuAvantG.h"
#include "xpiloteEntree1.h"
#include "xpiloteIOT1.h"
#include "xpiloteI2C1.h"
#include "piloteUDP.h"

// Include des Services
#include "xserviceTaskServer.h"
#include "xserviceBaseDeTemps.h"
#include "ServiceCommunication.h"
#include "serviceTank.h"

// Inlude des interfaces
#include "xinterfaceEntree1.h"
#include "xinterfaceT1.h"
#include "xinterfaceMoteurBenne.h"
#include "xinterfaceMoteurDroit.h"

// Include des processus
#include "xprocessusClignotant.h"
#include "xprocessusConduite.h"
#include "xprocessusBenne.h"
#include "processusVehicule.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:

/// @brief Fonction qui permet de tester certain module en activant 
//      leur requête tout de suite après leur initialisation
/// @param Aucun
void main_faitUnTest(void)
{
  
}
/// @brief Fonction qui fait l'initialisation de tout les modules permettant au fonctionnement global
/// @param  
void main_initialise(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:

void main_initialise(void)
{
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  ServiceCommunication_initialise();


  piloteEntree1_initialise();
  piloteIOT1_initialise(); 
  piloteI2C1_initialise();
  piloteUDP_initialise();
  
  interfaceMoteurBenne_initialise();
  interfaceEntree1_initialise();
  interfaceT1_initialise();

  processusClignotant_initialise();
  processusConduite_initialise();
  processusBenne_initialise();
  processusVehicule_initialise();
}

void setup(void) 
{
  serviceTank_initialise(); // Doit etre fais le plus vite possible a cause du bug des moteurs
  Serial.begin(115200);
  main_initialise();
  main_faitUnTest();
  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();
}

void loop(void) 
{
  serviceTaskServer_gestion.execute();
  serviceBaseDeTemps_gereDansLoop();   
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
//pas de fonctions publiques
