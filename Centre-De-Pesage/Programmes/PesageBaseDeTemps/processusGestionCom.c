// Processus Gestion de Communication


#include "main.h"
#include "interfaceBalance.h"
#include "serviceBaseDeTemps.h"
#include "processusGestionCom.h"
#include "processusPesage.h"
#include "processusDetection.h"
#include "ServiceCommunication.h"


// Variable privé
int compteurCom;


void processusGestionCom_Gere(void);


void processusGestionCom_initialise(void)
{
    compteurCom = 0;
    processusPesage.unite = PROCESSUSPESAGE_UNITE_G;
    ModuleData_SetUnits(Values.unit_Metric);
    serviceBaseDeTemps_execute[PROCESSUSGESTIONCOM_PHASE] = processusGestionCom_Gere;
}



void processusGestionCom_Gere(void)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    static unsigned char old_CantConnect = 0xFF;
    ////////////////////////////////////////////////////////////////////////////////////////////////
    compteurCom++;
    if(compteurCom <= 800)  // Petit délasi pour s'assurer que la balamnce est en fonction
    {
        return;
    }
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
        //printf("------------------------- METRIC\n");
        //ModuleData_SetUnits(Values.unit_Metric); 
        ModuleData.CommandsReceived.units_Metric = PARSED;
        //printf("On c'est fait dire d'être en Métric (g)\n");
        if(processusPesage.unite == PROCESSUSPESAGE_UNITE_OZ) // Si on est en imérial on change les unite de la balance
        {
            printf("On était en Métric donc on change pour Métric\n");
            processusPesage.unite = PROCESSUSPESAGE_UNITE_G;
            interfaceBalance_changeUnite();
        }
        processusPesage.unite = PROCESSUSPESAGE_UNITE_G;
    }
    if(ModuleData.CommandsReceived.units_Imperial == RECEIVED) // Si on a recu une demande d'unité Impérial on met notre unite a impérial
    {
        //printf("------------------------- IMPERIAL\n");
        //ModuleData_SetUnits(Values.unit_Imperial);
        ModuleData.CommandsReceived.units_Imperial = PARSED;
        //printf("On c'est fait dire d'être en Impérial (Oz)\n");
        if(processusPesage.unite == PROCESSUSPESAGE_UNITE_G)  // Si on est en métrique on change l'unite de la balance
        {
            printf("On était en Métric donc on change pour Impérial\n");
            processusPesage.unite = PROCESSUSPESAGE_UNITE_OZ;
            interfaceBalance_changeUnite();
        }
        processusPesage.unite = PROCESSUSPESAGE_UNITE_OZ;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    if(processusPesage.unite == PROCESSUSPESAGE_UNITE_G)
    {
        ModuleData_SetUnits(Values.unit_Metric);
    }
    else
    {
        ModuleData_SetUnits(Values.unit_Imperial);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    if(ModuleData.CantConnect != old_CantConnect)
    {
        //Print connection successful
        if(ModuleData.CantConnect == 0x00)
        {
            printf("[CAN]: Connection CAN établie\n");
        }
        else
        {
            printf("[CAN]: Connection perdue\n");            
        }
        
        old_CantConnect = ModuleData.CantConnect;
    }
}