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
//pas de definitions publiques

//Fonctions publiques:
void interfaceUsine_EcritUnElement (unsigned char elementID, bool etatAEcrire);
bool interfaceUsine_LitUnElement (unsigned char elementID);
void interfaceUsine_gere (void);
void interfaceUsine_Initialise (void);

  void interfaceUsine_PontHome (void);
  void interfaceUsine_PonPos1 (void);
  void interfaceUsine_PonPos2 (void);
  void interfaceUsine_PonPos3 (void);
    
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
