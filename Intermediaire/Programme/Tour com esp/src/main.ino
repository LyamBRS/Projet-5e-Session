//247-527Atelier3a: programme de depart pour faire operer le ESP32 en mode cooperatif
//Historique:
// 2022-10-18, Yves Roy, creation a partir du programme 247-527Atelier3a

//INCLUSIONS
#include "xmain.h"
#include "piloteUDPStation.h"
#include "xpiloteUART2.h"
#include "xpiloteEntree1.h"
#include "xpiloteAnalogue0.h"
#include "xpiloteAnalogue1.h"
#include "xserviceTaskServer.h"
#include "xserviceBaseDeTemps.h"
#include "serviceProtocole637.h"
#include "xinterfaceEntree1.h"
#include "xinterfaceT1.h"
#include "interfacePass.h"
#include "xprocessusCom.h"
#include <WiFi.h>
#include <WiFiUdp.h>


//Definitions privees
static const int RX_BUF_SIZE = 1024;
int num = 0;

//Declarations de fonctions privees:
void main_faitUnTest(void)
{
//interfacePassUartToUDP();
}
void main_initialise(void);



//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void main_initialise(void)
{
  piloteUDPStation_initialise();
  piloteUART2_initialise();
  piloteEntree1_initialise();
  piloteAnalogue0_initialise();
  piloteAnalogue1_initialise();  
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  serviceProtocole637_initialise();
  interfaceEntree1_initialise();
  interfaceT1_initialise();
  processusCom_initialise();
}

void setup(void) 
{
  Serial.begin(115200);
  main_initialise();
  main_faitUnTest();
  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();

//transUDP(ucUarttoUD, 8);
}

void loop(void) 
{
    // Read valeur sur buffeur
  serviceTaskServer_gestion.execute();
  serviceBaseDeTemps_gereDansLoop();   
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
//pas de fonctions publiques

