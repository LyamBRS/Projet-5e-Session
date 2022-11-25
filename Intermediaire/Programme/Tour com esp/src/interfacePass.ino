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
 readBuf[0] = 2; 
 readBuf[1] = 1; 
 readBuf[2] = '9'; 
 readBuf[3] = 'C'; 
 readBuf[4] = '6'; 
 readBuf[5] = 'B'; 
 readBuf[6] = 8; 
 readBuf[7] = 1; 
 if(readBuf[0] != 0)
 {
   for(i=0;i<8;i++)
   {
    piloteUART2_TX(readBuf[i]);
    //piloteUART2_TX(0x32);
    //delay(1);
   }
 }
}
//******************************************************************************
void interfacePassUartToUDP(void)
{
  int i;
  unsigned char ucUartToUDP[8] = {'M',4,'3','5','6','7','8','9'}; // debut test

  transUDP(ucUartToUDP,8);                                                 // fin test
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
