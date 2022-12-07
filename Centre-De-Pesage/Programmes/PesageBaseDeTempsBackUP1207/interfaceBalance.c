// interfaceBalance


#include "main.h"
#include "interfaceBalance.h"
#include "piloteUSBbal.h"


char reponseinit[3000];

int interfaceBalance_ecritUneCommande(char *Commande, unsigned char Longueur)
{
int retour;
  retour = piloteUSBbal_ecrit(Commande, Longueur);
  if (retour != (int)Longueur)
  {
    return -1;
  }
  piloteUSBbal_attendLaFinDeLEcriture();
  return retour;
}

int interfaceBalance_recoitUneReponse(char *Reponse, unsigned int LongueurMaximale)
{
  return piloteUSBbal_lit(Reponse, LongueurMaximale);  
}


int interfaceBalance_initialise(void)
{
    piloteUSBbal_initialise();
    return 0;
}