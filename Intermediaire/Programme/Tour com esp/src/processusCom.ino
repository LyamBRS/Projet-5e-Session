//processusClignotant:
//Historique: 
// 2022-04-11, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "piloteUDPStation.h"
#include "xpiloteUART2.h"
#include "xinterfaceT1.h"
#include "interfacePass.h"
#include "xserviceBaseDeTemps.h"
#include "xprocessusCom.h"
#include <stdio.h>

//Definitions privees
#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE  (\
  PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)
   
//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
unsigned long processusClignotant_compteur;

//Definitions de fonctions privees:
void processusClignotant_attendAvantDAllumerLeTemoinLumineux(void);
void processusClignotant_attendAvantDEteindreLeTemoinLumineux(void);

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
/******************************************************************************/
void processusClignotant_attendAvantDAllumerLeTemoinLumineux(void)
{
  static unsigned char ucControl = 0;
  interfacePassUDPtoUart();
<<<<<<< HEAD:Intermediaire/Programme/Tour com esp/src/processusClignotant.ino
<<<<<<< HEAD
=======
   if (Serial2.available()) 
{
>>>>>>> 4da58d318c6ea7a702745249341195bc18bc6aac:Intermediaire/Programme/Tour com esp/src/processusCom.ino
  interfacePassUartToUDP();
}
  interfaceT1_allume();
=======
  
  //ServiceUDPStation();
 // printf("OK voici un test \n");
  //ServiceUDP();
  //interfaceT1_allume();
>>>>>>> dee272e1a505a6efe1ca3ec339be59f1279cf86b
  processusClignotant_compteur = 0;
}
/******************************************************************************/
void processusClignotant_attendAvantDEteindreLeTemoinLumineux(void)
{ 
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE)
  {
    return;
  }
  interfaceT1_eteint();
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}
/******************************************************************************/
void processusCom_initialise(void)
{
  processusClignotant_compteur = 0;
  interfaceT1_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}
