//interfacePont:
//Historique: 
// 2022-12-08, Karl Naudin, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfacePont.h"
#include "interfaceUsine.h"
#include "interfaceT4.h"
//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
bool interfacePont_ReadyForOperation(void);
bool interfacePont_AckStart(void);
bool interfacePont_MotionComplete(void);
void interfacePont_Error(void);
void interfacePont_gere(void);
bool interfacePont_Position0(void);
bool interfacePont_Position1(void);
bool interfacePont_Position2(void);
void resetIOPositions (void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
void (*interfacePont_execute)(void);
unsigned char ucPosition;
unsigned char ucResultatDeplacement;
unsigned char ucError;
extern unsigned char ucResultatDeplacement;
extern unsigned char ucError;
unsigned char compteurPont; 
unsigned char ucEtat;


//Definitions de fonctions publiques:
//****************************************************************************
bool interfacePont_Position0(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : gere la position au dessus du convoyeur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : bool pour savoir si fonction fini               
//   Variables utilisées : Aucun.
{
  if(ucEtat == 1)//Envoie la position?
  {
   if(interfacePont_ReadyForOperation() == INTERFACEUSINE_SENSOR_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
   {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0,INTERFACEUSINE_OUTPUT_HIGH);
  }
  else if(ucEtat == 2)//Envoie un start
  {
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
   if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU?
   {return 0;}
  }
  else if(ucEtat == 3)//Verifie si deplacement fini
  {
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {
    resetIOPositions();
    ucPosition = 3;
    ucEtat = 0;
    return 1;
  }
  return 0;
  }
  return ucEtat;
}
//****************************************************************************
bool interfacePont_Position1(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Gere la position au dessus du bac
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : bool pour savoir si fonction fini                    
//   Variables utilisées : Aucun.
{
  
  if(ucEtat == 1)//Envoie la position?
  {
   if(interfacePont_ReadyForOperation() == INTERFACEUSINE_SENSOR_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
   {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1,INTERFACEUSINE_OUTPUT_HIGH);
  }
  else if(ucEtat == 2)//Envoie un start
  {
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
   if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU?
   {return 0;}
  }
  else if(ucEtat == 3)//Verifie si deplacement fini
  {
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {
    resetIOPositions();
    ucPosition = 3;
    ucEtat = 0;
    return 1;
  }
  return 0;
  }
  return ucEtat;
}
//****************************************************************************
bool interfacePont_Position2(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Gere position au dessus de l'ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : bool pour savoir si fonction fini                   
//   Variables utilisées : Aucun.
{
  
 if(ucEtat == 1)//Envoie la position?
  {
   if(interfacePont_ReadyForOperation() == INTERFACEUSINE_SENSOR_LOW)  // CONTROLLER RELEASE PAS ACTIVER?
   {return 0;}
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0,INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2,INTERFACEUSINE_OUTPUT_HIGH);
  }
  else if(ucEtat == 2)//Envoie un start
  {
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_HIGH);
   if(interfacePont_AckStart() == INTERFACEUSINE_OUTPUT_HIGH)         // ACK START PAS RECU?
   {return 0;}
  }
  else if(ucEtat == 3)//Verifie si deplacement fini
  {
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START,INTERFACEUSINE_OUTPUT_LOW);
  
  if(interfacePont_MotionComplete())                                 // MOTION COMPLETE?
  {
    //resetIOPositions();
    ucPosition = 3;
    ucEtat = 0;
    return 1;
  }
  return 0;
  }
  return ucEtat;
}

//****************************************************************************
//Definitions de fonctions privées:
//****************************************************************************
void interfacePont_gere(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Gere le pont et ses fonctions
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
  static unsigned int ucCompteurTemps;
  if (ucEtat != 0)
  {
    ucCompteurTemps++;
  }
  else ucCompteurTemps = 0;
  if (ucPosition == 3) interfaceT4_allume();
  else interfaceT4_eteint();

  if (ucEtat == 0)//Position recu?
  {
    if(ucPosition != 3)//Position valide?
    {
      ucEtat = 1;
    }
    else
    {ucCompteurTemps = 0;}
  }
    

  if(ucCompteurTemps == 200)//Position recu fini?
  {ucEtat = 2;}
  else if(ucCompteurTemps == 500)//Ack start recu?
  {
   ucEtat = 3;
  }

if(ucCompteurTemps >= 6)
{
 if(ucPosition == 0)//dessus convoyeur
 {
  ucResultatDeplacement = interfacePont_Position0();
 }
 else if(ucPosition == 1)//dessus bac
 {
  ucResultatDeplacement = interfacePont_Position1();
 }
 else if(ucPosition == 2)//dessus ascenseur
 {
  ucResultatDeplacement = interfacePont_Position2();
 }
 interfacePont_Error();
}
}

void interfacePont_pos0 (void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Active position convoyeur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
  ucPosition = 0;
}
void interfacePont_pos1 (void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Active position bac
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
  ucPosition = 1;
}
void interfacePont_pos2 (void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Active position ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
  ucPosition = 2;
}
bool interfacePont_fini (void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Verifie que le deplacement a la position est fini
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : retourne si postion fini                
//   Variables utilisées : Aucun.
{
  return(ucPosition == 3);
}

void resetIOPositions (void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : reinitialise a la position initiale
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1,INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2,INTERFACEUSINE_OUTPUT_LOW);
}
//****************************************************************************
bool interfacePont_ReadyForOperation(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : verifie que le pont est activer
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : retourne etat du pont                
//   Variables utilisées : Aucun.
{
 return interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_READY_FOR_OPERATION);
}
//****************************************************************************
bool interfacePont_AckStart(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Initialise l'ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : retourne etat du ack start              
//   Variables utilisées : Aucun.
{
  return interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_ACK_START);
}
//****************************************************************************
bool interfacePont_MotionComplete(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Verifie que le deplacement du pont est fini
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : retourne etat du deplacement                
//   Variables utilisées : Aucun.
{
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_MOTION_COMPLETE) == INTERFACEUSINE_SENSOR_HIGH)  return 1;
  else return 0;
}
//****************************************************************************
void interfacePont_Error(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Initialise l'ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : verifie qu'il n'y a pas d'erreur                
//   Variables utilisées : Aucun.
{
  /*
  if(interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_ERROR == INTERFACEUSINE_SENSOR_LOW)) // RECEIVE ERROR?
  {
    ucError = 0;
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER,INTERFACEUSINE_OUTPUT_LOW);
  }                                                                                                  // STOP PONT
  ucError = 1;
  */
}
//****************************************************************************
void interfacePont_initialise(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Initialise le pont
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER,INTERFACEUSINE_OUTPUT_HIGH);
  ucPosition = 3;
  serviceBaseDeTemps_execute[INTERFACEPONT_GERE] = interfacePont_gere;
}
//****************************************************************************