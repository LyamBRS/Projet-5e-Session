// interfaceBalance

#include <string.h>
#include "main.h"
#include "interfaceBalance.h"
#include "piloteUSBbal.h"


//char reponseinit[3000];


void interfaceBalance_prepareLecture(void)
{
  char commandebal[64]; 
  sprintf(commandebal, "P\n");
  interfaceBalance_ecritUneCommande(commandebal, 2);
  memset(commandebal, 0, 64);
}

void interfaceBalance_lit(char *reponse)
{
  interfaceBalance_recoitUneReponse(reponse,64);
  printf("Réponse: %s\n", reponse);
  fflush(stdout);
  
}

void interfaceBalance_changeUnite(void)
{
  char commandebal[64];
  sprintf(commandebal, "U\n");
  interfaceBalance_ecritUneCommande(commandebal, 2);
  memset(commandebal, 0, 64);
}

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