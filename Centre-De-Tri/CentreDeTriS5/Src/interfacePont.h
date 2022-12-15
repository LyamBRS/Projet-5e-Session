#ifndef INTERFACEPONT_H
#define INTERFACEPONT_H

<<<<<<< HEAD
<<<<<<< HEAD
//MODULE: interfaceT4
//DESCRIPTION: pour interagir avec un temoin lumineux T4 relie a un STM32F407. 
=======
//MODULE: interfacePont
//DESCRIPTION: pour interagir avec le pont relie a un STM32F407. 
>>>>>>> 4da58d318c6ea7a702745249341195bc18bc6aac

//HISTORIQUE:
// 2022-12-08, Karl Naudin, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles

//Dependances logicielles
<<<<<<< HEAD
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
=======
>>>>>>> 4da58d318c6ea7a702745249341195bc18bc6aac
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
<<<<<<< HEAD
<<<<<<< HEAD
void interfacePont_Position1(void);
void interfaceT4_eteint(void);
void interfaceT4_initialise(void);
=======
=======
>>>>>>> 4da58d318c6ea7a702745249341195bc18bc6aac
void BaseDeTempsPont(unsigned char *ucLisBaseTempsPont);
void interfacePont_pos0 (void);
void interfacePont_pos1 (void);
void interfacePont_pos2 (void);
void interfacePont_initialise(void);
bool interfacePont_fini (void);

<<<<<<< HEAD
>>>>>>> dee272e1a505a6efe1ca3ec339be59f1279cf86b
=======
>>>>>>> 4da58d318c6ea7a702745249341195bc18bc6aac

//Variables publiques:
//pas de variables publiques

#endif
