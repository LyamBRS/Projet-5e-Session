#ifndef SERVICETASKSERVER_H
#define SERVICETASKSERVER_H

//MODULE: serviceTaskServer
//DESCRIPTION: pour permettre des appels périodiques de fonctions
//La fonction d'initialisation du module permet de mettre des appels periodiques en place.
//Il faut faire appel a la fonction serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup pour lancer les appels periodiques.
//Le pointeur de fonction serviceTaskServer_execute sert a pointer la fonction qui sera appelee periodiquement apres le lancement du module
//L'initialisation du module fait en sorte que le pointeur de fonction serviceTaskServer_execute pointe par defaut une fonction qui ne fait rien
//Il faut faire en sorte que le pointeur de fonction serviceTaskServer_execute pointe la fonction a appelee periodiquement avant de lancer le module
//a l'aide de la fonction serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup (ex. serviceTaskServer_execute = serviceBaseDeTemps_gere)
//Comme l'indique son nom, la fonction serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup doit etre appelee a la toute fin de la fonction setup
//pour s'assurer que toutes les initialisations des pointeurs de fonctions du systeme a base de temps sont faites avant de lancer le module.
//Ce module remplace les modules qui utilisent des interruptions de "timers" pour mettre en place des appels periodiques de fonctions plutot que
//d'avoir recours aux fonctionnalites de RTOS.

//HISTORIQUE:
// 2021-04-16, Yves Roy, creation
// 2022-04-11, Yves Roy, ajout a la description

//DEFINITIONS REQUISES PAR LE MODULE:
// ==== Uncomment desired compile options =================================
// #define _TASK_SLEEP_ON_IDLE_RUN  // Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
// #define _TASK_TIMECRITICAL       // Enable monitoring scheduling overruns
// #define _TASK_STATUS_REQUEST     // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only
// #define _TASK_WDT_IDS            // Compile with support for wdt control points and task ids
// #define _TASK_LTS_POINTER        // Compile with support for local task storage pointer
// #define _TASK_PRIORITY           // Support for layered scheduling priority
#define _TASK_MICRO_RES          // Support for microsecond resolution
//#define _TASK_STD_FUNCTION       // Support for std::function (ESP8266 and ESP32 ONLY)
// #define _TASK_DEBUG              // Make all methods and variables public for debug purposes
// #define _TASK_INLINE             // Make all methods "inline" - needed to support some multi-tab, multi-file implementations
// #define _TASK_TIMEOUT            // Support for overall task timeout
// #define _TASK_OO_CALLBACKS       // Support for dynamic callback method binding
// #define _TASK_DEFINE_MILLIS      // Force forward declaration of millis() and micros() "C" style
// #define _TASK_EXPOSE_CHAIN       // Methods to access tasks in the task chain
// #define _TASK_SCHEDULING_OPTIONS // Support for multiple scheduling options
#include <TaskScheduler.h>  ////https://www.arduino.cc/reference/en/libraries/taskscheduler/

//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define SERVICETASKSERVER_PERIODE_EN_US 4000

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void serviceTaskServer_initialise(void);
void serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup(void);

//Variables publiques:
extern Scheduler serviceTaskServer_gestion;
extern Task serviceTaskServer_tache;//attention: la definition doit etre precedee de celle du Scheduler pour que ca fonctionne
extern void (*serviceTaskServer_execute)(void);

#endif
