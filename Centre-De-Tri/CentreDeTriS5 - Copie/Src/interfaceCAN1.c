//piloteCAN1:
//Historique: 
// 2018-11-12, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "interfaceCAN1.h"
#include "piloteCAN1.h"
//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Declarations de variables privees:

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned int interfaceCAN1_messageDisponible(void)
{
  return piloteCAN1_messageDisponible();
}

unsigned int interfaceCAN1_messageTransmis(void)
{
  return piloteCAN1_messageTransmis();
}

unsigned char interfaceCAN1_litUnMessageRecu(unsigned char *DonneesRecues)
{
  return piloteCAN1_litUnMessageRecu(DonneesRecues);
}

unsigned int interfaceCAN1_transmetDesDonnes(unsigned int Identification11Bits,
                                          unsigned char *Donnees,
                                          unsigned char Nombre)
{
  return piloteCAN1_transmetDesDonnes(Identification11Bits, Donnees, Nombre);
}

unsigned int interfaceCAN1_initialise(void)
{
  return piloteCAN1_initialise();
}
