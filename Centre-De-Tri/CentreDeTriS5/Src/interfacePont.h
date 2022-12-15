#ifndef INTERFACEPONT_H
#define INTERFACEPONT_H

<<<<<<< HEAD
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
=======
//MODULE: interfacePont
//DESCRIPTION: pour interagir avec le pont relie a un STM32F407. 

//HISTORIQUE:
// 2022-12-08, Karl Naudin, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles

//Dependances logicielles
>>>>>>> dee272e1a505a6efe1ca3ec339be59f1279cf86b
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
<<<<<<< HEAD
void interfacePont_Position1(void);
void interfaceT4_eteint(void);
void interfaceT4_initialise(void);
=======
void BaseDeTempsPont(unsigned char *ucLisBaseTempsPont);
void interfacePont_pos0 (void);
void interfacePont_pos1 (void);
void interfacePont_pos2 (void);
void interfacePont_initialise(void);
bool interfacePont_fini (void);

>>>>>>> dee272e1a505a6efe1ca3ec339be59f1279cf86b

//Variables publiques:
//pas de variables publiques

#endif
