
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
#include "interfacePont.h"
//Definitions privees
//Les unités des valeurs de délai suivantes corerespondent à la base de temps : 1/2ms
#define DELAI_MAX_INITIALISATION 50000
#define DELAI_MAX_EJECTION 1000
#define DELAI_MAX_DETECTION 5000
#define DELAI_AVANT_DETECTION 1000
#define DELAI_MAX_ELEVATEUR_HAUT 10000
#define DELAI_MAX_ATTEND_CHUTE 10000
#define DELAI_VENTOUSE_DESCEND 1000
#define DELAI_MAX_PISTON 3000
#define DELAI2SEC 4000

#define TEST_VITESSELEDCLIGNOTE 2000

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

#define VALEUR_ADC_BLOC_PRESENT 0

#define DELAITEST_RESET 1
#define DELAITEST_UTILISE 0
#define DELAITEST_TERMINE 1
#define DELAITEST_EN_COURS 0
#define VALEUR_DELAI_MODE_DE_TEST 4000
#define DELAI_MAX_TESTS 3000 //1.5 sec (ne doit pas dépasser 2 sec)
#define DELAI_MAX_TESTS_PONT 30000 //15 sec

//Declarations de fonctions privees:
void modeOperation_lanceInitialisation (void);
void modeOperation_attendFinInitialisation (void);
void modeOperation_pousseUnBloc (void);
void modeOperation_detecteLeBloc (void);
void modeOperation_monteElevateur (void);
void modeOperation_attendElevateurEnHaut (void);
void modeOperation_ejecteUnBloc (void);
void modeOperation_attendBlocChute (void);
void modeOperation_attendPontPos0(void);
void modeOperation_attendBlocAspire(void);
void modeOperation_attendVentouseHaut(void);
void modeOperation_vaALaFosse(void);
void modeOperation_vaALAscenseur(void);
void modeOperation_attendFinJetteBloc (void);
void modeDeTests_testeLaColonneLumineuse (void);
void modeDeTests_testeLesEntrees (void);
void modeDeTests_activeLeVerinDuMagasin (void);
void modeDeTests_desactiveLeVerinDuMagasin (void);
void modeDeTests_monteElevateur (void);
void modeDeTests_descendElevateur (void);
void modeDeTests_activeleConvoyeur (void);
void modeDeTests_desactiveLeConvoyeur (void);
void modeDeTests_activeEjecteur (void);
void modeDeTests_desactiveEjecteur (void);
void modeDeTests_activeLaVentouse (void);
void modeDeTests_desactiveLaVentouse (void);
void modeDeTests_descendLaVentouse (void);
void modeDeTests_monteLaVentouse (void);
void modeDeTests_attFinInitPont (void);
void modeDeTests_deplaceLaVentouse (void);
void modeDeTests_replaceLaventouse (void);
bool delaiModeDeTest (bool reset);
void modeTest_clignote(void);
void updateDiscColor(void);
void processusUsine_erreur (void);
//Definitions de variables privees:
void (*modeOperation_execute)(void);
void (*modeTest_execute)(void);

unsigned char ucTypeDeBloc;



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
  updateMessageEcran("Btn Vert: Operation Btn Bleu: Test");
  interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
  interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
  interfaceColonne_clignote(INTERFACECOLONNE_VERT);

  //Check le bouton vert || Si le mode de Technicien est activé par le poste de commande, on bypass l'attente.
  if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE || ModuleData.Mode == Modes.testing)
  {
    interfaceUsine_BV.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE || ModuleData.Mode == Modes.testing)
    {
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
      modeOperation_execute = modeOperation_lanceInitialisation;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ALLUME);
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_operation;
      updateMessageEcran("");
      #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
      ModuleData.State = States.waiting;                                      // ADDED FOR CC TESTS
      #endif
    }
  }  
  
  //Check le bouton rouge
  if (interfaceUsine_BR.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BR.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BR.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_arret;
      #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
      ModuleData.State = States.waiting;                                      // ADDED FOR CC TESTS
      #endif
    }
  } 
  
  //Check le bouton bleu men
  if (interfaceB1.information == INFORMATION_DISPONIBLE)
  {
    interfaceB1.information = INFORMATION_TRAITEE;
    if (interfaceB1.etatDuBouton == INTERFACEB1_APPUYE) 
    {
      modeTest_execute = modeDeTests_testeLaColonneLumineuse;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ALLUME);
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_tests;
      #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
      ModuleData.State = States.testing;                                      // ADDED FOR CC TESTS
      #endif
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
    }
  }
}

void processusUsine_operation (void)
{
  updateModeEcran("Operation");
  //  La série de "if" suivante sert à exécuter un mode différent 
  //  en fonction de ce qui est demandé par le poste de commande.
  //  Le mode de fonctionnement normal (mode opération) qui est 
  //  demandé dans le document de projet correspond au 1er "if".

  //Si en mode debug (pour ignorer la comm et toujours trier) main.h, 1re depandance logicielle.
  #ifdef MODE_BYPASS_POSTE_DE_COMMANDE
  modeOperation_execute();
  #endif

  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  /*
    if(ModuleData.State == States.error)
  {
    updateEtatEcran("EMERGENCY");
    updateMessageEcran("Erreur sur le can");
    interfaceUsine_Reset ();
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_erreur;
  }
  */
  if(ModuleData.Mode == Modes.operation || (ModuleData.CommandsReceived.start_Sorting == RECEIVED && ModuleData.Mode == Modes.testing))
  {
    updateMessageEcran("Tri en cours!");
    updateEtatEcran("Operation");
    if(ModuleData.StatesReceived.atSortingFactory == RECEIVED || (ModuleData.CommandsReceived.start_Sorting == RECEIVED && ModuleData.Mode == Modes.testing))
    {
      modeOperation_execute();
    }
    else
    {
      updateMessageEcran("En attente du vehicule");
      modeOperation_execute = modeOperation_lanceInitialisation;
      ModuleData.State = States.waitingToSort;
      ModuleData_SetAll_ValuesReceived(PARSED);
      ModuleData_SetAll_StatesReceived(PARSED);      
    }

  }

  if(ModuleData.Mode == Modes.emergencyStop)
  {
    updateEtatEcran("EMERGENCY");
    updateMessageEcran("En arret d'urgence! TT les I/O sont a 0");
    interfaceUsine_Reset ();
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.emergencyStop;
    #endif
  }

  if(ModuleData.Mode == Modes.pause)
  {
    updateEtatEcran("Pause");
    updateMessageEcran(" ");
    //processusUsine_attente();
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.paused;
    #endif
  }

  if(ModuleData.Mode == Modes.reinitialisation)
  {
    updateEtatEcran("Initialising");
    updateMessageEcran("En initialisation (selon poste commande)");
    interfaceUsine_Reset ();
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.processing;
    #endif
  }

  if(ModuleData.Mode == Modes.testing)
  {
    updateEtatEcran("Technician");
    updateDiscColor();
    //Envoie continuellement la valeur du block
    //modeOperation_detecteLeBloc();

    if(ModuleData.CommandsReceived.move_left == RECEIVED)
    {
      ModuleData.CommandsReceived.move_left = PARSED;
      interfaceUsine_RequetePont(INTERFACEUSINE_PONT_POSITION2);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_POUSSOIR, INTERFACEUSINE_OUTPUT_HIGH);
    }

    if(ModuleData.CommandsReceived.move_right == RECEIVED)
    {
      ModuleData.CommandsReceived.move_right = PARSED;
      interfaceUsine_RequetePont(INTERFACEUSINE_PONT_POSITION0);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_POUSSOIR, INTERFACEUSINE_OUTPUT_LOW);
    }
    // Move Upwards
    if(ModuleData.CommandsReceived.move_up == RECEIVED)
    {
      ModuleData.CommandsReceived.move_up = PARSED;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_MONTE, INTERFACEUSINE_OUTPUT_HIGH);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_DESCEND, INTERFACEUSINE_OUTPUT_LOW);

      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_HIGH);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_LOW);
    }
    // Move Downwards
    if(ModuleData.CommandsReceived.move_down == RECEIVED)
    {
      ModuleData.CommandsReceived.move_down = PARSED;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_MONTE, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);

      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);
    }
    //Move forwards (elements moves towards the bridge)
    if(ModuleData.CommandsReceived.move_forward == RECEIVED)
    {
      ModuleData.CommandsReceived.move_forward = PARSED;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_IN, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT, INTERFACEUSINE_OUTPUT_HIGH);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_HIGH);
    }
    //Move forwards (elements moves away from the bridge)
    if(ModuleData.CommandsReceived.move_backward == RECEIVED)
    {
      ModuleData.CommandsReceived.move_backward = PARSED;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_IN, INTERFACEUSINE_OUTPUT_HIGH);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_LOW);
    }

    if(ModuleData.CommandsReceived.light_A_ON == RECEIVED)
    {
      ModuleData.CommandsReceived.light_A_ON = PARSED;
      interfaceColonne_allume(INTERFACECOLONNE_VERT);
    }

    if(ModuleData.CommandsReceived.light_A_OFF == RECEIVED)
    {
      ModuleData.CommandsReceived.light_A_OFF = PARSED;
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
    }

    if(ModuleData.CommandsReceived.light_B_ON == RECEIVED)
    {
      ModuleData.CommandsReceived.light_B_ON = PARSED;
      interfaceColonne_allume(INTERFACECOLONNE_JAUNE);
    }

    if(ModuleData.CommandsReceived.light_B_OFF == RECEIVED)
    {
      ModuleData.CommandsReceived.light_B_OFF = PARSED;
      interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
    }

    if(ModuleData.CommandsReceived.light_C_ON == RECEIVED)
    {
      ModuleData.CommandsReceived.light_C_ON = PARSED;
      interfaceColonne_allume(INTERFACECOLONNE_ROUGE);
    }

    if(ModuleData.CommandsReceived.light_C_OFF == RECEIVED)
    {
      ModuleData.CommandsReceived.light_C_OFF = PARSED;
      interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
    }
    
    if(ModuleData.CommandsReceived.light_D_ON == RECEIVED)
    {
      ModuleData.CommandsReceived.light_D_ON = PARSED;
      HAL_GPIO_WritePin(HORN_GPIO_Port, HORN_Pin, (GPIO_PinState)1); 
    }

    if(ModuleData.CommandsReceived.light_D_OFF == RECEIVED)
    {
      ModuleData.CommandsReceived.light_D_OFF = PARSED;
      HAL_GPIO_WritePin(HORN_GPIO_Port, HORN_Pin, (GPIO_PinState)0); 
    } 

    if(ModuleData.CommandsReceived.suction_ON == RECEIVED)
    {
      ModuleData.CommandsReceived.suction_ON = PARSED;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_HIGH);
    }

    if(ModuleData.CommandsReceived.suction_OFF == RECEIVED)
    {
      ModuleData.CommandsReceived.suction_OFF = PARSED;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_LOW);
    }  
    
    #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
    ModuleData.State = States.waiting;
    #endif
  }
  else
  {
    // Reinitialisation de la demande de debut de tri au cas ou
    ModuleData.CommandsReceived.start_Sorting = PARSED;
  }
  if(ModuleData.Mode == Modes.maintenance)
  {
    updateEtatEcran("Maintenance");
    updateMessageEcran("En maintenance!     TT les I/O sont a 0");
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

  //Check le bouton rouge
  if (interfaceUsine_BR.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BR.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BR.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ETEINT);
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_arret;
      #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
      ModuleData.State = States.waiting;                                      // ADDED FOR CC TESTS
      #endif
    }
  } 
}
#pragma region EtatsModeOperation

void modeOperation_lanceInitialisation (void)
{
  updateEtatEcran("Lance Init");
  ucTypeDeBloc = BLOC_AUCUN;
  interfaceUsine_RequetePont (INTERFACEUSINE_PONT_POSITIONH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER, INTERFACEUSINE_OUTPUT_HIGH);
  
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
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
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
  if (interfaceUsine_EtatPont() != INTERFACEUSINE_PONT_ETAT_FINI || interfaceUsine_PositionPont() != INTERFACEUSINE_PONT_POSITIONH)return;
  updateEtatEcran("Pousse 1 bloc");
  compteurTempsInitialisation = 0;
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
    updateMessageEcran("Oups! Timeout d'ejection atteint");
    compteurTempsEjectionBloc = 0;
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
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
    compteurTempsEjectionBloc = 0;
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
    updateMessageEcran("Oops! Timeout de detection atteint");
    compteurTempsDetectionBloc = 0;
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
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
        compteurTempsDetectionBloc = 0;
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
        compteurTempsDetectionBloc = 0;
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
      compteurTempsDetectionBloc = 0;
      modeOperation_execute = modeOperation_monteElevateur;
    }

    else if (
        interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_AUCUN
          && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_AUCUN
            && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_AUCUN
              )
    {
      ucTypeDeBloc = BLOC_AUCUN;
      updateMessageEcran("Erreur: Magasin vide!");
      ModuleData.State = States.empty;
      compteurTempsDetectionBloc = 0;
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
    }
    else
    {
      ucTypeDeBloc = BLOC_INCONNU;
      if(ModuleData.Mode != Modes.testing)
      {
        updateMessageEcran("Erreur: Bloc inconnu!");
        compteurTempsDetectionBloc = 0;
        serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
      }
      else
      {
        ModuleData_SetDiscColor(Values.disc_NoColor);
      }
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
  updateMessageEcran("Erreur: elevateur pas en bas");
  serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
}
void modeOperation_attendElevateurEnHaut (void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
  static unsigned int compteurDelaiTpsADC = 0;
  static unsigned int compteurTempsElevateurEnHaut = 0;
  compteurTempsElevateurEnHaut++;
  if (compteurTempsElevateurEnHaut >= DELAI_MAX_ELEVATEUR_HAUT)
  {
    updateMessageEcran("Erreur: montee de l'elevateur impossible");
    compteurDelaiTpsADC = 0;
    compteurTempsElevateurEnHaut = 0;
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }

  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_ELEVATEUR_HAUT) == INTERFACEUSINE_SENSOR_HIGH )
  {
    updateMessageEcran("Arrived up");
    compteurDelaiTpsADC++;
    //Part le convoyeur
    if (compteurDelaiTpsADC >= 100)
    {
      updateMessageEcran("ADC_DELAY");
      if (interfaceUsine_LitADC() >= 0x0D)
      {
        updateMessageEcran("ERROR ADC");
        updateMessageEcran("Erreur: Capteur analog voit pas de bloc!");
        compteurDelaiTpsADC = 0;
        compteurTempsElevateurEnHaut = 0;
        serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_erreur;
      }
      else
      {
        updateMessageEcran("NEXT STEP");
        interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_HIGH);
        updateEtatEcran("EjectionBloc");
        compteurDelaiTpsADC = 0;
        compteurTempsElevateurEnHaut = 0;
        modeOperation_execute = modeOperation_ejecteUnBloc;
      }
      compteurDelaiTpsADC = 0;
      compteurTempsElevateurEnHaut = 0;
    }
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
    updateMessageEcran("Oups! Bloc perdu entre ejecteur et chute");
    compteurTempsAttendChute = 0;
    compteurDelaiVentouseBas = 0;
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_CHUTE) == INTERFACEUSINE_SENSOR_HIGH)
  {
    compteurDelaiVentouseBas++;
    if (compteurDelaiVentouseBas >= DELAI_VENTOUSE_DESCEND)
    {
      interfaceUsine_RequetePont(INTERFACEUSINE_PONT_POSITION0);
      compteurTempsAttendChute = 0;
      compteurDelaiVentouseBas = 0;
      modeOperation_execute = modeOperation_attendPontPos0;
    }
  }
}
void modeOperation_attendPontPos0(void)
{
  if (interfaceUsine_EtatPont() == INTERFACEUSINE_PONT_ETAT_FINI && interfaceUsine_PositionPont() == INTERFACEUSINE_PONT_POSITION0)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);  
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_LOW);  
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_HIGH);
      updateEtatEcran("AttendAspire");
      modeOperation_execute = modeOperation_attendBlocAspire;
  }  
}
void modeOperation_attendBlocAspire(void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.processing; // ADDED TO TEST STUFF
  #endif
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
    updateMessageEcran("Erreur: Timeout montee ventouse atteint");
    compteurTempsMouvement = 0;
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_VENTOUSE_HAUT) == INTERFACEUSINE_SENSOR_HIGH)
  {
    switch (ucTypeDeBloc)
    {
      case BLOC_NOIR:
      if(interfaceUsine_RequetePont (INTERFACEUSINE_PONT_POSITION1))
      {
        updateEtatEcran("PontVersFosse");
        compteurTempsMouvement = 0;
        modeOperation_execute = modeOperation_vaALaFosse;
      }
      
      break;
      case BLOC_ROUGE:
      case BLOC_METAL:
      if(interfaceUsine_RequetePont (INTERFACEUSINE_PONT_POSITION2))
      {
        compteurTempsMouvement = 0;
        modeOperation_execute = modeOperation_vaALAscenseur;
        updateEtatEcran("PontVersAsc");
      }      
      break;
    }
  }

}
void modeOperation_vaALaFosse(void)
{
  
  if (interfaceUsine_EtatPont() == INTERFACEUSINE_PONT_ETAT_FINI && interfaceUsine_PositionPont() == INTERFACEUSINE_PONT_POSITION1)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);
    modeOperation_execute = modeOperation_attendFinJetteBloc;
    return;
  }

  ModuleData.State = States.waitingToSort;
  //interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_LOW);
  
}
void modeOperation_vaALAscenseur(void)
{
  
  if (interfaceUsine_EtatPont() == INTERFACEUSINE_PONT_ETAT_FINI && interfaceUsine_PositionPont() == INTERFACEUSINE_PONT_POSITION2)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_LOW);
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);
    modeOperation_execute = modeOperation_attendFinJetteBloc;
    return;
  }
  

  //interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_LOW);
}
void modeOperation_attendFinJetteBloc (void)
{
  static bool flagSequenceFinie;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_VENTOUSE_BAS) == INTERFACEUSINE_SENSOR_HIGH)
  {
    if (flagSequenceFinie == 0)
    {
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_HIGH);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);
      if (ucTypeDeBloc == BLOC_ROUGE || ucTypeDeBloc == BLOC_METAL)
        ModuleData.State = States.finishedSortingAndHasLoaded; // ADDED TO TEST STUFF TEMPORARLY
      if (ucTypeDeBloc == BLOC_NOIR)
        ModuleData.State = States.waitingToSort; // ADDED TO TEST STUFF TEMPORARLY
      ModuleData_SetDiscColor(Values.disc_NoColor);
      updateMessageEcran("Tri fini!");
      // Au cas ou c'est la commande de demande de début de tri qui fait trier l'usine
      ModuleData.CommandsReceived.start_Sorting = PARSED;
      flagSequenceFinie = 1;
    }
    else updateMessageEcran("En delai avant restart");

   
      if (ModuleData.StatesReceived.atWeightStation == RECEIVED)
      {
        ModuleData.StatesReceived.atWeightStation = PARSED;
        ModuleData.State = States.waitingToSort;
        ModuleData_SetAll_StatesReceived(PARSED);
        ModuleData_SetAll_ValuesReceived(PARSED);
        modeOperation_execute = modeOperation_lanceInitialisation;
      }
      if (ucTypeDeBloc == BLOC_NOIR)modeOperation_execute = modeOperation_lanceInitialisation;


  }
  else 
  {
    flagSequenceFinie = 0;
  }
  
  
}

#pragma endregion EtatsModeOperation

/// @brief 
/// @param  
void processusUsine_arret (void)
{
  updateModeEcran("Arret");
  updateMessageEcran("Mode arret. Pesez vert pour mode attente");
  interfaceUsine_Reset();
  //Check le bouton vert
  if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BV.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      interfaceColonne_eteint(INTERFACECOLONNE_VERT);
      serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_attente;
      #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
      ModuleData.State = States.waiting;                                      // ADDED FOR CC TESTS
      #endif
    }
  } 
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
  modeTest_clignote();
}

#pragma region EtatsDuModeDeTests

void modeDeTests_testeLaColonneLumineuse (void)
{
  updateEtatEcran("test Colonne");
  updateMessageEcran("Fin dans 2 sec");
  static unsigned int compteurDelai = 0;
  compteurDelai++;
  if(compteurDelai>=4000)
  {
    modeTest_execute = modeDeTests_testeLesEntrees;
    interfaceColonne_eteint(INTERFACECOLONNE_ROUGE);
    interfaceColonne_eteint(INTERFACECOLONNE_VERT);
    interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
    return;
  }
  interfaceColonne_allume(INTERFACECOLONNE_ROUGE);
  interfaceColonne_allume(INTERFACECOLONNE_VERT);
  interfaceColonne_allume(INTERFACECOLONNE_JAUNE);
}
void modeDeTests_testeLesEntrees (void)
{
  updateEtatEcran("test Entrees");
  updateMessageEcran("Test des entrees.   PesezBtnVPrContinuer");
  if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BV.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      modeTest_execute = modeDeTests_activeLeVerinDuMagasin;
      delaiModeDeTest(DELAITEST_RESET);
    }
  }
}
void modeDeTests_activeLeVerinDuMagasin (void)
{
  //Partie de détection d'erreurs
  bool flagMouvementTermine = 0;
  static unsigned int compteurTempsEjectionBloc = 0;
  if(flagMouvementTermine == 0)compteurTempsEjectionBloc++;
  if (compteurTempsEjectionBloc >= DELAI_MAX_TESTS)
  {
    updateMessageEcran("Oups! Timeout poussoir out atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_POUSSOIR_OUT) == INTERFACEUSINE_SENSOR_HIGH) flagMouvementTermine = 1;

  //Partie du fonctionnement
  updateEtatEcran("Act. Verin Mag.");
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_POUSSOIR, INTERFACEUSINE_OUTPUT_HIGH);
  if (delaiModeDeTest(DELAITEST_UTILISE))
  {
    modeTest_execute = modeDeTests_desactiveLeVerinDuMagasin;
  }
      

}
void modeDeTests_desactiveLeVerinDuMagasin (void)
{
  //Partie de détection d'erreurs
  bool flagMouvementTermine = 0;
  static unsigned int compteurTempsTimeout = 0;
  if(flagMouvementTermine == 0)compteurTempsTimeout++;
  else compteurTempsTimeout = 0;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS)
  {
    updateMessageEcran("Oups! Timeout poussoir in atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_POUSSOIR_IN) == INTERFACEUSINE_SENSOR_HIGH) flagMouvementTermine = 1;

 //Partie fonctionnement
  updateEtatEcran("Des. Verin Mag.");
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_POUSSOIR, INTERFACEUSINE_OUTPUT_LOW);
  
  //AttendBtnPourProchainEtat  
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_POUSSOIR_IN) == INTERFACEUSINE_SENSOR_HIGH)
  {
    //Détection du bouton
    updateMessageEcran("Pesez bouton vert   pour test elevateur");
    if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE)
    {
      interfaceUsine_BV.information = INFORMATION_TRAITEE;
      if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
      {
        modeTest_execute = modeDeTests_monteElevateur;
        updateMessageEcran("");
        delaiModeDeTest(DELAITEST_RESET);
      }
    }
  }
}
void modeDeTests_monteElevateur (void)
{
    //Partie de détection d'erreurs
  bool flagMouvementTermine = 0;
  static unsigned int compteurTempsTimeout = 0;
  if(flagMouvementTermine == 0)compteurTempsTimeout++;
  else compteurTempsTimeout = 0;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS)
  {
    updateMessageEcran("Oups! Timeout elevateur monte atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_ELEVATEUR_HAUT) == INTERFACEUSINE_SENSOR_HIGH) flagMouvementTermine = 1;

  //Partie fonctionnement
  updateEtatEcran("Monte Elev.");

  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_MONTE, INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_DESCEND, INTERFACEUSINE_OUTPUT_LOW);

  //Attend delai pour prochain etat
  if (delaiModeDeTest(DELAITEST_UTILISE))
  {
    modeTest_execute = modeDeTests_descendElevateur;
    delaiModeDeTest(DELAITEST_RESET);
  }
}
void modeDeTests_descendElevateur (void)
{
    //Partie de détection d'erreurs
  bool flagMouvementTermine = 0;
  static unsigned int compteurTempsTimeout = 0;
  if(flagMouvementTermine == 0)compteurTempsTimeout++;
  else compteurTempsTimeout = 0;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS)
  {
    updateMessageEcran("Oups! Timeout elevateur bas atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_ELEVATEUR_BAS) == INTERFACEUSINE_SENSOR_HIGH) flagMouvementTermine = 1;


  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_MONTE, INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_ELEVATEUR_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);
  updateEtatEcran("Descend Elev.");

  //AttendBtnPourProchainEtat
  updateMessageEcran("Pesez bouton vert   pour test convoyeur");
  if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BV.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      modeTest_execute = modeDeTests_activeleConvoyeur;
      updateMessageEcran("");
      delaiModeDeTest(DELAITEST_RESET);
    }
  }
}
void modeDeTests_activeleConvoyeur (void)
{
  updateEtatEcran("Act. Convoyeur.");
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_HIGH);
    //Attend delai pour prochain etat
  if (delaiModeDeTest(DELAITEST_UTILISE))
  {
    modeTest_execute = modeDeTests_desactiveLeConvoyeur;
    delaiModeDeTest(DELAITEST_RESET);
  }
}
void modeDeTests_desactiveLeConvoyeur (void)
{
  updateEtatEcran("Des. Convoyeur.");
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_CONVOYEUR, INTERFACEUSINE_OUTPUT_LOW);

    //AttendBtnPourProchainEtat
  updateMessageEcran("Pesez bouton vert   pour test ejecteur");
  if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BV.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      modeTest_execute = modeDeTests_activeEjecteur;
      updateMessageEcran("");
      delaiModeDeTest(DELAITEST_RESET);
    }
  }
}
void modeDeTests_activeEjecteur (void)
{
    //Partie de détection d'erreurs
  bool flagMouvementTermine = 0;
  static unsigned int compteurTempsTimeout = 0;
  if(flagMouvementTermine == 0)compteurTempsTimeout++;
  else compteurTempsTimeout = 0;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS)
  {
    updateMessageEcran("Oups! Timeout ejecteur out atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_EJECTEUR_OUT) == INTERFACEUSINE_SENSOR_HIGH) flagMouvementTermine = 1;

  //Partie fonctionnement
  updateEtatEcran("Act. Ejecteur.");
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT, INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_IN, INTERFACEUSINE_OUTPUT_LOW);
  //Attend delai pour prochain etat
  if (delaiModeDeTest(DELAITEST_UTILISE))
  {
    modeTest_execute = modeDeTests_desactiveEjecteur;
    delaiModeDeTest(DELAITEST_RESET);
  }
}
void modeDeTests_desactiveEjecteur (void)
{
    //Partie de détection d'erreurs
  bool flagMouvementTermine = 0;
  static unsigned int compteurTempsTimeout = 0;
  if(flagMouvementTermine == 0)compteurTempsTimeout++;
  else compteurTempsTimeout = 0;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS)
  {
    updateMessageEcran("Oups! Timeout ejecteur out atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_EJECTEUR_OUT) == INTERFACEUSINE_SENSOR_HIGH) flagMouvementTermine = 1;

  //Partie fonctionnement
  updateEtatEcran("Des. Ejecteur.");
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_OUT, INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_EJECTEUR_IN, INTERFACEUSINE_OUTPUT_HIGH);
    //AttendBtnPourProchainEtat
  updateMessageEcran("Pesez bouton vert   pour test Air");
  if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BV.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      modeTest_execute = modeDeTests_activeLaVentouse;
      updateMessageEcran("");
      delaiModeDeTest(DELAITEST_RESET);
    }
  }
}
void modeDeTests_activeLaVentouse (void)
{
  updateEtatEcran("Active Air");
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_HIGH);

  //Attend delai pour prochain etat
  if (delaiModeDeTest(DELAITEST_UTILISE))
  {
    modeTest_execute = modeDeTests_desactiveLaVentouse;
    delaiModeDeTest(DELAITEST_RESET);
  }
}
void modeDeTests_desactiveLaVentouse (void)
{
  updateEtatEcran("Desact. Air");
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_AIR_TRIG, INTERFACEUSINE_OUTPUT_LOW);

  //AttendBtnPourProchainEtat
  updateMessageEcran("Pesez bouton vert   pour test Ventouse");
  if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BV.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      modeTest_execute = modeDeTests_descendLaVentouse;
      updateMessageEcran("");
      delaiModeDeTest(DELAITEST_RESET);
    }
  }
}
void modeDeTests_descendLaVentouse (void)
{
    //Partie de détection d'erreurs
  bool flagMouvementTermine = 0;
  static unsigned int compteurTempsTimeout = 0;
  if(flagMouvementTermine == 0)compteurTempsTimeout++;
  else compteurTempsTimeout = 0;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS)
  {
    updateMessageEcran("Oups! Timeout ventouse bas atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_VENTOUSE_BAS) == INTERFACEUSINE_SENSOR_HIGH) flagMouvementTermine = 1;

  //Partie fonctionnement
  updateEtatEcran("Descend Vent");

    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_HIGH);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_LOW);

  //Attend delai pour prochain etat
  if (delaiModeDeTest(DELAITEST_UTILISE))
  {
    modeTest_execute = modeDeTests_monteLaVentouse;
    delaiModeDeTest(DELAITEST_RESET);
  }
}
void modeDeTests_monteLaVentouse (void)
{
  //Partie de détection d'erreurs
  bool flagMouvementTermine = 0;
  static unsigned int compteurTempsTimeout = 0;
  if(flagMouvementTermine == 0)compteurTempsTimeout++;
  else compteurTempsTimeout = 0;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS)
  {
    updateMessageEcran("Oups! Timeout ventouse haut atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_VENTOUSE_HAUT) == INTERFACEUSINE_SENSOR_HIGH) flagMouvementTermine = 1;

  //Partie fonctionnement
  updateEtatEcran("Monte Vent.");

    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_DESCEND, INTERFACEUSINE_OUTPUT_LOW);
  interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_VENTOUSE_MONTE, INTERFACEUSINE_OUTPUT_HIGH);

  //AttendBtnPourProchainEtat
  updateMessageEcran("Pesez bouton vert   pour test Pont");
  if (interfaceUsine_BV.information == INFORMATION_DISPONIBLE)
  {
    interfaceUsine_BV.information = INFORMATION_TRAITEE;
    if (interfaceUsine_BV.etatDuBouton == INTERFACEUSINE_BV_APPUYE)
    {
      interfacePont_initialise();
      modeTest_execute = modeDeTests_attFinInitPont;
      interfaceUsine_RequetePont(INTERFACEUSINE_PONT_POSITIONH);
      updateMessageEcran("Test du pont en cours");
      delaiModeDeTest(DELAITEST_RESET);
    }
  }
}
void modeDeTests_attFinInitPont (void)
{
  updateEtatEcran("Deplace Vent.");
  
  static unsigned int compteurTempsInitPont = 0;
  compteurTempsInitPont++;
  if (compteurTempsInitPont >= DELAI_MAX_TESTS_PONT) //Timeout de 10sec
  {
    updateMessageEcran("Oups! Timeout init pont atteint");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }
  
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_MOTION_COMPLETE) == INTERFACEUSINE_SENSOR_HIGH)
  {
    compteurTempsInitPont = 0;
    updateMessageEcran("Init pont fini");
    modeTest_execute = modeDeTests_deplaceLaVentouse;
    interfacePont_pos2();
  }
  
}
void modeDeTests_deplaceLaVentouse (void)
{
  //Partie de détection d'erreurs
  static unsigned int compteurTempsTimeout = 0;
  compteurTempsTimeout++;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS_PONT)
  {
    updateMessageEcran("Oups! Timeout pont atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }



  updateEtatEcran("Deplace Vent.");
  if (interfacePont_fini())
  {
    compteurTempsTimeout = 0;
    modeTest_execute = modeDeTests_replaceLaventouse;
    interfacePont_pos0();
  }
}
void modeDeTests_replaceLaventouse (void)
{
  //Partie de détection d'erreurs
  static unsigned int compteurTempsTimeout = 0;
  compteurTempsTimeout++;
  if (compteurTempsTimeout >= DELAI_MAX_TESTS_PONT)
  {
    updateMessageEcran("Oups! Timeout pont atteint!");
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_erreur;
  }

  updateEtatEcran("Replace Vent.");
  if (interfacePont_fini())
  {
    compteurTempsTimeout = 0;
    modeTest_execute = modeDeTests_testeLaColonneLumineuse;
    updateMessageEcran("Pont fonctionnel");
  }
}

/**
 * @brief Cette fonction, appelée de façon récurrente, compte jusqu'à VALEUR_DELAI_MODE_DE_TEST, puis retourne un 1
 * cela permet de 
 * 
 * @param reset Reset le compteur du délai si on reçoit un 1 en paramètre
 * @return true si délai écoulé
 * @return false si délai en cours
 */
bool delaiModeDeTest (bool reset)
{
  
  //Paramètre d'entrée: 1 si on veut reset, 0 si on veut utiliser le délai
  //Paramètre de sortie: 1 si le délai est terminé, 0 si il n'est pas terminé
  static unsigned int iCompteurDelaiTest;
  if (reset) 
  {
    iCompteurDelaiTest = 0;
    return 0;
  }
  if (iCompteurDelaiTest >= VALEUR_DELAI_MODE_DE_TEST)
  {
    iCompteurDelaiTest = 0;
    return 1;
  }
  iCompteurDelaiTest++;
  return 0;
}

void modeTest_clignote(void)
{
  static unsigned int compteurTpsClignote;
    compteurTpsClignote++;
  if (compteurTpsClignote == TEST_VITESSELEDCLIGNOTE/2)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ETEINT);
  }
    if (compteurTpsClignote >= TEST_VITESSELEDCLIGNOTE)
  {
    interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_LED, INTERFACEUSINE_ALLUME);
    compteurTpsClignote = 0;
  }
}
#pragma endregion EtatsDuModeDeTests



void processusUsine_erreur (void)
{
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  ModuleData.State = States.error;
  #endif
  interfaceUsine_Reset ();
  updateModeEcran("Erreur");
  interfaceColonne_eteint(INTERFACECOLONNE_JAUNE);
  interfaceColonne_allume(INTERFACECOLONNE_ROUGE);
  interfaceColonne_eteint(INTERFACECOLONNE_VERT);
  static int compteurClignote;
  if (compteurClignote < 1000)
  if (compteurClignote > 1000) 
  if (compteurClignote > 2000) compteurClignote = 0;
  compteurClignote++;

  //Reinitialise le processus usine depuis le tout début
  /*
  #ifndef MODE_BYPASS_POSTE_DE_COMMANDE
  if(ModuleData.Mode == Modes.reinitialisation)
  {
    serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] =  processusUsine_initialise;
  }
  #endif
  */
}

void updateDiscColor(void)
{
  unsigned char tempTypeDeBloc;
  if (
      interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_ROUGE 
      && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_ROUGE 
      && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_ROUGE)
  {
    tempTypeDeBloc = BLOC_ROUGE;
  }

  else if (
      interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_NOIR 
      && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_NOIR 
      && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_NOIR)
  {
    tempTypeDeBloc = BLOC_NOIR;
  }

  else if (
      interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_METAL 
      && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_METAL 
      && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_METAL)
  {
    tempTypeDeBloc = BLOC_METAL;
  }

  else if (
      interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_CAP) == ETAT_CAPTEUR_CAP_POUR_BLOC_AUCUN 
      && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_MAG) == ETAT_CAPTEUR_MAG_POUR_BLOC_AUCUN 
      && interfaceUsine_LitUnElement(INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC) == ETAT_CAPTEUR_OPT_POUR_BLOC_AUCUN)
  {
    tempTypeDeBloc = BLOC_AUCUN;
    ModuleData_SetDiscColor(Values.disc_NoColor);
  }
  else
  {
    tempTypeDeBloc = BLOC_INCONNU;
    ModuleData_SetDiscColor(Values.disc_NoColor);
  }

  if (tempTypeDeBloc == BLOC_AUCUN)  ModuleData_SetDiscColor(Values.disc_NoColor);
  if (tempTypeDeBloc == BLOC_NOIR)  ModuleData_SetDiscColor(Values.disc_Black);
  if (tempTypeDeBloc == BLOC_ROUGE)  ModuleData_SetDiscColor(Values.disc_Red);
  if (tempTypeDeBloc == BLOC_METAL)  ModuleData_SetDiscColor(Values.disc_Silver);
}

void processusUsine_initialise(void)
{
  modeOperation_execute = modeOperation_lanceInitialisation;
  serviceBaseDeTemps_execute[PROCESSUSUSINE_GERE] = processusUsine_attente;
}