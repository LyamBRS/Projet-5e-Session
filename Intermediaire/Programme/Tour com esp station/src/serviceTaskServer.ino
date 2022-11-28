//serviceTaskServer:
//Historique: 
// 2021-04-16, Yves Roy, creation

//INCLUSIONS
#define _TASK_MICRO_RES  //requis par TaskScheduler
#include "xmain.h"
#include "xserviceTaskServer.h"

//Definitions privees
//pas de definitions privees
		
//Declarations de fonctions privees:
void serviceTaskServer_neFaitRien(void);
void serviceTaskServer_gereLesTaches(void);

//Definitions de variables privees:
//pas de variables privees


//Definitions de fonctions privees:
void serviceTaskServer_neFaitRien(void)
{
}

void serviceTaskServer_gereLesTaches(void)
{
  serviceTaskServer_execute();
}

//Definitions de variables publiques:
Scheduler serviceTaskServer_gestion; //doit etre defini avant Task pour que ca fonctionne
Task serviceTaskServer_tache(SERVICETASKSERVER_PERIODE_EN_US, TASK_FOREVER,  
    &serviceTaskServer_gereLesTaches, &serviceTaskServer_gestion, true);//doit etre precede de Scheduler
void (*serviceTaskServer_execute)(void);

//Definitions de fonctions publiques:
void serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup(void)
{
	serviceTaskServer_gestion.startNow();
//	serviceTaskServer_gestion.enableAll();    
}

void serviceTaskServer_initialise(void)
{
  serviceTaskServer_execute = serviceTaskServer_neFaitRien;
}
