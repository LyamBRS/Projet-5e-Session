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
void interfaceAscenseur_Descend(void);
void interfaceAscenseur_Monte(void);
void interfaceAscenseur_gere(void);

//Definitions de variables publiques:
unsigned char ucEtatA;
unsigned char ucDeplaceAscens;
//Definitions de fonctions publiques:
//****************************************************************************
void interfaceAscenseur_Descend(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Fais descendre l'ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
    //int ampoule = 0;

//interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AMPOULE,INTERFACEUSINE_OUTPUT_HIGH); // allume ampoule
    if (ucEtatA == 0)//1er pas
    {
        interfaceUsine_EcritUnElement(STEP0_Pin, INTERFACEUSINE_OUTPUT_HIGH);
        interfaceUsine_EcritUnElement(STEP1_Pin, INTERFACEUSINE_OUTPUT_LOW);
        interfaceUsine_EcritUnElement(STEP2_Pin, INTERFACEUSINE_OUTPUT_HIGH);
        interfaceUsine_EcritUnElement(STEP3_Pin, INTERFACEUSINE_OUTPUT_LOW);//FIN PARTIE 1
    }
    else if (ucEtatA == 1)//2eme pas
    {
        interfaceUsine_EcritUnElement(STEP0_Pin, INTERFACEUSINE_OUTPUT_HIGH);
        interfaceUsine_EcritUnElement(STEP1_Pin, INTERFACEUSINE_OUTPUT_LOW);
        interfaceUsine_EcritUnElement(STEP2_Pin, INTERFACEUSINE_OUTPUT_LOW);
        interfaceUsine_EcritUnElement(STEP3_Pin, INTERFACEUSINE_OUTPUT_HIGH);//FIN PARTIE 2
    }
    else if (ucEtatA == 2)//3eme pas
    {
        interfaceUsine_EcritUnElement(STEP0_Pin, INTERFACEUSINE_OUTPUT_LOW);
        interfaceUsine_EcritUnElement(STEP1_Pin, INTERFACEUSINE_OUTPUT_HIGH);
        interfaceUsine_EcritUnElement(STEP2_Pin, INTERFACEUSINE_OUTPUT_LOW);
        interfaceUsine_EcritUnElement(STEP3_Pin, INTERFACEUSINE_OUTPUT_HIGH);//FIN PARTIE 3
    }
    else if (ucEtatA == 3)//4eme pas
    {
        interfaceUsine_EcritUnElement(STEP0_Pin, INTERFACEUSINE_OUTPUT_LOW);
        interfaceUsine_EcritUnElement(STEP1_Pin, INTERFACEUSINE_OUTPUT_HIGH);
        interfaceUsine_EcritUnElement(STEP2_Pin, INTERFACEUSINE_OUTPUT_HIGH);
        interfaceUsine_EcritUnElement(STEP3_Pin, INTERFACEUSINE_OUTPUT_LOW);//FIN PARTIE 4
    }
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
 // ampoule++;
// interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AMPOULE,INTERFACEUSINE_OUTPUT_HIGH);  // Allume quand en bas
}
//****************************************************************************
void interfaceAscenseur_Monte(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Fais monter l'ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
 // interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AMPOULE,INTERFACEUSINE_OUTPUT_LOW); // Eteint quand monte
      if (ucEtatA == 0)//1er pas
      {
          interfaceUsine_EcritUnElement(STEP0_Pin, INTERFACEUSINE_OUTPUT_HIGH);
          interfaceUsine_EcritUnElement(STEP1_Pin, INTERFACEUSINE_OUTPUT_LOW);
          interfaceUsine_EcritUnElement(STEP2_Pin, INTERFACEUSINE_OUTPUT_HIGH);
          interfaceUsine_EcritUnElement(STEP3_Pin, INTERFACEUSINE_OUTPUT_LOW);//FIN PARTIE 1
      }
      else if (ucEtatA == 1)//2eme pas
      {
          interfaceUsine_EcritUnElement(STEP0_Pin, INTERFACEUSINE_OUTPUT_HIGH);
          interfaceUsine_EcritUnElement(STEP1_Pin, INTERFACEUSINE_OUTPUT_LOW);
          interfaceUsine_EcritUnElement(STEP2_Pin, INTERFACEUSINE_OUTPUT_LOW);
          interfaceUsine_EcritUnElement(STEP3_Pin, INTERFACEUSINE_OUTPUT_HIGH);//FIN PARTIE 2
      }
      else if (ucEtatA == 2)//3eme pas
      {
          interfaceUsine_EcritUnElement(STEP0_Pin, INTERFACEUSINE_OUTPUT_LOW);
          interfaceUsine_EcritUnElement(STEP1_Pin, INTERFACEUSINE_OUTPUT_HIGH);
          interfaceUsine_EcritUnElement(STEP2_Pin, INTERFACEUSINE_OUTPUT_LOW);
          interfaceUsine_EcritUnElement(STEP3_Pin, INTERFACEUSINE_OUTPUT_HIGH);//FIN PARTIE 3
      }
      else if (ucEtatA == 3)//4eme pas
      {
          interfaceUsine_EcritUnElement(STEP0_Pin, INTERFACEUSINE_OUTPUT_LOW);
          interfaceUsine_EcritUnElement(STEP1_Pin, INTERFACEUSINE_OUTPUT_HIGH);
          interfaceUsine_EcritUnElement(STEP2_Pin, INTERFACEUSINE_OUTPUT_HIGH);
          interfaceUsine_EcritUnElement(STEP3_Pin, INTERFACEUSINE_OUTPUT_LOW);//FIN PARTIE 4
      }
}
//****************************************************************************
void interfaceAscen_descend(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Fonction pour activer la descente de l'ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
    ucDeplaceAscens = 1;
}
//****************************************************************************
void interfaceAscen_monte(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Fonction pour activer la monter de l'ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
    ucDeplaceAscens = 2;
}
//****************************************************************************
void interfaceAscenseur_gere(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Fonctio pour gerer les deplacement de l'ascenseur suivant la base de temps
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
 static unsigned int ucCompteurTemps;
 static int nombreDeFoisAvantFinDes;
 ucCompteurTemps++;
 if (ucDeplaceAscens != 0)
 {
     if (ucCompteurTemps <= 10)//1er peut commencer?
     {
         ucEtatA = 0;
     }
     else if (ucCompteurTemps <= 20)//1er pas fini
     {
         ucEtatA = 1;
     }
     else if (ucCompteurTemps <= 30)//2eme pas fini
     {
         ucEtatA = 2;
     }
     else if (ucCompteurTemps <= 40)//3eme pas fini
     {
         ucEtatA = 3;
     }
     else if (ucCompteurTemps <= 50)//4eme pas fini
     {
         ucCompteurTemps = 0;
     }

     if (nombreDeFoisAvantFinDes <= 400)//Fin descente?
     {
         if (ucDeplaceAscens == 1)
         {
             interfaceAscenseur_Descend();
             nombreDeFoisAvantFinDes++;
         }
     }
     else
     {
         nombreDeFoisAvantFinDes = 0;
     }
     if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SW_ASC) != INTERFACEUSINE_SENSOR_LOW)// Arriver en haut?
     {
         if (ucDeplaceAscens == 2)
         {
             interfaceAscenseur_Monte();
         }
     }
 }
 else
 {
     ucCompteurTemps = 0;
 }
}
//****************************************************************************
void interfaceAscenseur_initialise(void)
//****************************************************************************
//   Auteur : Karl Naudin                 
//      Date de création : 22-12-12   
//   Description : Initialise l'ascenseur
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
{
  interfaceAscen_monte();
  serviceBaseDeTemps_execute[INTERFACEASCENSEUR_GERE] = interfaceAscenseur_gere;
}