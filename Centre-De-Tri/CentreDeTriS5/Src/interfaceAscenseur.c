//interfaceAscenseur:
//Historique: 
// 2022-12-08, Karl Naudin, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceAscenseur.h"
#include "interfaceUsine.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:

//Definitions de fonctions publiques:
/*********************************************************************************************************************/
void interfaceAscenseur_BaseDeTemps(unsigned char *ucLisBaseTempsAscenseur)
{
static unsigned char ucCompteurAscenseur = 0;
  if(ucCompteurAscenseur == 20)
  {
    *ucLisBaseTempsAscenseur = 20;
    return;
  }
  *ucLisBaseTempsAscenseur = ucCompteurAscenseur;
}
/*********************************************************************************************************************/
void interfaceAscenseur_Descend(void)
{
    unsigned char ucBasetemps = 0;
    int nombreDeFoisAvantFinDes = 0;
    //int ampoule = 0;

//interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AMPOULE,INTERFACEUSINE_OUTPUT_HIGH); // allume ampoule
while(nombreDeFoisAvantFinDes < 100)// Arriver en bas?
 {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q1,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q2,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q3,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q4,INTERFACEUSINE_OUTPUT_LOW);//FIN PARTIE 1
     while(ucBasetemps != 20)//10ms?
  {
    interfaceAscenseur_BaseDeTemps(&ucBasetemps);
  };
  ucBasetemps = 0;
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q1,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q2,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q3,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q4,INTERFACEUSINE_OUTPUT_HIGH);//FIN PARTIE 2
     while(ucBasetemps != 20)//10ms?
  {
    interfaceAscenseur_BaseDeTemps(&ucBasetemps);
  };
  ucBasetemps = 0;
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q1,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q2,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q3,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q4,INTERFACEUSINE_OUTPUT_HIGH);//FIN PARTIE 3
     while(ucBasetemps != 20)//10ms?
  {
    interfaceAscenseur_BaseDeTemps(&ucBasetemps);
  };
  ucBasetemps = 0;
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q1,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q2,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q3,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q4,INTERFACEUSINE_OUTPUT_LOW);//FIN PARTIE 4
     while(ucBasetemps != 20)//10ms?
  {
    interfaceAscenseur_BaseDeTemps(&ucBasetemps);
  };
  ucBasetemps = 0;
 /* if(ampoule == 10)                                                                      // Clignote del
  {
    ampoule = interfaceUsine_LitUnElement(INTERFACEUSINE_ID_AMPOULE);
    if(ampoule == 1)
    {
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AMPOULE,INTERFACEUSINE_OUTPUT_LOW);
    }
    else
    {
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AMPOULE,INTERFACEUSINE_OUTPUT_HIGH);
    }
    ampoule = 0;*/
 // }
  nombreDeFoisAvantFinDes++;
 // ampoule++;
 };
// interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AMPOULE,INTERFACEUSINE_OUTPUT_HIGH);  // Allume quand en bas
}
/*****************************************************************************************************/
void interfaceAscenseur_Monte(void)
{
  unsigned char ucBasetemps = 0;
 // interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AMPOULE,INTERFACEUSINE_OUTPUT_LOW); // Eteint quand monte
  while(interfaceUsine_LitUnElement(INTERFACEUSINE_ID_ASCENSEUR_CAPTEUR) != INTERFACEUSINE_OUTPUT_LOW)// Arriver en haut?
 {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q1,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q2,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q3,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q4,INTERFACEUSINE_OUTPUT_LOW);//FIN PARTIE 1
     while(ucBasetemps != 20)//10ms?
  {
    interfaceAscenseur_BaseDeTemps(&ucBasetemps);
  };
  ucBasetemps = 0;
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q1,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q2,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q3,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q4,INTERFACEUSINE_OUTPUT_HIGH);//FIN PARTIE 2
     while(ucBasetemps != 20)//10ms?
  {
    interfaceAscenseur_BaseDeTemps(&ucBasetemps);
  };
  ucBasetemps = 0;
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q1,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q2,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q3,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q4,INTERFACEUSINE_OUTPUT_HIGH);//FIN PARTIE 3
     while(ucBasetemps != 20)//10ms?
  {
    interfaceAscenseur_BaseDeTemps(&ucBasetemps);
  };
  ucBasetemps = 0;
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q1,INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q2,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q3,INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ASCENSEUR_Q4,INTERFACEUSINE_OUTPUT_LOW);//FIN PARTIE 4
     while(ucBasetemps != 20)//10ms?
  {
    interfaceAscenseur_BaseDeTemps(&ucBasetemps);
  };
  ucBasetemps = 0;
 };
}
/*********************************************************************************************************/
void interfaceAscenseur_initialise(void)
{
  interfaceAscenseur_Monte();
}