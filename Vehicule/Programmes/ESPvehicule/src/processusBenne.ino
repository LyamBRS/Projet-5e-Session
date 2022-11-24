/**
 * @file processusBenne.ino
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
#include "xprocessusBenne.h"
#include "xinterfaceEntree1.h"
#include "xinterfaceMoteurBenne.h"

// Définition Privé
void processusBenne_AttendBouttonEnFonction(void);
void processusBenne_TestEntree1(void);


// Fonction du Processus

/// @brief Fonction qui initialise le processus gestion de la benne
/// @param Aucun
void processusBenne_initialise(void)
{
    processusBenne.requete = PROCESSUSBENNE_REQUETEINACTIVE;
    processusBenne.etatDuModule = PROCESSUSBENNE_MODULE_PAS_EN_FONCTION;
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_AttendBouttonEnFonction;
}

void processusBenne_AttendBouttonEnFonction(void)
{
    if(interfaceEntree1.etatDuModule == INTERFACEENTREE1_MODULE_PAS_EN_FONCTION)
    {
        return;
    }
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_TestEntree1;
}
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

void processusBenne_EnMouvement(void)
{
    if(interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_INACTIVE)
    {
        return;
    }
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_EnAjustement;
}
void processusBenne_EnAjustement(void)
{
    if(interfaceEntree1.etatDeLEntree == INTERFACEENTREE1_ACTIVE)
    {
        return;
    }
    interfaceMoteurBenne_eteint();
    processusBenne.etatDuModule = PROCESSUSBENNE_MODULE_EN_FONCTION;
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_AttendUneRequete;
}


/// @brief Fonction qui est appelé après un ajustementde la benne.
//  Elle attend une requête du processus véhicule pour larger le contenue de la Benne
/// @param  Aucun
void processusBenne_AttendUneRequete(void)
{
    if(processusBenne.requete == PROCESSUSBENNE_REQUETEINACTIVE)
    {
        return;
    }
    interfaceMoteurBenne_allume();
    serviceBaseDeTemps_execute[PROCESSUSBENNE_PHASE] = processusBenne_EnMouvement;
}