//******************************************************************************
//   Nom du fichier : GLcd.h
//   Auteur : Alain Champagne                  
//      Date de création : 16-03-2006 
//      Date de modification pour le STM32F4 : 23-12-2015
//        Fichier de déclaration et de définission pour les fonctions de 
//        contrôle d'un écran graphique de type KS0108.
// 
//******************************************************************************


//******************************************************************************
//                            DECLARATION ET DEFINITION                         
//******************************************************************************


#ifndef XGLCD_H
  #define XGLCD_H

//Include
#include "stm32f4xx_hal.h"                       //Définition pour le KIT ARM
#include "IO_BUS.h"       
#include "main.h"

//Define
#define ADRINSTRLEFTR 0x06
#define ADRINSTRRIGHTR 0x05                          
#define ADRINSTRLEFTW 0x02
#define ADRINSTRRIGHTW 0x01
#define ADRDATALEFTR 0x0E
#define ADRDATARIGHTR 0x0D                          
#define ADRDATALEFTW 0x0A
#define ADRDATARIGHTW 0x09
#define ADRBUSYFLAG 0x04

//Predeclaration externe                     
uint8_t ucInputGLcd(uint8_t ucAdresse);
void vOutputGLcd(uint8_t ucAdresse, uint8_t ucDonnee);
void vDelaiGLcd(uint16_t uiTemps);  
void vInitGLcd(void);
void vClearGLcd                                 (uint8_t ucData); 
void vPutPixelGLcd                              (uint8_t ucX, uint8_t ucY);
void vClearPixelGLcd                            (uint8_t ucX, uint8_t ucY);                                             
void vDrawLineGLcd                              (uint8_t ucX, uint8_t ucY, uint8_t ucLong, uint8_t ucDir); 
void vDrawRectangleGLcd                         (uint8_t ucX1, uint8_t ucY1, uint8_t ucX2, uint8_t ucY2); 
void vDrawCircleGLcd                            (uint8_t ucX, uint8_t ucY, uint8_t ucRayon); 

void vPutCharGLcd                               (uint8_t ucChar, uint8_t ucLigne, uint8_t ucColonne, uint8_t ucFont);
void vPutCharGLcdINV                            (uint8_t ucChar, uint8_t ucLigne, uint8_t ucColonne, uint8_t ucFont);

void vPutStringGLcd                             (char const ucTab[], int8_t iLigneLcd, uint8_t ucFont);
void vPutStringGLcdINV                          (char const ucTab[], int8_t iLigneLcd, uint8_t ucFont);

void vPutBMPGLcd                                (uint8_t ucTab[]);
void vPutBMPGLcdINV                             (uint8_t ucTab[]);



#endif 