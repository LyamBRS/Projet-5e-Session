/**
 * @file processusUsine.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "piloteCAN1.h"
#include "processusUsine.h"
#include "piloteI2C.h"
#include "interfaceT1.h"
#include "interfaceT2.h"
#include "interfaceT4.h"
#include "interfaceUsine.h"
#include "interfaceColonne.h"
#include <string.h>
#include "interfaceB1.h"
//Definitions privees
//Les unités des valeurs de délai suivantes corerespondent à la base de temps : 1/2ms
#define DELAI_MAX_INITIALISATION 5000
#define DELAI_MAX_EJECTION 1000
#define DELAI_MAX_DETECTION 1000
#define DELAI_AVANT_DETECTION 100
#define DELAI_MAX_ELEVATEUR_HAUT 10000
#define DELAI_MAX_ATTEND_CHUTE 10000
#define DELAI_VENTOUSE_DESCEND 1000

#define BLOC_AUCUN 0
#define BLOC_ROUGE 1
#define BLOC_NOIR 2
#define BLOC_METAL 3

#define ETAT_CAPTEUR_CAP_POUR_BLOC_NOIR 1
#define ETAT_CAPTEUR_MAG_POUR_BLOC_NOIR 0
#define ETAT_CAPTEUR_OPT_POUR_BLOC_NOIR 0

#define ETAT_CAPTEUR_CAP_POUR_BLOC_ROUGE 1
#define ETAT_CAPTEUR_MAG_POUR_BLOC_ROUGE 0
#define ETAT_CAPTEUR_OPT_POUR_BLOC_ROUGE 1

#define ETAT_CAPTEUR_CAP_POUR_BLOC_METAL 1
#define ETAT_CAPTEUR_MAG_POUR_BLOC_METAL 1
#define ETAT_CAPTEUR_OPT_POUR_BLOC_METAL 1

#define ETAT_CAPTEUR_CAP_POUR_BLOC_AUCUN 0
#define ETAT_CAPTEUR_MAG_POUR_BLOC_AUCUN 0
#define ETAT_CAPTEUR_OPT_POUR_BLOC_AUCUN 0
//Declarations de fonctions privees:
void modeOperation_lanceInitialisation (void);
void modeOperation_attendFinInitialisation (void);
void modeOperation_pousseUnBloc (void);
void modeOperation_detecteLeBloc (void);
void modeOperation_monteElevateur (void);
void modeOperation_attendElevateurEnHaut (void);
void modeOperation_ejecteUnBloc (void);
void modeOperation_attendBlocChute (void);
void modeOperation_attendBlocAspire(void);

void modeErreur (void);
//Definitions de variables privees:
void (*modeOperation_execute)(void);
void (*modeTest_execute)(void);

unsigned char ucTypeDeBloc;
//string messageErreur;


//Definitions de fonctions privees:

/**
 * @brief Fonction qui gère le fonct...
 * @author Renaud Gagnon
 * @date 2022-11-18
 * @param void aucun paramètre d'entrée
 * @return void 
 * @warning
 * @example 
 */
// Références: \ref "variable" crée un lien cliquable qui mène a la variable ou a la fonction
void processusUsine_attente (void)
{
  updateModeEcran("Attente");
  interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
  interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
  interfaceColonne_clignote(INTERFACECOLONNE_VERT);
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_BOUTON_VERT) == INTERFACEUSINE_BOUTON_APPUYE) serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_operation;
  if (interfaceB1.etatDuBouton == INTERFACEB1_APPUYE) serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_attente;
}

void processusUsine_operation (void)
{
  updateModeEcran("Operation");
  modeOperation_execute();
  
}
#pragma region EtatsModeOperation

void modeOperation_lanceInitialisation (void)
{
  ucTypeDeBloc = BLOC_AUCUN;
  
  //Lumière
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ETEINT);
  
  //EJECTEUR
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT, INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_IN, INTERFACEUSINE_OUTPUT_HIGH);
  
  //VENTOUSE
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_LOW);
  
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_HIGH);
  
  //CONVOYEUR
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_LOW);
  
  //POUSSOIR MAGASIN
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_POUSSOIR, INTERFACEUSINE_OUTPUT_LOW);
  
  //Pont
  //interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0, INTERFACEUSINE_OUTPUT_HIGH);
  //interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START, INTERFACEUSINE_OUTPUT_HIGH);
  modeOperation_execute = modeOperation_attendFinInitialisation;
}

void modeOperation_attendFinInitialisation (void)
{
  static unsigned int compteurTempsInitialisation = 0;
  compteurTempsInitialisation++;
  if (compteurTempsInitialisation >= DELAI_MAX_INITIALISATION)
  {
    updateMessageEcran("Erreur d'initialisation");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
  }
  
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_POUSSOIR_OUT) != INTERFACEUSINE_SENSOR_LOW)return;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_POUSSOIR_IN) != INTERFACEUSINE_SENSOR_HIGH)return;
  //ELEVATEUR
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_MONTE, INTERFACEUSINE_OUTPUT_LOW);
  
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_ELEVATEUR_BAS) != INTERFACEUSINE_SENSOR_HIGH)return;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_EJECTEUR_IN) != INTERFACEUSINE_SENSOR_HIGH)return;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_CHUTE) != INTERFACEUSINE_SENSOR_LOW)return;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) != INTERFACEUSINE_SENSOR_LOW)return;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) != INTERFACEUSINE_SENSOR_LOW)return;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) != INTERFACEUSINE_SENSOR_LOW)return;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_VENTOUSE_HAUT) != INTERFACEUSINE_SENSOR_HIGH)return;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_VENTOUSE_BAS) != INTERFACEUSINE_SENSOR_LOW)return;
  
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ALLUME);
  modeOperation_execute = modeOperation_pousseUnBloc;
}

void modeOperation_pousseUnBloc (void)
{
  static unsigned int compteurTempsEjectionBloc = 0;
  compteurTempsEjectionBloc++;
  if (compteurTempsEjectionBloc >= DELAI_MAX_EJECTION)
  {
    //messageErreur = "Erreur d'ejection";
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
  }

  //Éjecte le bloc
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_POUSSOIR) == INTERFACEUSINE_OUTPUT_LOW)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_POUSSOIR, INTERFACEUSINE_OUTPUT_HIGH);
  }

  //Éjection terminée
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_POUSSOIR_OUT) == INTERFACEUSINE_SENSOR_HIGH)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_POUSSOIR, INTERFACEUSINE_OUTPUT_LOW);
    modeOperation_execute = modeOperation_detecteLeBloc;
  }
}

void modeOperation_detecteLeBloc (void)
{
  static unsigned int compteurTempsDetectionBloc = 0;
  compteurTempsDetectionBloc++;
  if (compteurTempsDetectionBloc >= DELAI_MAX_DETECTION + DELAI_AVANT_DETECTION)
  {
    //messageErreur = "Erreur de détection";
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
  }

  if (compteurTempsDetectionBloc >= DELAI_AVANT_DETECTION)
  {
    if (
        interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_ROUGE
          && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_ROUGE
            && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_ROUGE
              )
    {
      ucTypeDeBloc = BLOC_ROUGE;
      interfaceColonne_allume(INTERFACECOLONNE_JAUNE);
      interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
      modeOperation_execute = modeOperation_monteElevateur;
    }
    
    if (
        interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_NOIR
          && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_NOIR
            && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_NOIR
              )
    {
      ucTypeDeBloc = BLOC_NOIR;
      interfaceColonne_clignote(INTERFACECOLONNE_JAUNE);
      interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
      modeOperation_execute = modeOperation_monteElevateur;
    }
    
    if (
        interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_METAL
          && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_METAL
            && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_METAL
              )
    {
      ucTypeDeBloc = BLOC_METAL;
      interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
      interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
      interfaceColonne_allume(INTERFACECOLONNE_VERT);
      modeOperation_execute = modeOperation_monteElevateur;
    }
    
    if (
        interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_AUCUN
          && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_AUCUN
            && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_AUCUN
              )
    {
      ucTypeDeBloc = BLOC_AUCUN;
      //messageErreur = "Erreur pas de bloc";
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
    }
  }
  
}

void modeOperation_monteElevateur (void)
{
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_ELEVATEUR_BAS) == INTERFACEUSINE_SENSOR_HIGH)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_DESCEND, INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_MONTE, INTERFACEUSINE_OUTPUT_HIGH);
    modeOperation_execute = modeOperation_attendElevateurEnHaut;
    return;
  }
  //messageErreur = "Erreur elevateur pas en bas";
  serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
}


void modeOperation_attendElevateurEnHaut (void)
{
  static unsigned int compteurTempsElevateurEnHaut = 0;
  compteurTempsElevateurEnHaut++;
  if (compteurTempsElevateurEnHaut >= DELAI_MAX_ELEVATEUR_HAUT)
  {
    //messageErreur = "Erreur montee de l'elevateur";
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
  }

  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_ELEVATEUR_HAUT) == INTERFACEUSINE_SENSOR_HIGH)
  {
    //Part le convoyeur
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_HIGH);
    modeOperation_execute = modeOperation_ejecteUnBloc;
  }
}

void modeOperation_ejecteUnBloc (void)
{

  if (//Pas en train d'éjecter
    interfaceUsine_LitUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT) == INTERFACEUSINE_OUTPUT_LOW
    && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_EJECTEUR_IN) == INTERFACEUSINE_SENSOR_HIGH
    && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_EJECTEUR_OUT) == INTERFACEUSINE_SENSOR_LOW
  )
  {
    //Étire l'ejecteur
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_IN, INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT, INTERFACEUSINE_OUTPUT_HIGH);
  }

  if (//Éjection terminée
    interfaceUsine_LitUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT) == INTERFACEUSINE_OUTPUT_HIGH
    && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_EJECTEUR_IN) == INTERFACEUSINE_SENSOR_LOW
    && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_EJECTEUR_OUT) == INTERFACEUSINE_SENSOR_HIGH
  )
  {
    //Rétracte l'éjecteur
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_IN, INTERFACEUSINE_OUTPUT_HIGH);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT, INTERFACEUSINE_OUTPUT_LOW);

    //Change d'état
    modeOperation_execute = modeOperation_attendBlocChute;
  }
}

void modeOperation_attendBlocChute(void)
{
  static unsigned int compteurTempsAttendChute = 0;
  static unsigned int compteurDelaiVentouseBas = 0;
  compteurTempsAttendChute++;
  if (compteurTempsAttendChute >= DELAI_MAX_ATTEND_CHUTE)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_LOW);
    //messageErreur = "Erreur montee de l'elevateur";
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_CHUTE) == INTERFACEUSINE_SENSOR_HIGH)
  {
    compteurDelaiVentouseBas++;
    if (compteurDelaiVentouseBas >= DELAI_VENTOUSE_DESCEND)
    {
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);  
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_LOW);  
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_HIGH);
      modeOperation_execute = modeOperation_attendBlocAspire;
    }
  }
}

void modeOperation_attendBlocAspire(void)
{
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ETEINT);
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_PRESSION) == INTERFACEUSINE_SENSOR_LOW)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_HIGH);
  }

}

#pragma endregion EtatsModeOperation


void processusUsine_arret (void)
{
  updateModeEcran("Arret");
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_BOUTON_VERT) == INTERFACEUSINE_BOUTON_APPUYE) serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_operation;
}

void processusUsine_tests (void)
{
  updateModeEcran("Tests");
  #define ALLUME 1
  #define ETEINT 0
  #define CLIGNOTE 2
  //Gestion de la colonne lumineuse
  unsigned char tempVert;
  unsigned char tempRouge;
  unsigned char tempJaune;
  tempVert = ETEINT;
  tempRouge = ETEINT;
  tempJaune = ETEINT;

  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == INTERFACEUSINE_SENSOR_HIGH)tempJaune = ALLUME;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == INTERFACEUSINE_SENSOR_HIGH)tempRouge = ALLUME;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == INTERFACEUSINE_SENSOR_HIGH)tempVert = ALLUME;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_CHUTE) == INTERFACEUSINE_SENSOR_HIGH)
  {
    tempVert = ALLUME;
    tempRouge = ALLUME;
  }
  switch (tempVert)
  {
    case ALLUME:
    interfaceColonne_allume(INTERFACECOLONNE_VERT);
    break;
    case ETEINT:
    interfaceColonne_eteint(INTERFACECOLONNE_VERT);
    break;
    case CLIGNOTE:
    interfaceColonne_clignote(INTERFACECOLONNE_VERT);
    break;
  }

  switch (tempJaune)
  {
    case ALLUME:
    interfaceColonne_allume(INTERFACECOLONNE_JAUNE);
    break;
    case ETEINT:
    interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
    break;
    case CLIGNOTE:
    interfaceColonne_clignote(INTERFACECOLONNE_JAUNE);
    break;
  }

  switch (tempRouge)
  {
    case ALLUME:
    interfaceColonne_allume(INTERFACECOLONNE_ROUGE);
    break;
    case ETEINT:
    interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
    break;
    case CLIGNOTE:
    interfaceColonne_clignote(INTERFACECOLONNE_ROUGE);
    break;
  }
  modeTest_execute();
}



void processusUsine_initialise(void)
{
  modeOperation_execute = modeOperation_lanceInitialisation;
  serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_attente;
}

void modeErreur (void)
{
  updateModeEcran("Errerur");
  interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
  interfaceColonne_allume(INTERFACECOLONNE_ROUGE);
  interfaceColonne_eteint(INTERFACECOLONNE_VERT);
  static int compteurClignote;
  if (compteurClignote < 1000) interfaceT4_eteint();
  if (compteurClignote > 1000) interfaceT4_allume();
  if (compteurClignote > 2000) compteurClignote = 0;
  compteurClignote++;
}
