//piloteUART2:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteUART2.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
unsigned char piloteUART2_RX(void)
{
  unsigned char ucReceiveUART;

  return ucReceiveUART;
}

void piloteUART2_TX(unsigned char ucTransmitUART)
{
  
}

void piloteUART2_initialise(void)
{
 Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
}

