// ProcessusPesage
// Fichier contenant le state Machine du centre de pesage


#include "main.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"
#include "processusPesage.h"
#include "processusDetection.h"

// Définition des variables privées


void processusPesage_attendUneRequete(void);
void processusPesage_gere(void);

void processusPesage_initialise(void)
{
    
    processusPesage.requete = PROCESSUSPESAGE_REQUETE_TRAITE;
    processusPesage.etatDuModule = PROCESSUSPESAGE_MODULE_PAS_EN_FONCTION;
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_attendUneRequete;
}


void processusPesage_attendUneRequete(void)
{
    if(ModuleData.Mode == Modes.pause)
    {
        ModuleData.State = States.paused;
    }
    if(ModuleData.Mode == Modes.reinitialisation)
    {
        ModuleData.State = States.waiting;
    }
    
    // Si on recois le mode Opération on commence a detecté
    if(ModuleData.Mode != Modes.operation)
    {
        return;
    }
    
    ModuleData.State = States.waitingToWeight;
    // Si le véhicule est a la station de pesage
    if(ModuleData.StatesReceived.atWeightStation != RECEIVED)
    {
        return;
    }
    
    // Si le véhicule a bien le bloc dans sa benne 
    if(ModuleData.StatesReceived.finishedSortingAndHasLoaded != RECEIVED)
    {
        return;
    }
    
    if(ModuleData.ValuesReceived.disc_Silver != RECEIVED)
    {
        return;
    }
    
    ModuleData.StatesReceived.atWeightStation = PARSED;
    ModuleData.StatesReceived.finishedSortingAndHasLoaded = PARSED;
    ModuleData.ValuesReceived.disc_Silver = PARSED;
    ModuleData_SetAll_ValuesReceived(PARSED);
    ModuleData_SetAll_StatesReceived(PARSED);
    
    processusPesage.requete = PROCESSUSPESAGE_REQUETE_TRAITE;
    processusPesage.etatDuModule = PROCESSUSPESAGE_MODULE_EN_FONCTION;
    
    // On lance une détection
    processusDetection.requete = PROCESSUSDETECTION_REQUETE_ACTIVE;
    
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_gere;
    
}
void processusPesage_gere(void)
{
    if(processusDetection.requete != PROCESSUSDETECTION_REQUETE_TRAITE)
    {
        return;
    }
    
    
    
}