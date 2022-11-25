#ifndef PILOTEUDPSTATION_H
#define PILOTEUDPSTATION_H

//MODULE: piloteEntree1
//DESCRIPTION: pour permettre la lecture d'une entree
//ENVIRONNEMENT ESP32 et Arduino 
// 2021-04-04, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteUDPStation_initialise(void);
void ServiceUDPStation(void);
void receiveUDP(void);
void transUDP(unsigned char* transmitBuffer, char sizeOfBuffer);
//Variables publiques:
char readBuf[8];
//pas de variables publiques

#endif
