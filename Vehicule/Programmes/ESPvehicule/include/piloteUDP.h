/**
 * @file piloteUDP.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PILOTEUDP_H
#define PILOTEUDP_H

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
void piloteUDP_initialise(void);
int GetUDPSize();
void receiveUDP1(void);
void transUDP1(unsigned char send[255]);
//Variables publiques:
typedef struct
{
  unsigned char replyBuffer[8]; //buffer to hold incoming packet
  unsigned char readBuffer[8];  //buffer to send packet

} stPILOTEUDP;


stPILOTEUDP piloteUDP;

#endif