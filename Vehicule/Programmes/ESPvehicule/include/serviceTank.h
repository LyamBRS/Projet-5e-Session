/**
 * @file serviceTank.h
 * @author Camille Fortin  CamFo (camfortin2022@gmail.com)
 * @brief  
 * @version 0.1
 * @date 2022-11-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SERVICETANK_H
#define SERVICETANK_H

void serviceTank_initialise(void);
void serviceTank_tourneDroit(unsigned char vitesse);
void serviceTank_tourneGauche(unsigned char vitesse);
void serviceTank_uturnDroit(unsigned char vitesse);
void serviceTank_uturnGauche(unsigned char vitesse);

#endif