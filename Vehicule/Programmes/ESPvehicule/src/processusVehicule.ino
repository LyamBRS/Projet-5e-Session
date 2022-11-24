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

#include "xmain.h"
#include "xserviceBaseDeTemps.h"
#include "processusVehicule.h"
#include "ServiceCommunication.h"
#include "xprocessusBenne.h"
#include "xprocessusConduite.h"


//Définition Privé
void processusVehicule_AttendUneRequete(void);
void processusVehicule_AttendArriveTri(void);
void processusVehicule_AttendFinChargement(void);
void processusVehicule_Uturn(void);
void processusVehicule_AttendArrivePesage(void);
void processusVehicule_AttendDechargementBenne(void);
void processusVehicule_AttendPriseParRobot(void);
void processusVehicule_Repositionnement(void);

// Fonction du Processus
void processusVehicule_initialise(void)
{
    
    if(processusBenne.etatDuModule != PROCESSUSBENNE_MODULE_EN_FONCTION)
    {
        return;
    }
    //piloteIOFeuArriereD_metAUn();
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_AttendUneRequete;
}
void processusVehicule_AttendUneRequete(void)
{
    if(ModuleData.Mode == Modes.reinitialisation)
    {
        ModuleData.State = States.waiting;
    }
    if(ModuleData.Mode == Modes.operation)
    {
        // processusConduite.requete = PROCESSUSCONDUITE_REQUETEACTIVE;
    }

    // Pour faire des test
    processusConduite.requete = PROCESSUSCONDUITE_REQUETEACTIVE;
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
        return;
    }
    ModuleData.StatesReceived.finishedSortingAndHasLoaded = PARSED;
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_Uturn;
}
void processusVehicule_Uturn(void)
{


}