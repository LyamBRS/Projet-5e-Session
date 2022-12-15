#ifndef INTERFACEUSINE_H
#define INTERFACEUSINE_H

//MODULE: interfaceT4
//DESCRIPTION: pour interagir avec un temoin lumineux T4 relie a un STM32F407. 

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACET4_VALEUR_POUR_ALLUMER  1   
//#define INTERFACET4_VALEUR_POUR_ETEINDRE 0

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
/**
 * @brief Valeur de l'état du bouton vert du centre de tri lorsqu'il n'est pas appuyé.
 * 
 */
#define INTERFACEUSINE_BV_RELACHE  0

/**
 * @brief Valeur de l'état du bouton vert du centre de tri lorsqu'il est appuyé.
 * 
 */
#define INTERFACEUSINE_BV_APPUYE  1
#define INTERFACEUSINE_BV_INCONNU 2

/**
 * @brief Valeur de l'état du bouton rouge du centre de tri lorsqu'il n'est pas appuyé.
 * 
 */
#define INTERFACEUSINE_BR_RELACHE  0

/**
 * @brief Valeur de l'état du bouton rouge du centre de tri lorsqu'il n'est pas appuyé.
 * 
 */
#define INTERFACEUSINE_BR_APPUYE  1
#define INTERFACEUSINE_BR_INCONNU 2
//pas de definitions publiques

//Fonctions publiques:

/**
 * @brief Cette fonction est la fonction qu'il faut appeler pour écrire une valeur a un des entrées de l'usine.
 * @example 
 * @param elementID identifiant de l'élément de l'usine duquel on veut changer l'état
 * @param etatAEcrire 
 */
void interfaceUsine_EcritUnElement (unsigned char elementID, bool etatAEcrire);
bool interfaceUsine_LitUnElement (unsigned char elementID);
unsigned char interfaceUsine_LitADC (void);
void interfaceUsine_gere (void);
void interfaceUsine_Initialise (void);
void interfaceUsine_Reset (void);

//bool interfaceUsine_DetecteUnFrontSurLeBoutonVert (void);

typedef struct
{
  //unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDuBouton;
} INTERFACEBOUTON;

extern INTERFACEBOUTON interfaceUsine_BV;
extern INTERFACEBOUTON interfaceUsine_BR;



bool interfaceUsine_RequetePont (unsigned char ucPositiondemandee);
unsigned char interfaceUsine_PositionPont(void);
unsigned char interfaceUsine_EtatPont(void);
    
#define INTERFACEUSINE_PONT_ETAT_ERREUR 0
#define INTERFACEUSINE_PONT_ETAT_EN_COURS 1
#define INTERFACEUSINE_PONT_ETAT_FINI 2

#define INTERFACEUSINE_PONT_REQUETE_TRAITEE 0
#define INTERFACEUSINE_PONT_POSITION_DEPLACEMENT 0
#define INTERFACEUSINE_PONT_POSITIONH 1
#define INTERFACEUSINE_PONT_POSITION0 2
#define INTERFACEUSINE_PONT_POSITION1 3
#define INTERFACEUSINE_PONT_POSITION2 4

//Variables publiques:
//pas de variables publiques

#endif
