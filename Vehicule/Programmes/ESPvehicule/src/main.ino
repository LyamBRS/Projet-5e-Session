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
#include "xpilotePWMDroitHaut.h"
#include "xpilotePWMDroitBas.h"
#include "xpilotePWMGaucheHaut.h"
#include "xpilotePWMGaucheBas.h"
#include "xpiloteEntree1.h"
#include "xpiloteIOT1.h"
#include "xpiloteI2C1.h"

// Include des interfaces
#include "xserviceTaskServer.h"
#include "xserviceBaseDeTemps.h"

// Inlude des interfaces
#include "xinterfaceEntree1.h"
#include "xinterfaceT1.h"
#include "xinterfaceMoteurBenne.h"

// Include des processus
#include "xprocessusClignotant.h"




//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void main_faitUnTest(void)
{
//  processusMoteurPasAPas.pasRequis = PROCESSUSMOTEURPASAPAS_ARRET;
//  processusMoteurPasAPas.pasRequis = PROCESSUSMOTEURPASAPAS_SENS_HORAIRE_PAR_DEMI_PAS;
//  processusMoteurPasAPas.pasRequis = PROCESSUSMOTEURPASAPAS_SENS_ANTI_HORAIRE_PAR_DEMI_PAS;
//  processusMoteurPasAPas.pasRequis = PROCESSUSMOTEURPASAPAS_SENS_HORAIRE_PAR_DEMI_PAS;


}
void main_initialise(void);



//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void main_initialise(void)
{
  piloteEntree1_initialise();
  piloteIOT1_initialise();
  piloteAnalogue0_initialise();
  piloteAnalogue1_initialise();  
  piloteI2C1_initialise();
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  interfaceEntree1_initialise();
  interfaceT1_initialise();
  processusClignotant_initialise();
}

void setup(void) 
{
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
