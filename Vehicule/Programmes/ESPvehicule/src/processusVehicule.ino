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
#include "xmain.h"
#include "xserviceBaseDeTemps.h"
#include "processusVehicule.h"
#include "ServiceCommunication.h"


//Définition Privé
void processusVehicule_Gere(void);



// Fonction du Processus
void processusVehicule_initialise(void)
{
    
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusVehicule_Gere;
}
void processusVehicule_Gere(void)
{
    if(ModuleData.Mode == Modes.reinitialisation)
    {
        ModuleData.State = States.waiting;
    }
    if(ModuleData.Mode == Modes.operation)
    {
        
    }


}