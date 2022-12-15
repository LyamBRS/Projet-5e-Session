//interfacePass:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteUSART2.h"
#include "piloteCAN1.h"
#include "interfacePass.h"
#include "serviceProtocole637.h"
#include "interfaceT2.h"
#include "interfaceT3.h"
#include "interfaceT4.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
//******************************************************************************
void interfacePassCANtoUart(void)
{// Convertit de reception CAN a transmission UART
  int i;
  unsigned char ucRecuCAN = PILOTECAN1_PAS_DISPONIBLE;
  static unsigned char WeAlreadyTransmitting = 0;

  if(piloteCAN1_messageDisponible() && !WeAlreadyTransmitting)//Message CAN dispo et pas deja transmis?
 {
   WeAlreadyTransmitting = 1;
   if(piloteCAN1_litUnMessageRecu(serviceProtocole637.octetsATransmettre) == PILOTECAN1_PAS_DISPONIBLE)
   {
     piloteCAN1_initialise();
   }
   interfaceT2_allume(); // ORANGE

   serviceProtocole637.requete = REQUETE_ACTIVE;
 }
 
 if(   serviceProtocole637.requete != REQUETE_ACTIVE)
 {
      WeAlreadyTransmitting = 0;
      interfaceT2_eteint();
 }
}

//******************************************************************************
void interfacePassUartToCAN(void)
{//Convertit de reception UART a transmission CAN
  int i;
  
  //regarde si du data est enregistrer dans le buffer
  if(serviceProtocole637.octetsRecus[7] != 0)
  {
    // Transmet le buffer en CAN
    piloteCAN1_transmetDesDonnes(0x0201,serviceProtocole637.octetsRecus,0x08);
    interfaceT3_allume(); // VERT
    //Reset le buffer a 0
    for(i=0; i<8; ++i)
    {
      serviceProtocole637.octetsRecus[i] = 0;
    }
    serviceProtocole637.information = INFORMATION_TRAITEE;
  }
}
//******************************************************************************
void interfacePass_initialise(void)
{
 
}


