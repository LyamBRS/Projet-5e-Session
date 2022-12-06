//interfacePass:
//Historique: 
// 2021-04-15, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "piloteUDPStation.h"
#include "xpiloteUART2.h"
#include "interfacePass.h"
#include "serviceProtocole637.h"

//Definitions privees
//Declarations de fonctions privees:

//Definitions de variables privees:

//Definitions de fonctions privees:
void interfacePassUDPtoUart(void)
{
 int i;
  
 receiveUDP();
 /*readBuffer[0] = 'M'; 
 readBuffer[1] = 'E'; 
 readBuffer[2] = 'S'; 
 readBuffer[3] = 'S'; 
 readBuffer[4] = 'A'; 
 readBuffer[5] = 'G'; 
 readBuffer[6] = 'E'; 
 readBuffer[7] = 'S'; */
 if(readBuffer[0] != 0)
 {
   serviceProtocole637.nombreATransmettre = 0x08;
   serviceProtocole637.requete = REQUETE_ACTIVE;
 }
}
//******************************************************************************
void interfacePassUartToUDP(void)
{
  static unsigned char ucData = 0x00;
  static unsigned char ucLongueur = 0x00;
  static int i = 0;
  static unsigned char ucUarttoUDP[8] = {0,0,0,0,0,0,0,0};
  //transUDP(serviceProtocole637.octetsRecus, 8);

  ucData = piloteUART2_RX();

  if(ucData == 255)
  {
    //bruh moment
    return;
  }

  if(ucData == 0x08)
  {
    ucLongueur = 1;
    i = 0;
  }

  else if(ucLongueur == 1)
  {
    if(ucData == 0x00 && i<1)
    {
      ucLongueur = 0;
      return;
    }
    if(i == 0)
    {
      ucUarttoUDP[0] = ucData;
      i++;
    }
    else if(i == 1)
    {
     ucUarttoUDP[1] = ucData;
     i++;
    }
    else if(i == 2)
    {
     ucUarttoUDP[2] = ucData;
     i++;
    }
    else if(i == 3)
    {
     ucUarttoUDP[3] = ucData;
     i++;
    }
    else if(i == 4)
    {
     ucUarttoUDP[4] = ucData;
     i++;
    }
    else if(i == 5)
    {
     ucUarttoUDP[5] = ucData;
     i++;
    }
    else if(i == 6)
    {
     ucUarttoUDP[6] = ucData;
     i++;
    }
    else if(i == 7)
    {
     ucUarttoUDP[7] = ucData;
     transUDP(ucUarttoUDP, 8);
     i = 0;
     ucLongueur = 0x00;
     ucData = 0x00;
    }
  }
   //piloteUART2_TX(piloteUART2_RX());
}
//Definitions de variables publiques:

//Definitions de fonctions publiques:
void interfacePass_initialise(void)
{

}
