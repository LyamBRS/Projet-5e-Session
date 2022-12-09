//interfaceColonne:
//Historique: 
// 2018-09-24, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceColonne.h"
#include "piloteColonne.h"
//Definitions privees
#define VITESSECLIGNOTANT 2000 //période en 1/2ms
#define ETEINT 0
#define ALLUME 1
#define CLIGNOTE 2


    
//Declarations de fonctions privees:
void interfaceColonne_allume(unsigned char couleur);
void interfaceColonne_eteint(unsigned char couleur);
void interfaceColonne_clignote(unsigned char couleur);

unsigned char etatRouge = ETEINT;
unsigned char etatVert = ETEINT;
unsigned char etatJaune = ETEINT;

//Definitions de variables privees:
unsigned int interfaceColonne_compteur;

//Definitions de fonctions privees:
void interfaceColonne_gere(void)
{
  interfaceColonne_compteur++;
  if (interfaceColonne_compteur == VITESSECLIGNOTANT/2)
  {
    if (etatRouge == CLIGNOTE)piloteColonne_allume(PILOTECOLONNE_ROUGE);
    if (etatVert == CLIGNOTE)piloteColonne_allume(PILOTECOLONNE_VERT);
    if (etatJaune == CLIGNOTE)piloteColonne_allume(PILOTECOLONNE_JAUNE);
  }
    if (interfaceColonne_compteur >= VITESSECLIGNOTANT)
  {
    if (etatRouge == CLIGNOTE)piloteColonne_eteint(PILOTECOLONNE_ROUGE);
    if (etatVert == CLIGNOTE)piloteColonne_eteint(PILOTECOLONNE_VERT);
    if (etatJaune == CLIGNOTE)piloteColonne_eteint(PILOTECOLONNE_JAUNE);
    interfaceColonne_compteur = 0;
  }
  
  
}

void interfaceColonne_allume(unsigned char couleur)
{
  switch (couleur)
  {
    case (INTERFACECOLONNE_ROUGE):
    etatRouge = ALLUME;
    piloteColonne_allume(PILOTECOLONNE_ROUGE);
    break;
    case (INTERFACECOLONNE_VERT):
    etatVert = ALLUME;
    piloteColonne_allume(PILOTECOLONNE_VERT);
    break;
    case (INTERFACECOLONNE_JAUNE):
    etatJaune = ALLUME;
    piloteColonne_allume(PILOTECOLONNE_JAUNE);
    break;
  }
}
void interfaceColonne_eteint(unsigned char couleur)
{
  switch (couleur)
  {
    case (INTERFACECOLONNE_ROUGE):
    etatRouge = ALLUME;
    piloteColonne_eteint(PILOTECOLONNE_ROUGE);
    break;
    case (INTERFACECOLONNE_VERT):
    etatVert = ALLUME;
    piloteColonne_eteint(PILOTECOLONNE_VERT);
    break;
    case (INTERFACECOLONNE_JAUNE):
    etatJaune = ALLUME;
    piloteColonne_eteint(PILOTECOLONNE_JAUNE);
    break;
  }
}
void interfaceColonne_clignote(unsigned char couleur)
{
  switch (couleur)
  {
    case (INTERFACECOLONNE_ROUGE):
    etatRouge = CLIGNOTE;
    break;
    case (INTERFACECOLONNE_VERT):
    etatVert = CLIGNOTE;
    break;
    case (INTERFACECOLONNE_JAUNE):
    etatJaune = CLIGNOTE;
    break;
  }
}
//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceColonne_initialise(void)
{
  interfaceColonne_compteur = 0;
  piloteColonne_eteint(PILOTECOLONNE_ROUGE);
  piloteColonne_eteint(PILOTECOLONNE_VERT);
  piloteColonne_eteint(PILOTECOLONNE_JAUNE);
  etatRouge = ETEINT;
  etatVert = ETEINT;
  etatJaune = ETEINT;
  serviceBaseDeTemps_execute[INTERFACECOLONNE_PHASE] =
      interfaceColonne_gere;
}
