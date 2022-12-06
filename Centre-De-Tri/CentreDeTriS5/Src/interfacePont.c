//interfaceT4:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "interfacePont.h"
#include "interfaceUsine.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
bool interfacePont_ReadyForOperation(void);
bool interfacePont_AckStart(void);
bool interfacePont_MotionComplete(void);
//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
bool interfacePont_Position0(void)
{
  if(interfacePont_ReadyForOperation() == INTERFACEUSINE_OUTPUT_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0,INTERFACEUSINE_OUTPUT_HIGH);
  if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {return 1;}
}

bool interfacePont_Position1(void)
{
  if(interfacePont_ReadyForOperation() == INTERFACEUSINE_OUTPUT_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1,INTERFACEUSINE_OUTPUT_HIGH);
  if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {return 1;}
}

bool interfacePont_Position2(void)
{
  if(interfacePont_ReadyForOperation() == INTERFACEUSINE_OUTPUT_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2,INTERFACEUSINE_OUTPUT_HIGH);
  if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU
  {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {return 1;}
}

void interfacePont_initialise(void)
{
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER,INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2,INTERFACEUSINE_OUTPUT_LOW);
}
//Definitions de fonctions privées:
bool interfacePont_ReadyForOperation(void)
{
 return interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_READY_FOR_OPERATION);
}

bool interfacePont_AckStart(void)
{
  return interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_ACK_START);
}

bool interfacePont_MotionComplete(void)
{
  while (INTERFACEUSINE_ID_PONT_DEFAULT_MOTION_COMPLETE != INTERFACEUSINE_OUTPUT_HIGH)
  {}
  return 1;
}

