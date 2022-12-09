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
{
  int i;
  unsigned char ucRecuCAN = PILOTECAN1_PAS_DISPONIBLE;
  static unsigned char WeAlreadyTransmitting = 0;

  if(piloteCAN1_messageDisponible() && !WeAlreadyTransmitting)
 {
   WeAlreadyTransmitting = 1;
   piloteCAN1_litUnMessageRecu(serviceProtocole637.octetsATransmettre);
   // Doesnt go there
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
{
  int i;
  
  //Check if there is data stored inside the buffer
  if(serviceProtocole637.octetsRecus[7] != 0)
  {
    // Transmit the buffer on can
    piloteCAN1_transmetDesDonnes(0x0201,serviceProtocole637.octetsRecus,0x08);
    interfaceT3_allume(); // GREEN
    //Reset the buffer back to 0
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


