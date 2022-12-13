/**
 * @file processusVehicule.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Processus qui gere le véhicule du projet de 5eme session de TSO.
 *  Le \ref xprocessusVehicule.h gere les requetes de transport de rondelles 
 *  envoyé par les autres modules du projet. Il utilise le \ref ServiceCommunication.h
 *  ainsi que sa structure \ref ModuleData pour savoir quand conduire les rondelles.
 * 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCUSIONS
#include "xpiloteIOFeuArriereD.h"
#include "piloteUDP.h"
#include <stdio.h>

#include "xinterfaceSuiveur.h"

#include "xmain.h"
#include "xserviceBaseDeTemps.h"
#include "processusVehicule.h"
#include "serviceTank.h"
#include "ServiceCommunication.h"
#include "xprocessusBenne.h"
#include "xprocessusConduite.h"

// Variable Privé

/**
 * @brief Compteur utilisé pour des délais avec la base de temps
 */
int compteurT = 0;


//Définition Privé


void processusVehicule_AttendUneRequete(void);
void processusVehicule_AttendArriveTri(void);
void processusVehicule_AttendFinChargement(void);
void processusVehicule_Uturn(void);
void processusVehicule_AttendArrivePesage(void);
void processusVehicule_Repositionnement(void);
void processusVehicule_AttendDechargementBenne(void);
void processusVehicule_AttendPriseParRobot(void);


//********* Fonction du Processus Vehicule ***********//

/**
 * @brief  Fonction d'initialisation du Processus Véhicule
 *  
 */
void processusVehicule_initialise(void)
{
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendUneRequete;
}
/**
 * @brief Fonction qui permet de gêrer les requêtes envoyé au véhicule par les autre modules 
 *  du projet en utilisant la structure \ref ModuleData qui est mise a jour par \ref ServiceCommunication.h
 *  
 * @return * void 
 */
void processusVehicule_AttendUneRequete(void)
{
    static unsigned char lastError = 0;

    if(lastError != serviceCommunication_ErrorState)
    {
        printf("CURRENT ERROR CODE: %i\n",serviceCommunication_ErrorState);
        //serviceCommunication_ErrorState = NO_ERROR;
        lastError = serviceCommunication_ErrorState;
    }

    // Test si la benne est bien calibré
    /*
    if(processusBenne.etatDuModule != PROCESSUSBENNE_MODULE_EN_FONCTION)
    {
        return;
    }
    */

    // Test Pour la communication
    if(ModuleData.Mode == Modes.pause)
    {
        ModuleData.State = States.paused;
    }

    if(ModuleData.Mode == Modes.reinitialisation)
    {
        ModuleData.State = States.waiting;
    }
    if(ModuleData.Mode == Modes.emergencyStop)
    {
        ModuleData.State = States.emergencyStop;
    }

    if(ModuleData.Mode != Modes.operation)
    {
        
        return;
    }
    ModuleData.State = States.calibrating;
    if(ModuleData.StatesReceived.waitingToSort != RECEIVED)
    {
        printf("%i",ModuleData.Mode);
        ModuleData.State = States.waiting;
        return;
    }
    //ModuleData_SetAll_ValuesReceived(PARSED);
    //ModuleData_SetAll_StatesReceived(PARSED);

    compteurT = 0; //On s'assusre que le compteur est a 0 avant de commencer une séquence
    processusConduite.requete = PROCESSUSCONDUITE_REQUETE_ACTIVE;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendArriveTri;
}
/**
 * @brief État du processus Véhicule qui attend la fin du processus Conduite 
 *  et donc d'être arrivé au centre de tri. 
 * 
 * @param void
 */
void processusVehicule_AttendArriveTri(void)
{
    ModuleData.State = States.processing;
    if(processusConduite.etatDuModule != PROCESSUSCONDUITE_MODULE_ARRIVE_TRI)
    {
        return;
    }

    ModuleData.State = States.atSortingFactory;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendFinChargement;
}

/**
 * @brief État du processus Véhicule qui attend que le véhicule soit chargé par le centre de tri.
 *  L'information envoyé par le centre de tri est geré par \ref ModuleData.
 *   
 * @param void
 */
void processusVehicule_AttendFinChargement(void)
{
    ModuleData.State = States.atSortingFactory;
    if(ModuleData.StatesReceived.finishedSortingAndHasLoaded != RECEIVED)  
    {
        return;
    }
    ModuleData.StatesReceived.finishedSortingAndHasLoaded = PARSED;

    serviceTank_uturnDroit(PROCESSUSCONDUITE_VITESSESTANDARD);
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_Uturn;
}
/**
 * @brief État du processus Véhicule qui attend que le véhicule aille fini d'avoir effectué 
 *  sont 180 pour continuer vers le centre de pesage
 * 
 * @param void
 */
void processusVehicule_Uturn(void)
{
    ModuleData.State = States.processing;
    if(compteurT < 800) //Un bref delais avant de checker le suiveur pour etre sur 
    {                   //qu'il ne reprenne pas la ligne sans avoir fais de 180
        compteurT++;
        return;
    }

    unsigned char suiveurValue;
    suiveurValue = interfaceSuiveur_litOctet();
    if(suiveurValue != 0xE4)
    {
        return;
    }
    serviceTank_Arret(); // Si le suiveur a vu la ligne au milieu
    processusConduite.requete = PROCESSUSCONDUITE_REQUETE_ACTIVE;
    compteurT = 0;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendArrivePesage;
}
/**
 * @brief État du processus Véhicule qui attend la fin du processus Conduite 
 *  et donc d'être arrivé au centre de pesage. 
 * @param void
 */
void processusVehicule_AttendArrivePesage(void)
{
    ModuleData.State = States.processing;
    if(processusConduite.etatDuModule != PROCESSUSCONDUITE_MODULE_ARRIVE_PESAGE)
    {
        return;
    }
    serviceTank_uturnGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_Repositionnement;
}

/**
 * @brief État du processus Véhicule qui attend la fin de sont repositionnement 
 * pour ensuite être déchargé par le bras robot ou en descendant sa benne
 * 
 * @return * void 
 */
void processusVehicule_Repositionnement(void)
{
    ModuleData.State = States.processing;
    // ############## 
    if(compteurT < 700) //Un bref delais avant de checker le suiveur pour etre sur 
    {                   //qu'il ne reprenne pas la ligne sans avoir fais de 180
        compteurT++;
        return;
    }
    // ##############


    unsigned char suiveurValue;
    suiveurValue = interfaceSuiveur_litOctet();
    if(suiveurValue != 0xE4)
    {
        return;
    }
    serviceTank_Arret(); // Si le suiveur a vu la ligne au milieu il est en position
    ModuleData.State = States.atWeightStation;

    // SI la rondelle est en Métal
    if(ModuleData.ValuesReceived.disc_Silver == RECEIVED)
    {
        ModuleData.ValuesReceived.disc_Silver = PARSED;
        serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendPriseParRobot;
        return;
    }

    //SI la rondelle est une rondelle Orange
    if(ModuleData.ValuesReceived.disc_Red == RECEIVED)
    {
        ModuleData.ValuesReceived.disc_Red = PARSED;
        processusBenne.requete = PROCESSUSBENNE_REQUETE_ACTIVE;
        serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendDechargementBenne;
        return;
    } 
}

/**
 * @brief État du processus Véhicule qui attend la fin du déchargement de la benne
 * 
 * @return * void 
 */
void processusVehicule_AttendDechargementBenne(void)
{
    // On attend que la benne finisse de décharger
    
    if(processusBenne.requete != PROCESSUSBENNE_REQUETE_TRAITE)
    {
        return;
    }
    
    ModuleData_SetAll_StatesReceived(PARSED);
    ModuleData_SetAll_ValuesReceived(PARSED);
    ModuleData.State = States.empty;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendUneRequete;
    // ON A fini de décharger
}

/**
 * @brief État du processus Véhicule qui attend la prise par le bras robot et la fin du pesage de bloc
 * 
 * @return * void 
 */
void processusVehicule_AttendPriseParRobot(void)
{
    ModuleData.State = States.atWeightStation;
    if(ModuleData.StatesReceived.finishedWeighting != RECEIVED)
    {
        return;   
    }
    // SI le bras a bel et bien pris la rondelle
    ModuleData_SetAll_StatesReceived(PARSED);
    ModuleData_SetAll_ValuesReceived(PARSED);
    ModuleData.State = States.empty;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendUneRequete;
}