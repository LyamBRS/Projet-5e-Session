#ifndef PILOTEUART2_H
#define PILOTEUART2_H

//MODULE: piloteUART2
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteUART2_RX(void);
void piloteUART2_TX(unsigned char);
void piloteUART2_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
