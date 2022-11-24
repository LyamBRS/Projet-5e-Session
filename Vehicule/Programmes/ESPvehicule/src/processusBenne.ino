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

// Définition Privé
void processusBenne_AttendBouttonEnFonction(void);


// Fonction du Processus

/// @brief Fonction qui initialise le processus gestion de la benne
/// @param Aucun
void processusBenne_initialise(void)
{
    
    serviceBaseDeTemps_execute[PROCESSUSVEHICULE_PHASE] = processusBenne_AttendBouttonEnFonction;
}

void processusBenne_AttendBouttonEnFonction(void)
{


}
void processusBenne_CourDelai(void)
{


}
void processusBenne_EnAjustement(void)
{

}
void processusBenne_EnMouvement(void)
{


}

/// @brief Fonction qui est appelé après un ajustementde la benne.
//  Elle attend une requête du processus véhicule pour larger le contenue de la Benne
/// @param  Aucun
void processusBenne_AttendUneRequete(void)
{

}