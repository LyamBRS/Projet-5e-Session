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
  
 //receiveUDP();
 readBuffer[0] = 'M'; 
 readBuffer[1] = 'E'; 
 readBuffer[2] = 'S'; 
 readBuffer[3] = 'S'; 
 readBuffer[4] = 'A'; 
 readBuffer[5] = 'G'; 
 readBuffer[6] = 'E'; 
 readBuffer[7] = 'S'; 
 if(readBuffer[0] != 0)
 {
   for(i=0;i<8;i++)
   {
    piloteUART2_TX(readBuffer[i]);
   }
 }
}
//******************************************************************************
void interfacePassUartToUDP(void)
{
  int i;
  unsigned char ucUartToUDP[8] = {'M',4,0,0,0,0,0,0}; // debut test

  //transUDP(ucUartToUDP,8);                                                 // fin test
 // if(Serial2.available())
 // {
    //unsigned char ucUartToUDP[8] = {0,0,0,0,0,0,0,0};
    ////unsigned char ucUartToUDP[8] = {28,29,10,98,17,7,3,57};
//
    //ucUartToUDP[0] = piloteUART2_RX();
    //if(ucUartToUDP[0] != 0)
    //{
    //    transUDP(ucUartToUDP[0]);
    //    for(i=1;i<8;i++)
    //    {
    //      ucUartToUDP[i] = piloteUART2_RX();
    //      transUDP(ucUartToUDP[i]);
    //    }
    //}
//
 // }
}
//Definitions de variables publiques:

//Definitions de fonctions publiques:
void interfacePass_initialise(void)
{

}
