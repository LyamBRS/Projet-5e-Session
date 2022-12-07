// ProcessusBras 
// Fichier contenant le state Machine de la détection d'un bloc


#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceVL6180x.h"
#include "interfaceBras.h"
#include "processusDetection.h"


// Définition des variables privées
char reponse[2000];
unsigned long processusDetection_compteur;
char commande[64];

float distance;
float dernieredistance = 25;


int x = 200;
int y = -100;
int z = PROCESSUSDETECTION_HAUTEUR_DE_SCAN;



void processusDetection_attendReponseInit(void);
void processusDetection_attendUneRequete(void);
void processusDetection_Bouge(void);
void processusDetection_attendReponseCmd(void);
void processusDetection_changeCoordonne(void);
void processusDetection_lit(void);
void processusDetection_alignement(void);
void processusDetection_descend(void);
void processusDetection_remonte(void);
void processusDetection_pese(void);


void processusDetection_initialise(void)
{
    processusDetection.requete = PROCESSUSDETECTION_REQUETE_TRAITE;
    processusDetection.etatDuModule = PROCESSUSDETECTION_MODULE_PAS_EN_FONCTION;
    serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_attendReponseInit;
}

void processusDetection_attendReponseInit(void)
{
    processusDetection_compteur ++;
    if(processusDetection_compteur != PROCESSUSDETECTION_COMPTEPOURREPONSE_INIT)
    {
        return;
    }

    
    processusDetection_compteur = 0;
    interfaceBras_recoitUneReponse(reponse,2000);
    printf("%s\n", reponse);
    fflush(stdout);
    memset(reponse, 0, sizeof reponse);
    
    serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_attendUneRequete;
}

void processusDetection_attendUneRequete(void)
{
    if(processusDetection.requete != PROCESSUSDETECTION_REQUETE_ACTIVE)
    {
        return;
    }
    
    processusDetection.requete = PROCESSUSDETECTION_REQUETE_TRAITE;
    processusDetection.etatDuModule = PROCESSUSDETECTION_MODULE_EN_FONCTION;
    serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_Bouge;
}




void processusDetection_Bouge(void)
{
    // Fonction qui gere les valeur de coordonnés
    processusDetection_changeCoordonne();

    
    sprintf(commande, "#1 G0 X%d Y%d Z%d F8000\n", x, y, z);
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_attendReponseCmd;
}

void processusDetection_attendReponseCmd(void)
{
    processusDetection_compteur ++;
    if(processusDetection_compteur != PROCESSUSDETECTION_COMPTEPOURREPONSE_CMD)
    {
        return;
    }
    processusDetection_compteur = 0;
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    
    serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_lit;
}

void processusDetection_lit(void)
{
    if (interfaceVL6180x_litUneDistance(&distance) < 0)
   	{
		printf("erreur: interfaceVL6180x_litUneDistance");
        fflush(stdout);		
        return;
    }
    if(dernieredistance <= 19)
    {
        if(distance <= 19)
        {
            //On a vu deux fois la meme distance donc c'est probablement le cube
            printf("CUUUBE\n");
            fflush(stdout);
            
            serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_alignement;
            return;
        }
    }
    
    dernieredistance = distance;
    printf("%2.1f\n", distance);
    fflush(stdout);
    serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_Bouge;
}



void processusDetection_alignement(void)
{
    x = x + 60;
    //y = y + 5;
    sprintf(commande, "#1 G0 X%d Y%d Z%d F8000\n", x, y, z);
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_descend;
}
void processusDetection_descend(void)
{
    processusDetection_compteur ++;
    if(processusDetection_compteur != 360) // Delai pour laisser le temps de descendre
    {
        return;
    }
    processusDetection_compteur = 0;
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    
    
    // A modifier pour tester la limit switch 
    if(z <= PROCESSUSDETECTION_HAUTEUR_DE_SCAN - 125)
    {
        // On allume la ventouse 
        sprintf(commande, "M2231 V1\n");    
        interfaceBras_ecritUneCommande(commande, sizeof commande);
        memset(commande, 0, 64);
        z = 100;
        
        serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_remonte;
        return;
    }
    
    z = PROCESSUSDETECTION_HAUTEUR_DE_SCAN - 125;
    sprintf(commande, "#1 G0 X%d Y%d Z%d F8000\n", x, y, z);
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    
}
void processusDetection_remonte(void)
{
    processusDetection_compteur ++;
    if(processusDetection_compteur != PROCESSUSDETECTION_COMPTEPOURREPONSE_CMD)
    {
        return;
    }
    processusDetection_compteur = 0;
    interfaceBras_recoitUneReponse(reponse,64);
    printf("%s", reponse);
    fflush(stdout);
    // On remonte a Z = 100
    sprintf(commande, "#1 G0 X%d Y%d Z%d F8000\n", x, y, z);
    interfaceBras_ecritUneCommande(commande, sizeof commande);
    memset(commande, 0, 64);
    
    processusDetection.requete = PROCESSUSDETECTION_REQUETE_TRAITE;
    serviceBaseDeTemps_execute[PROCESSUSDETECTION_PHASE] = processusDetection_pese;
}

void processusDetection_pese(void)
{
    
}


// Fonction Utilitaire Pour modifier les position
void processusDetection_changeCoordonne(void)
{
    y = y + 10;
    if(y == 100)
    {
        y = -100;
        x = x + 15;
    }
    
    // Pour recommencer la détection
    if(x >= 320)
    {
        x = 200;
    }
}