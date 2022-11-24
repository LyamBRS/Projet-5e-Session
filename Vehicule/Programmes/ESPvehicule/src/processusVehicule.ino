/**
 * @file processusVehicule.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCUSIONS
#include "xpiloteIOFeuArriereD.h"

#include "xinterfaceSuiveur.h"

#include "xmain.h"
#include "xserviceBaseDeTemps.h"
#include "processusVehicule.h"
#include "serviceTank.h"
#include "ServiceCommunication.h"
#include "xprocessusBenne.h"
#include "xprocessusConduite.h"

// Variable Privé
int compteurT = 0;
int compteurR = 0;

//Définition Privé
void processusVehicule_AttendUneRequete(void);
void processusVehicule_AttendArriveTri(void);
void processusVehicule_AttendFinChargement(void);
void processusVehicule_Uturn(void);
void processusVehicule_AttendArrivePesage(void);
void processusVehicule_Repositionnement(void);
void processusVehicule_AttendDechargementBenne(void);
void processusVehicule_AttendPriseParRobot(void);


// Fonction du Processus
void processusVehicule_initialise(void)
{
    
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendUneRequete;
}
void processusVehicule_AttendUneRequete(void)
{
    // Test si la benne est bien calibré
    if(processusBenne.etatDuModule != PROCESSUSBENNE_MODULE_EN_FONCTION)
    {
        return;
    }

    // Test Pour la communication
    if(ModuleData.Mode == Modes.reinitialisation)
    {
        ModuleData.State = States.waiting;
    }
    if(ModuleData.Mode == Modes.operation)
    {
        // Acive la requete de conduite
    }

    // Pour faire des test normalement c'est les if de communication qui vont mettre la requete de Conduite active
    processusConduite.requete = PROCESSUSCONDUITE_REQUETE_ACTIVE;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendArriveTri;
}

void processusVehicule_AttendArriveTri(void)
{
    if(processusConduite.etatDuModule != PROCESSUSCONDUITE_MODULE_ARRIVE_TRI)
    {
        return;
    }
    ModuleData.State = States.atSortingFactory;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendFinChargement;

}
void processusVehicule_AttendFinChargement(void)
{
    if(ModuleData.StatesReceived.finishedSortingAndHasLoaded != RECEIVED)  
    {
        //return;
    }
    ModuleData.StatesReceived.finishedSortingAndHasLoaded = PARSED;

    if(compteurT < 1000) //Calcul pour ajouter un delai pour les test c'est l'attente du chargement
    {
        compteurT++;
        return;
    }
    compteurT = 0;
    serviceTank_uturnGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_Uturn;
}
void processusVehicule_Uturn(void)
{
    if(compteurT < 400) //Un bref delais avant de checker le suiveur pour etre sur 
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
void processusVehicule_AttendArrivePesage(void)
{
    if(processusConduite.etatDuModule != PROCESSUSCONDUITE_MODULE_ARRIVE_PESAGE)
    {
        return;
    }
    serviceTank_uturnGauche(PROCESSUSCONDUITE_VITESSESTANDARD);
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_Repositionnement;
}

void processusVehicule_Repositionnement(void)
{

    // ############## 
    if(compteurT < 400) //Un bref delais avant de checker le suiveur pour etre sur 
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


    // SI la rondelle est en Métal 
    //serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendPriseParRobot;
    
    //SI la rondelle est une rondelle Orange
    processusBenne.requete = PROCESSUSBENNE_REQUETE_ACTIVE;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendDechargementBenne;
}
void processusVehicule_AttendDechargementBenne(void)
{
    if(processusBenne.etatDuModule != PROCESSUSBENNE_REQUETE_TRAITE)
    {
        return;
    }
    

    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendUneRequete;
    // ON A fini de décharger
}
void processusVehicule_AttendPriseParRobot(void)
{

    // SI le bras a bel et bien pris la rondelle
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendUneRequete;
}