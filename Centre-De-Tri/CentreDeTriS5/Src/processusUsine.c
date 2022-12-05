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
#include "ServiceCommunication.h"
#include "piloteCAN1.h"
#include "processusUsine.h"
#include "piloteI2C.h"
#include "interfaceT1.h"
#include "interfaceT2.h"
#include "interfaceT4.h"
#include "interfaceUsine.h"
#include "interfaceColonne.h"
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
#define DELAI_MAX_PISTON 3000

#define BLOC_AUCUN 0
#define BLOC_ROUGE 1
#define BLOC_NOIR 2
#define BLOC_METAL 3
#define BLOC_INCONNU 4

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
void modeOperation_attendVentouseHaut(void);
void modeOperation_vaALaFosse(void);
void modeOperation_vaALAscenseur(void);
void modeDeTests_testeLesEntrees (void);
void modeDeTests_activeLeVerinDuMagasin (void);
void modeDeTests_desactiveLeVerinDuMagasin (void);
void modeDeTests_monteElevateur (void);
void modeDeTests_descendElevateur (void);
void modeDeTests_activeleConvoyeur (void);
void modeDeTests_desactiveLeConvoyeur (void);
void modeDeTests_activeEjecteur (void);
void modeDeTests_activeLaVentouse (void);
void modeDeTests_desactiveLaVentouse (void);
void modeDeTests_descendLaVentouse (void);
void modeDeTests_monteLaVentouse (void);
void modeDeTests_deplaceLaVentouse (void);
void modeDeTests_replaceLaventouse (void);
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
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_BOUTON_VERT) == INTERFACEUSINE_BOUTON_APPUYE) 
  {
    interfaceT1_allume();
    interfaceColonne_eteint(INTERFACECOLONNE_VERT);
    modeOperation_execute = modeOperation_lanceInitialisation;
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_operation;
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.waiting;                                      // ADDED FOR CC TESTS
    #endif
  }
  
  //if (HAL_GPIO_ReadPin(PILOTEIOB1_PORT, PILOTEIOB1_ENTREE))serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_tests;
  

    if (interfaceB1.etatDuBouton == INTERFACEB1_APPUYE) 
    {
      interfaceT2_allume();
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_tests;
      #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
      ModuleData.State = States.testing;                                      // ADDED FOR CC TESTS
      #endif
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
    }
  
}

void processusUsine_operation (void)
{
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER, INTERFACEUSINE_OUTPUT_HIGH);
  //  La série de "if" suivante sert à exécuter un mode différent 
  //  en fonction de ce qui est demandé par le poste de commande.
  //  Le mode de fonctionnement normal (mode opération) qui est 
  //  demandé dans le document de projet correspond au 1er "if".

  //Si en mode debug (pour ignorer la comm et toujours trier) main.h, 1re depandance logicielle.
  #ifdef MODE_BYPASS_POSTE_DE_COMMANDE
  modeOperation_execute();
  #endif

  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE

  if(ModuleData.Mode == Modes.operation)
  {
    updateEtatEcran("Operation");
    modeOperation_execute();
  }

  if(ModuleData.Mode == Modes.emergencyStop)
  {
    updateEtatEcran("EMERGENCY");
    interfaceUsine_Reset ();
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.emergencyStop;
    #endif
  }

  if(ModuleData.Mode == Modes.pause)
  {
    processusUsine_attente();
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.paused;
    #endif
  }

  if(ModuleData.Mode == Modes.reinitialisation)
  {
    updateEtatEcran("Initialising");
    interfaceUsine_Reset ();
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.processing;
    #endif
  }

  if(ModuleData.Mode == Modes.testing)
  {
    updateEtatEcran("Technician");
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.waiting;
    #endif
  }

  if(ModuleData.Mode == Modes.maintenance)
  {
    updateEtatEcran("Maintenance");
    interfaceUsine_Reset ();
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.safe;
    #endif
  }
  if (ucTypeDeBloc == BLOC_AUCUN)  ModuleData_SetDiscColor(Values.disc_NoColor);
  if (ucTypeDeBloc == BLOC_NOIR)  ModuleData_SetDiscColor(Values.disc_Black);
  if (ucTypeDeBloc == BLOC_ROUGE)  ModuleData_SetDiscColor(Values.disc_Red);
  if (ucTypeDeBloc == BLOC_METAL)  ModuleData_SetDiscColor(Values.disc_Silver);
  #endif
}
#pragma region EtatsModeOperation

void modeOperation_lanceInitialisation (void)
{
  updateEtatEcran("Lance Init");
  ucTypeDeBloc = BLOC_AUCUN;
  //interfaceUsine_RequetePont (INTERFACEUSINE_PONT_POSITIONH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER, INTERFACEUSINE_OUTPUT_HIGH);
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
  updateEtatEcran("Att Fin init");
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
  updateEtatEcran("Pousse 1 bloc");
  modeOperation_execute = modeOperation_pousseUnBloc;
}

void modeOperation_pousseUnBloc (void)
{  
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
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
    updateEtatEcran("Detection bloc");
    modeOperation_execute = modeOperation_detecteLeBloc;
  }
}

void modeOperation_detecteLeBloc (void)
{  
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
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
      updateMessageEcran("Succes:Bloc ROUGE!");
      interfaceColonne_allume(INTERFACECOLONNE_JAUNE);
      interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
      modeOperation_execute = modeOperation_monteElevateur;
    }
    
    else if (
        interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_NOIR
          && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_NOIR
            && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_NOIR
              )
    {
      ucTypeDeBloc = BLOC_NOIR;
      updateMessageEcran("Succes:Bloc NOIR!");
      interfaceColonne_clignote(INTERFACECOLONNE_JAUNE);
      interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
      modeOperation_execute = modeOperation_monteElevateur;
    }
    
    else if (
        interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_METAL
          && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_METAL
            && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_METAL
              )
    {
      ucTypeDeBloc = BLOC_METAL;
      updateMessageEcran("Succes:Bloc METAL!");
      interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
      interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
      interfaceColonne_allume(INTERFACECOLONNE_VERT);
      modeOperation_execute = modeOperation_monteElevateur;
    }
    
    else if (
        interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_AUCUN
          && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_AUCUN
            && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_AUCUN
              )
    {
      ucTypeDeBloc = BLOC_AUCUN;
      updateMessageEcran("Erreur:Magasin vide!");
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
    }
    else
    {
      ucTypeDeBloc = BLOC_INCONNU;
      updateMessageEcran("Erreur:Bloc inconnu!");
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
    }
  }
  
}

void modeOperation_monteElevateur (void)
{
  updateEtatEcran("Elevateur Monte");
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
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
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
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
    updateEtatEcran("EjectionBloc");
    modeOperation_execute = modeOperation_ejecteUnBloc;
  }
}

void modeOperation_ejecteUnBloc (void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
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
    updateEtatEcran("AttendBlocChute");
    modeOperation_execute = modeOperation_attendBlocChute;
  }
}

void modeOperation_attendBlocChute(void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
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
      updateEtatEcran("AttendAspire");
      modeOperation_execute = modeOperation_attendBlocAspire;
    }
  }
}

void modeOperation_attendBlocAspire(void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ETEINT);
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_PRESSION) == INTERFACEUSINE_SENSOR_LOW)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_HIGH);
    updateEtatEcran("VentouseMonte");
    modeOperation_execute = modeOperation_attendVentouseHaut;
  }

}

void modeOperation_attendVentouseHaut(void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
  static unsigned int compteurTempsMouvement = 0;
  compteurTempsMouvement++;
  if (compteurTempsMouvement >= DELAI_MAX_PISTON)
  {
    updateMessageEcran("Erreur: Delai montee ventouse expirer");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  modeErreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_VENTOUSE_HAUT) == INTERFACEUSINE_SENSOR_HIGH)
  {
    switch (ucTypeDeBloc)
    {
      case BLOC_NOIR:
      updateEtatEcran("PontVersFosse");
      modeOperation_execute = modeOperation_vaALaFosse;
      break;
      case BLOC_ROUGE:
      case BLOC_METAL:
      updateEtatEcran("PontVersAsc");
      modeOperation_execute = modeOperation_vaALAscenseur;
      break;
    }
  }

}

void modeOperation_vaALaFosse(void)
{
  //interfaceUsine_RequetePont (INTERFACEUSINE_PONT_POSITION1);
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.waitingToSort; // ADDED TO TEST STUFF TEMPORARLY
  #endif
}

void modeOperation_vaALAscenseur(void)
{
  //interfaceUsine_RequetePont (INTERFACEUSINE_PONT_POSITION2);
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.finishedSortingAndHasLoaded; // ADDED TO TEST STUFF TEMPORARLY
  #endif
}

#pragma endregion EtatsModeOperation


void processusUsine_arret (void)
{
  updateModeEcran("Arret");
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_BOUTON_VERT) == INTERFACEUSINE_BOUTON_APPUYE) serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_operation;
}

void processusUsine_tests (void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.testing; // ADDED TO TEST STUFF TEMPORARLY
  #endif
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

#pragma region EtatsDuModeDeTests
void modeDeTests_testeLesEntrees (void)
{

}
void modeDeTests_activeLeVerinDuMagasin (void)
{

}
void modeDeTests_desactiveLeVerinDuMagasin (void)
{

}
void modeDeTests_monteElevateur (void)
{

}
void modeDeTests_descendElevateur (void)
{

}
void modeDeTests_activeleConvoyeur (void)
{

}
void modeDeTests_desactiveLeConvoyeur (void)
{

}
void modeDeTests_activeEjecteur (void)
{

}
void modeDeTests_activeLaVentouse (void)
{
  
}
void modeDeTests_desactiveLaVentouse (void)
{

}
void modeDeTests_descendLaVentouse (void)
{

}
void modeDeTests_monteLaVentouse (void)
{

}
void modeDeTests_deplaceLaVentouse (void)
{

}
void modeDeTests_replaceLaventouse (void)
{

}

#pragma endregion EtatsDuModeDeTests



void modeErreur (void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.error;
  #endif
  updateModeEcran("Erreur");
  interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
  interfaceColonne_allume(INTERFACECOLONNE_ROUGE);
  interfaceColonne_eteint(INTERFACECOLONNE_VERT);
  static int compteurClignote;
  if (compteurClignote < 1000) interfaceT4_eteint();
  if (compteurClignote > 1000) interfaceT4_allume();
  if (compteurClignote > 2000) compteurClignote = 0;
  compteurClignote++;
}

void processusUsine_initialise(void)
{
  modeOperation_execute = modeOperation_lanceInitialisation;
  serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_attente;
}