//interfaceT4:
//Historique: 
// 2018-09-30, , creation

//INCLUSIONS
#include "main.h"
#include "piloteI2C.h"
#include "interfaceUsine.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
struct cartesI2CUsine
{
  unsigned char PCF1;
  unsigned char PCF2;
  unsigned char PCF3;
  unsigned char PCF4;
  unsigned char PCF5;
}
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:

void interfaceUsine_LED(unsigned char action)
{
  switch (action)
  {
    case ALLUME:
      cartesI2C.PCF1 &= 0xFE;
      break;
    case ETEINT:
      cartesI2C.PCF1 |= 0x01;
      break;
  }
}

void interfaceUsine_ventouse_Monte(unsigned char action)
{
  switch (action)
  {
    case ALLUME:
      cartesI2C.PCF1 &= 0xFE;
      break;
    case DESCEND:
      cartesI2C.PCF1 |= 0x01;
      break;
  }
}

void interfaceUsine_LED(unsigned char action)
{
  switch (action)
  {
    case ALLUME:
      cartesI2C.PCF1 &= 0xFE;
      break;
    case ETEINT:
      cartesI2C.PCF1 |= 0x01;
      break;
  }
}

void interfaceT4_initialise(void)
{
  piloteIOT4_metLaSortieA(INTERFACET4_VALEUR_POUR_ETEINDRE);
}

void interfaceUsine_Initialise ()
{
  
}


void interfaceUsine_LitUnBit (unsigned char entreeALire)
{
  switch entreeALire
}
