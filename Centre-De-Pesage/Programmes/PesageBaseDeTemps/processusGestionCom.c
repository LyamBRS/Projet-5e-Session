// Processus Gestion de Communication


#include "main.h"
#include "interfaceBalance.h"
#include "serviceBaseDeTemps.h"
#include "processusGestionCom.h"
#include "processusPesage.h"
#include "processusDetection.h"
#include "ServiceCommunication.h"


// Variable privé
int compteur;


void processusGestionCom_Gere(void);


void processusGestionCom_initialise(void)
{
    processusPesage.unite = PROCESSUSPESAGE_UNITE_G;
    ModuleData_SetUnits(Values.unit_Metric);
    serviceBaseDeTemps_execute[PROCESSUSGESTIONCOM_PHASE] = processusGestionCom_Gere;
}



void processusGestionCom_Gere(void)
{
    if(processusDetection.information == PROCESSUSDETECTION_INFORMATION_CUBEDETECTED)
    {
        ModuleData_SetDiscDetection(Values.disc_Detected);
    }
    if(processusDetection.information == PROCESSUSDETECTION_INFORMATION_CUBEUNUSED)
    {
        ModuleData_SetDiscDetection(Values.disc_Lost);
    }
    
    /////////////////////////////////////    TEST POUR LES UNITÉ     /////////////////////////////
    if(ModuleData.CommandsReceived.units_Metric == RECEIVED) // Si on a recu un demande d'unité métrique on met notre unité a métrique 
    {
        ModuleData_SetUnits(Values.unit_Metric); 
        ModuleData.CommandsReceived.units_Metric = PARSED;
        if(processusPesage.unite == PROCESSUSPESAGE_UNITE_OZ) // Si on est en imérial on change les unite de la balance
        {
            interfaceBalance_changeUnite();
        }
    }
    if(ModuleData.CommandsReceived.units_Imperial == RECEIVED) // Si on a recu une demande d'unité Impérial on met notre unite a impérial
    {
        ModuleData_SetUnits(Values.unit_Imperial);
        ModuleData.CommandsReceived.units_Imperial = PARSED;
        if(processusPesage.unite == PROCESSUSPESAGE_UNITE_G)  // Si on est en métrique on change l'unite de la balance
        {
            interfaceBalance_changeUnite();
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
}