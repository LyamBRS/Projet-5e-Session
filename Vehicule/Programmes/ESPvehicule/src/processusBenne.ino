/**
 * @file processusBenne.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * 
 * @brief Le processus Benne est un State Machine qui gêre les requêtes 
 *  de déchargement de la benne et sa calibrartion.
 * 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCUSIONS
#include "xmain.h"
#include "xserviceBaseDeTemps.h"
#include "xprocessusBenne.h"
#include "xinterfaceEntree1.h"
#include "xinterfaceMoteurBenne.h"

// Définition Privé
void processusBenne_AttendBouttonEnFonction(void);
void processusBenne_TestEntree1(void);


// Fonction du Processus


/**
 * @brief Fonction qui initialise le State Machine du processus Benne.
 *  
 */
void processusBenne_initialise(void)
{
    processusBenne.requete = PROCESSUSBENNE_REQUETE_TRAITE;
    processusBenne.etatDuModule = PROCESSUSBENNE_MODULE_PAS_EN_FONCTION;
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_AttendBouttonEnFonction;
}
/**
 * @brief État du processus Benne qui attend que la limite switch de la 
 *  benne soit en fonction pour pouvoir faire des lectures fiable de l'interrupteur.
 * 
 */
void processusBenne_AttendBouttonEnFonction(void)
{
    if(interfaceEntree1.etatDuModule == INTERFACEENTREE1_MODULE_PAS_EN_FONCTION)
    {
        return;
    }
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_TestEntree1;
}
/**
 * @brief État du processus Benne qui test l'interrupteur pour savoir ou la benne
 *  est rendu.
 * 
 */
void processusBenne_TestEntree1(void)
{
    if(interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_ACTIVE)
    {
        interfaceMoteurBenne_allume();
        serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_EnAjustement;
    }
    if(interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_INACTIVE)
    {
        interfaceMoteurBenne_allume();
        serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_EnMouvement;
    }

}
/**
 * @brief État du processus Benne qui fais tourner le moteur de 
 *  la benne en attendant que l'interrupteur soit appuyé. 
 * 
 */
void processusBenne_EnMouvement(void)
{
    if(interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_INACTIVE)
    {
        return;
    }
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_EnAjustement;
}
/**
 * @brief État du processus Benne qui attend le front montant de l'interrupteur 
 *  pour arrêter le moteur de la benne au moment ou elle est droite. 
 * 
 */
void processusBenne_EnAjustement(void)
{
    if(interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_ACTIVE)
    {
        return;
    }
    interfaceMoteurBenne_eteint();
    processusBenne.etatDuModule = PROCESSUSBENNE_MODULE_EN_FONCTION;
    processusBenne.requete = PROCESSUSBENNE_REQUETE_TRAITE;
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_AttendUneRequete;
}
/**
 * @brief Fonction qui est appelé après un ajustementde la benne.
 *   L'état attend une requête pour larger le contenue de la Benne.
 *      
 * @param void
 */
void processusBenne_AttendUneRequete(void)
{
    if(processusBenne.requete != PROCESSUSBENNE_REQUETE_ACTIVE)
    {
        return;
    }
    interfaceMoteurBenne_allume();
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_EnMouvement;
}