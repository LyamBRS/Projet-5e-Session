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
int compteur = 0;
char reponse[64];
char commande[64];
int x2;
int y2;

void processusPesage_attendUneRequete(void);
void processusPesage_depose(void);
void processusPesage_attendFinDepot(void);
void processusPesage_prepareMesureBalance(void);
void processusPesage_attendLecture(void);
void processusPesage_repriseRondelle(void);
void processusPesage_repriseRondellePart2(void);
void processusPesage_disposeRondelle(void);
void processusPesage_gere(void);
void processusPesage_retourEtatInit(void);

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
    
    //printf("ON a recu OPÉRATION\n");
    ModuleData.WeightToSend = 0x00;
    ModuleData.State = States.waitingToWeight;
    // Si le véhicule est a la station de pesage
    if(ModuleData.StatesReceived.atWeightStation != RECEIVED)
    {
        return;
    }
    printf("ON est en Waiting to Weight\n");
    // Si le véhicule a bien le bloc dans sa benne
    if(ModuleData.StatesReceived.finishedSortingAndHasLoaded != RECEIVED)
    {
        return;
    }

    if(ModuleData.ValuesReceived.disc_Silver != RECEIVED)
    {
        return;
    }
    printf("Démarrage de la détection\n");
    ModuleData.StatesReceived.atWeightStation = PARSED;
    ModuleData.StatesReceived.finishedSortingAndHasLoaded = PARSED;
    ModuleData.ValuesReceived.disc_Silver = PARSED;
    ModuleData_SetAll_ValuesReceived(PARSED);
    ModuleData_SetAll_StatesReceived(PARSED);

    processusPesage.requete = PROCESSUSPESAGE_REQUETE_TRAITE;
    processusPesage.etatDuModule = PROCESSUSPESAGE_MODULE_EN_FONCTION;

    
    // On lance une détection
    processusDetection.requete = PROCESSUSDETECTION_REQUETE_ACTIVE;
    compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_depose;

}
void processusPesage_depose(void)
{
    ModuleData.State = States.processing;
    if(processusDetection.requete != PROCESSUSDETECTION_REQUETE_TRAITE)
    {
        return;
    }
    //printf("processusPesage_depose: Fin du procesSUS de détection\n");
    
    compteur++;
    if(compteur <= 1000)
    {
        return;
    }
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    printf("processusPesage_depose: Fin de la remonté!\n");
    
    y2 = -278;
    x2 = 81;
    
    printf("On va a la Balance\n");
    // Va mettre le poid sur la balance
    sprintf(commande, "#1 G0 X%d Y%d Z-43 F8000\n", x2, y2);  // On va au coordonne de la balance
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_attendFinDepot;
}

void processusPesage_attendFinDepot(void)
{
    compteur ++;
    if(compteur <= 2000)  // Gros délais pour s'assurer que le bras est rendu a la balance
    {
        return;
    }
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    
    /*
    if(reponse[0] != '$')
    {
        return;
    }
    */
    compteur = 0;
    printf("On Relache le Cube\n");
    // ON envoie au bras d'arreter la ventouse
    sprintf(commande, "#6 M2231 V0\n");    
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_prepareMesureBalance;
}

void processusPesage_prepareMesureBalance(void)
{
    compteur ++;
    if(compteur <= 500) // Délais qui permet au bras de laché la rondelle
    {
        return;
    }
    interfaceBras_recoitUneReponse(reponse,64); // On attend la réponse du bras qui nous 
    printf("%s", reponse);                      // indique que la ventouse est a OFF
    fflush(stdout);
    
    /*
    if(reponse[0] != '$')
    {
        return;
    }
    */
    
    // Si le decompte pour un delais est fini
    compteur = 0;
    
    interfaceBalance_prepareLecture();
    printf("Préparation de la lecture\n");
    fflush(stdout);
    
    sprintf(commande, "#1 G0 X%d Y%d Z0 F8000\n", x2, y2);  // On dit au bras de remonter a 0 pendant le pesage
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);

    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_attendLecture;
}
void processusPesage_attendLecture(void)
{
    char str[64];
    compteur++;
    if(compteur <= 1000) // Délais pour attendre avant de lire la réponse de la balance
    {
        return;
    }
    
    
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    /*
    if(reponse[0] != '$')  // On attend d'avoir recu la réponse du bras qui confirme qu'il est monté
    {
        return;
    }
    */
    
    // Quand le délais est terminé on assume qu'on est pret 
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
          printf("%d\n", processusPesage.weight);
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
    
    // on dit au bras de redescendre prendre la rondelle 
    sprintf(commande, "#1 G0 X%d Y%d Z-43 F8000\n", x2, y2); 
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_repriseRondelle;
}

void processusPesage_repriseRondelle(void)
{
    memset(reponse, 0, 64); // On vide le buffer de réponse 
    
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    
    /*
    if(reponse[0] != '$')  // On attend d'avoir recu la réponse du bras qui confirme qu'il est REDESCENDU
    {
        return;
    }
    
    */
    
    if(compteur <= 1000) // Délais pour attendre avant d'envoyer une autre commande au bras
    {
        compteur++;
        return;
    }
    
    sprintf(commande, "#1 M2231 V1\n");   // ON allume la ventouse
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_repriseRondellePart2;
}


void processusPesage_repriseRondellePart2(void)
{
    if(compteur <= 1000) // Délais pour attendre avant d'envoyer une autre commande au bras
    {
        compteur++;
        return;
    }
    
    // quand le delais est fini on envoie un autre commande
    interfaceBras_recoitUneReponse(reponse,64);  // On lit la reponse meme si on l'utilise pas 
    printf("%s", reponse);
    fflush(stdout);
    
    sprintf(commande, "#1 G0 X%d Y%d Z100 F8000\n", x2, y2);   // on envoie une commande pour qu'il remonte avec la rondelle
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_disposeRondelle; 
}


void processusPesage_disposeRondelle(void)
{
    
    /*
    if(reponse[0] != '$')  // On attend d'avoir recu la réponse du bras qui confirme qu'il a monté avec la rondelle
    {
        return;
    }
    */
    if(compteur <= 1000) // Délais pour attendre avant d'envoyer une autre commande au bras
    {
        compteur++;
        return;
    }
    
    memset(reponse, 0, 64);
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    
    x2 = 200;  // Coordonné de lespace de stockage des rondelles
    y2 = 150;
    sprintf(commande, "#1 G0 X%d Y%d Z-86 F8000\n", x2, y2);  // Coordonné pour aller stocker la rondelle
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_gere;
}

void processusPesage_gere(void)
{
    memset(reponse, 0, 64);
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    
    if(compteur <= 3000) // Délais pour attendre que le bras soit en position
    {
        compteur++;
        return;
    }
    
    
    sprintf(commande, "#2 M2231 V0\n");    // Commande pour relacher la rondelle 
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_retourEtatInit;
}

void processusPesage_retourEtatInit(void)
{
    if(compteur <= 1000) // Délais pour attendre avant d'envoyer une autre commande au bras
    {
        compteur++;
        return;
    }
    
    sprintf(commande, "#1 G0 X200 Y0 Z100 F8000\n");    // Commande pour retourner en position d'init
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    compteur = 0;
    
    
    serviceBaseDeTemps_execute[PROCESSUSPESAGE_PHASE] = processusPesage_attendUneRequete;
}