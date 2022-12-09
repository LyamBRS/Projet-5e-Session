#ifndef INTERFACEPONT_H
#define INTERFACEPONT_H

//MODULE: interfacePont
//DESCRIPTION: pour interagir avec le pont relie a un STM32F407. 

//HISTORIQUE:
// 2022-12-08, Karl Naudin, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void BaseDeTempsPont(unsigned char *ucLisBaseTempsPont);
void interfacePont_pos0 (void);
void interfacePont_pos1 (void);
void interfacePont_pos2 (void);
void interfacePont_initialise(void);
bool interfacePont_fini (void);


//Variables publiques:
//pas de variables publiques

#endif
