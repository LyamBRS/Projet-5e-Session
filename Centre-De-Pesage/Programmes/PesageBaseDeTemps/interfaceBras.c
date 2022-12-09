// InterfaceBras


#include "main.h"
#include "interfaceBras.h"
#include "piloteSerieUSB.h"


char reponseinit[3000];

int interfaceBras_ecritUneCommande(char *Commande, unsigned char Longueur)
{
int retour;
  retour = piloteSerieUSB_ecrit(Commande, Longueur);
  if (retour != (int)Longueur)
  {
    return -1;
  }
  piloteSerieUSB_attendLaFinDeLEcriture();
  return retour;
}

int interfaceBras_recoitUneReponse(char *Reponse, unsigned int LongueurMaximale)
{
  return piloteSerieUSB_lit(Reponse, LongueurMaximale);  
}


int interfaceBras_initialise(void)
{
    if(piloteSerieUSB_initialise() < 0)
    {
      return -1;
    }
    return 0;
}