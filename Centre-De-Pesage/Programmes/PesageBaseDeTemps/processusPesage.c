// ProcessusPesage
// Fichier contenant le state Machine du centre de pesage


#include "main.h"
#include "interfaceBras.h"
#include "interfaceBalance.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"
#include "processusPesage.h"
#include "processusDetection.h"

// Définition des variables privées
int compteur;
char reponse[64];
char commande[64];
int x;
int y;

void processusPesage_attendUneRequete(void);
void processusPesage_depose(void);
void processusPesage_attendFinDepot(void);
void processusPesage_prepareMesueBalance(void);
void processusPesage_attendLecture(void);
void processusPesage_repriseRondelle(void);
void processusPesage_disposeRondelle(void);
void processusPesage_gere(void);


void processusPesage_initialise(void)
{
    ModuleData.WeightToSend = UNUSED;
    processusPesage.unite = PROCESSUSPESAGE_UNITE_G;
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
    
    ModuleData.WeightToSend = 0x00;
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


    /////////////////////////////////////    TEST POUR LES UNITÉ     /////////////////////////////
    
    if(ModuleData.ValuesReceived.unit_Metric == RECEIVED) // Si on a recu un demande d'unité métrique on met notre unité a métrique 
    {
        ModuleData_SetUnits(Values.unit_Metric); 
        ModuleData.ValuesReceived.unit_Metric = PARSED;
        if(processusPesage.unite == PROCESSUSPESAGE_UNITE_OZ) // Si on est en imérial on change les unite de la balance
        {
            interfaceBalance_changeUnite();
        }
    }
    if(ModuleData.ValuesReceived.unit_Imperial == RECEIVED) // Si on a recu une demande d'unité Impérial on met notre unite a impérial
    {
        ModuleData_SetUnits(Values.unit_Imperial);
        ModuleData.ValuesReceived.unit_Imperial = PARSED;
        if(processusPesage.unite == PROCESSUSPESAGE_UNITE_G)  // Si on est en métrique on change l'unite de la balance
        {
            interfaceBalance_changeUnite();
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // On lance une détection
    processusDetection.requete = PROCESSUSDETECTION_REQUETE_ACTIVE;

    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_depose;

}
void processusPesage_depose(void)
{
    if(processusDetection.requete != PROCESSUSDETECTION_REQUETE_TRAITE)
    {
        return;
    }
    
    y = 100;
    x = 100;
    // Va mettre le poid su la balance
    sprintf(commande, "#1 G0 X%d Y%d Z-43 F8000\n", x, y);
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);

    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_attendFinDepot;
}

void processusPesage_attendFinDepot(void)
{
    compteur ++;
    if(compteur != PROCESSUSDETECTION_COMPTEPOURREPONSE_CMD)
    {
        return;
    }
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    if(reponse[0] != '$')
    {
        return;
    }
    
    compteur = 0;
    
    // ON envoie au bras d'arreter la ventouse
    sprintf(commande, "#1 M2231 V0\n");    
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_prepareMesueBalance;
}

void processusPesage_prepareMesueBalance(void)
{
    compteur ++;
    if(compteur <= 500) // Délais qui permet au bras de laché la rondelle
    {
        return;
    }
    interfaceBras_recoitUneReponse(reponse,64); // On attend la réponse du bras qui nous 
    printf("%s", reponse);                      // indique que la ventouse est a OFF
    fflush(stdout);
    if(reponse[0] != '$')
    {
        return;
    }
    
    // Si le decompte pour un delais est fini
    compteur = 0;
    
    interfaceBalance_prepareLecture();
    printf("Préparation de la lecture\n");
    fflush(stdout);
    
    sprintf(commande, "#1 G0 X%d Y%d Z0 F8000\n", x, y);  // On dit au bras de remonter a 0 pendant le pesage
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);

    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_attendLecture;
}
void processusPesage_attendLecture(void)
{
    char str[64];
    if(compteur <= 600) // Délais pour attendre avant de lire la réponse de la balance
    {
        compteur++;
        return;
    }
    
    
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    if(reponse[0] != '$')  // On attend d'avoir recu la réponse du bras qui confirme qu'il est monté
    {
        return;
    }
    
    // Quand le délais est terminé et que on a recu la réponse
    compteur = 0;
    interfaceBalance_lit(reponse);  // On lit la balance 

    for(int i=0; i<64;i++)
    {
        str[i] = reponse[i];
    }
    const char s[2] = " ";
    unsigned char index = 0;
    char *token;

    // get the first token
    token = strtok(str, s);

    // walk through other tokens
    while( token != NULL )
    {
      if(index == 1)
      {
          printf( "Poid: %s\n", token );
          processusPesage.weight = atoi(token);
          printf("%d\n", x);
      }
      if(index == 2)
      {
          printf( "Unite: %s\n", token );
          if(token[0] == 'g')
          {
              processusPesage.unite = PROCESSUSPESAGE_UNITE_G;
          }
          if(token[0] == 'o')
          {
              processusPesage.unite = PROCESSUSPESAGE_UNITE_OZ;
          }
      }
      token = strtok(NULL, s);
      index++;
    }
    //////////////////////////////////// ENVOIE DU POID ///////////////////////////////////
    
    // ENVOIE DU POID AU MASTER 
    ModuleData.WeightToSend = processusPesage.weight;
    
    /////////////////////////////////////////////////////////////////////////////////////// 




    /////////////////////////////////////    TEST POUR LES UNITÉ     /////////////////////////////
    
    if(ModuleData.ValuesReceived.unit_Metric == RECEIVED) // Si on a recu un demande d'unité métrique on met notre unité a métrique 
    {
        ModuleData_SetUnits(Values.unit_Metric); 
        ModuleData.ValuesReceived.unit_Metric = PARSED;
        if(processusPesage.unite == PROCESSUSPESAGE_UNITE_OZ) // Si on est en imérial on change les unite de la balance
        {
            interfaceBalance_changeUnite();
        }
    }
    if(ModuleData.ValuesReceived.unit_Imperial == RECEIVED) // Si on a recu une demande d'unité Impérial on met notre unite a impérial
    {
        ModuleData_SetUnits(Values.unit_Imperial);
        ModuleData.ValuesReceived.unit_Imperial = PARSED;
        if(processusPesage.unite == PROCESSUSPESAGE_UNITE_G)  // Si on est en métrique on change l'unite de la balance
        {
            interfaceBalance_changeUnite();
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // on dit au bras de redescendre prendre la rondelle 
    sprintf(commande, "#1 G0 X%d Y%d Z-43 F8000\n", x, y); 
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_repriseRondelle;
}

void processusPesage_repriseRondelle(void)
{
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    if(reponse[0] != '$')  // On attend d'avoir recu la réponse du bras qui confirme qu'il est REDESCENDU
    {
        return;
    }
    
    sprintf(commande, "#1 M2231 V1\n");    
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    if(compteur <= 600) // Délais pour attendre avant d'envoyer une autre commande au bras
    {
        compteur++;
        return;
    }
    
    // quand le delais est fini on envoie un autre commande
    compteur = 0;
    
    x = 100;  // Coordonné de lespace de stockage des rondelles
    y = 100;
    sprintf(commande, "#1 G0 X%d Y%d Z100 F8000\n", x, y);   // on envoie une commande pour qu'il remonte avec la rondelle
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_disposeRondelle;
}

void processusPesage_disposeRondelle(void)
{
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    if(reponse[0] != '$')  // On attend d'avoir recu la réponse du bras qui confirme qu'il a monté avec la rondelle
    {
        return;
    }
    
    sprintf(commande, "#1 G0 X%d Y%d Z-60 F8000\n", x, y);  // Coordonné pour aller stocker la rondelle
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    if(compteur <= 600) // Délais pour attendre avant d'envoyer une autre commande au bras
    {
        compteur++;
        return;
    }
    
    sprintf(commande, "#1 M2231 V0\n");    // Commande pour relacher la rondelle 
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_gere;
}

void processusPesage_gere(void)
{
    

}