//#############################################################################
/**
 * @file main.c
 * @author CamFo Camille Fortin
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
//247-527Atelier3a: programme de depart pour faire operer le ESP32 en mode cooperatif
//Historique:
// 2022-10-18, Yves Roy, creation a partir du programme 247-527Atelier3a

//INCLUSIONS
#include "xmain.h"
#include "xpiloteEntree1.h"
#include "xpiloteIOT1.h"
#include "xpiloteAnalogue0.h"
#include "xpiloteAnalogue1.h"
#include "xpiloteI2C1.h"
#include "xserviceTaskServer.h"
#include "xserviceBaseDeTemps.h"
#include "xinterfaceEntree1.h"
#include "xinterfaceT1.h"
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
