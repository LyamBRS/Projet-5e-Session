/**
 * @file piloteUDP.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief Le pilote UDP sers à la communication wifi UDP
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

/// @brief Fonction d'initialisation du piloteUDP
/// @param  void
void piloteUDP_initialise(void);

/// @brief Fonction permettant de savoir la longueur d'un packet UDP
/// @return Un entier indiquant la quantité de caractère du packet
int GetUDPSize();

/// @brief Fonction permettant de recevoir un packet envoyé en par wifi en utilisant UDP
/// @param  void
void receiveUDP1(void);

/// @brief Fonction qui envoie un packet UDP
/// @param send Buffer with maximum of 255 unsigned char
void transUDP1(unsigned char send[255]);

//Variables publiques:
typedef struct
{
  /// @brief Buffer to send packet
  unsigned char replyBuffer[8]; 

  /// @brief Buffer to hold incoming packet
  unsigned char readBuffer[8];

} stPILOTEUDP;

/// @brief Structure contenant 2 tableau de 8 unsigned char pour la réception et la transmition UDP
stPILOTEUDP piloteUDP;

#endif