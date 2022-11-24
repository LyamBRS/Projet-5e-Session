//interfacePass:
//Historique: 
// 2021-04-15, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "piloteUDPStation.h"
#include "xpiloteUART2.h"
#include "interfacePass.h"

//Definitions privees
//Declarations de fonctions privees:

//Definitions de variables privees:

//Definitions de fonctions privees:
void interfacePassUDPtoUart(void)
{
 int i;
  
 receiveUDP();
 if(readBuf[0] != 0)
 {
   for(i=0;i<8;i++)
   {
    piloteUART2_TX(readBuf[i]);
   }
 }
}
//******************************************************************************
void interfacePassUartToUDP(void)
{
  int i;

  if(Serial2.available())
  {
    unsigned char ucUartToUDP[8] = {0,0,0,0,0,0,0,0};

    ucUartToUDP[0] = piloteUART2_RX();
    if(ucUartToUDP[0] != 0)
    {
        transUDP(ucUartToUDP[0]);
        for(i=1;i<8;i++)
        {
          ucUartToUDP[i] = piloteUART2_RX();
          transUDP(ucUartToUDP[i]);
        }
    }

  }
}
//Definitions de variables publiques:

//Definitions de fonctions publiques:
void interfacePass_initialise(void)
{

}
