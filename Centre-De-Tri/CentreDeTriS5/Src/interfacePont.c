//interfacePont:
//Historique: 
// 2022-12-08, Karl Naudin, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfacePont.h"
#include "interfaceUsine.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
bool interfacePont_ReadyForOperation(void);
bool interfacePont_AckStart(void);
bool interfacePont_MotionComplete(void);
void interfacePont_Error(void);
void interfacePont_gere(void);
//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
void (*interfacePont_execute)(void);
unsigned char ucPosition;
unsigned char ucResultatDeplacement;
unsigned char ucError;

//Definitions de fonctions publiques:
/*********************************************************************************************************************/
void BaseDeTempsPont(unsigned char *ucLisBaseTempsPont)
{
static unsigned char ucCompteurPont = 0;
  if(ucCompteurPont == 6)
  {
    *ucLisBaseTempsPont = 6;
    return;
  }
  *ucLisBaseTempsPont = ucCompteurPont;
}
/*********************************************************************************************************************/
bool interfacePont_Position0(void)
{
  unsigned char ucBasetemps = 0;
  if(interfacePont_ReadyForOperation() == INTERFACEUSINE_OUTPUT_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
   while(ucBasetemps != 6)
  {
    BaseDeTempsPont(&ucBasetemps);
  };
  ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0,INTERFACEUSINE_OUTPUT_HIGH);
  if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU
  {return 0;}
   while(ucBasetemps != 6)
  {
    BaseDeTempsPont(&ucBasetemps);
  };
  ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {return 1;}
  return 0;
}
/*********************************************************************************************************************/
bool interfacePont_Position1(void)
{
  static unsigned char ucBasetemps = 0;
  if(interfacePont_ReadyForOperation() == INTERFACEUSINE_OUTPUT_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
   while(ucBasetemps != 6)
  {
    BaseDeTempsPont(&ucBasetemps);
  };
  ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1,INTERFACEUSINE_OUTPUT_HIGH);
  if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU
  {return 0;}
   while(ucBasetemps != 6)
  {
    BaseDeTempsPont(&ucBasetemps);
  };
  ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {return 1;}
  return 0;
}
/*********************************************************************************************************************/
bool interfacePont_Position2(void)
{
  static unsigned char ucBasetemps = 0;
  if(interfacePont_ReadyForOperation() == INTERFACEUSINE_OUTPUT_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
   while(ucBasetemps != 6)
  {
    BaseDeTempsPont(&ucBasetemps);
  };
  ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2,INTERFACEUSINE_OUTPUT_HIGH);
  if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU
  {return 0;}
   while(ucBasetemps != 6)
  {
    BaseDeTempsPont(&ucBasetemps);
  };
  ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {return 1;}
  return 0;
}
/*********************************************************************************************************************/
void interfacePont_initialise(void)
{
  static unsigned char ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER,INTERFACEUSINE_OUTPUT_HIGH);
  while(ucBasetemps != 6)
  {
    BaseDeTempsPont(&ucBasetemps);
  };
  ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  while(ucBasetemps != 6)
  {
    BaseDeTempsPont(&ucBasetemps);
  };
  ucBasetemps = 0;
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2,INTERFACEUSINE_OUTPUT_LOW);
  interfacePont_execute = interfacePont_gere;
}
/*********************************************************************************************************************/
//Definitions de fonctions privées:
/*********************************************************************************************************************/
void interfacePont_gere(void)
{
 if(ucPosition == 0)
 {
  ucResultatDeplacement = interfacePont_Position0();
 }
 else if(ucPosition == 1)
 {
  ucResultatDeplacement = interfacePont_Position1();
 }
 else if(ucPosition == 2)
 {
  ucResultatDeplacement = interfacePont_Position2();
 }
 ucPosition = 3;
 interfacePont_Error();
}
/*********************************************************************************************************************/
bool interfacePont_ReadyForOperation(void)
{
 return interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_READY_FOR_OPERATION);
}
/*********************************************************************************************************************/
bool interfacePont_AckStart(void)
{
  return interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_ACK_START);
}
/*********************************************************************************************************************/
bool interfacePont_MotionComplete(void)
{
  while (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_MOTION_COMPLETE != INTERFACEUSINE_OUTPUT_HIGH))
  {};
  return 1;
}
/*********************************************************************************************************************/
void interfacePont_Error(void)
{
  if(interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_ERROR == INTERFACEUSINE_OUTPUT_LOW)) // RECEIVE ERROR?
  {
    ucError = 0;
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER,INTERFACEUSINE_OUTPUT_LOW);
  }                                                                                                  // STOP PONT
  ucError = 1;
}
/*********************************************************************************************************************/