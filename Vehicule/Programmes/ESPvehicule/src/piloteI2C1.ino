/**
 * @file piloteI2C1.ino
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief   Fichier conteneant le code du pilote I2C fonctionnant avec 
 *    un ESP32. Le pilote utilise la librairie \ref Wire.h fourni avec 
 *    l'environnement arduino. 
 * 
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include <Wire.h>
#include "xmain.h"
#include "xpiloteI2C1.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:


/// @brief Fonction qui lit un octect précédament envoyé sur le port I2C 
/// @param Adresse Adresse I2C
/// @return La valeur lu sur le port I2C
unsigned char piloteI2C1_lisUnOctet(unsigned char Adresse)
{
  Wire.requestFrom((uint8_t)Adresse, (uint8_t)1);
  return (unsigned char)(Wire.read()); 
}
/// @brief Fonction qui ecris un Octet sur le port I2C
/// @param Adresse 
/// @param Octet 
void piloteI2C1_ecritUnOctet(unsigned char Adresse, unsigned char Octet)
{
  Wire.beginTransmission((uint8_t)Adresse);
  Wire.write((uint8_t)Octet);
  Wire.endTransmission();
}
/// @brief Fonction qui lit un entier (unsigned int) recu sur le port I2C
/// @param Adresse 
/// @return Un entier recu sur le port I2C (unsigned int)
unsigned int piloteI2C1_lisUnEntier(unsigned char Adresse)
{
  Wire.requestFrom((uint8_t)Adresse, (uint8_t)2);
  return (unsigned int)(Wire.read() | (((unsigned int)Wire.read()) << 8));   
}
/// @brief Fonction qui écrit un entier (unsigned int) sur le port I2C
/// @param Adresse 
/// @param Entier 
void piloteI2C1_ecritUnEntier(unsigned char Adresse, unsigned int Entier)
{
  Wire.beginTransmission((uint8_t)Adresse);
  Wire.write((unsigned char)(Entier >> 8));
  Wire.write((unsigned char)(Entier & 0xFF));
  Wire.endTransmission();  
}
/// @brief Fonction qui lit un registre d'un microcontrôleur avec le port I2C
/// @param Adresse Adresse I2C
/// @param Registre Adresse du registre à lire 
/// @param ValeurLue L'adresse de la variable ou mettre la valeur du registre lu
void piloteI2C1_litUnRegistre(unsigned char Adresse, unsigned char Registre, char *ValeurLue)
{
  Wire.beginTransmission(Adresse);
  Wire.write(Registre);
  Wire.endTransmission();
  while(Wire.available())
  {
    Serial.print("bug");
    Wire.read();
  }
  Wire.requestFrom((int)Adresse, (int)1);
  Wire.available();
  *ValeurLue = Wire.read();
}
/// @brief Fonction qui écrit dans un registre d'un microcontrôleur avec le port I2C
/// @param Adresse Adresse I2C
/// @param Registre Adresse du registre à lire 
/// @param Octet Valeur qu'on veut envoyé dans le registre 
void piloteI2C1_ecritUnOctetDansUnRegistre(unsigned char Adresse, unsigned char Registre, char Octet)
{
  Wire.beginTransmission(Adresse);
  Wire.write(Registre);
  Wire.write(Octet);
  Wire.endTransmission();
}
/// @brief Fonction qui permet de lire automatiquement plusieurs registre d'un microcontrôleur 
/// @param Adresse Adresse I2C
/// @param Registre Première adresse des registre à lire 
/// @param Nombre Nombre de registre qui doivent être lu
/// @param ValeursLues L'adresse du tableau ou mettre les valeurs des registres lu
void piloteI2C1_litAutomatiquementDesRegistres(unsigned char Adresse, unsigned char Registre, unsigned char Nombre, char *ValeursLues)
{
unsigned char indice;
  Wire.beginTransmission(Adresse);
  Wire.write(Registre);
  Wire.endTransmission();
  while(Wire.available())
  {
    Wire.read();
  }
  Wire.requestFrom((int)Adresse, (int)Nombre);
  Wire.available();
  for (indice = 0; indice < Nombre; indice++) 
  {
    ValeursLues[indice] = Wire.read();
  }
}
/// @brief Fonction qui initialise le port I2C
/// @param  Aucun
void piloteI2C1_initialise(void)
{
  Wire.begin(PILOTEI2C1_SDA, PILOTEI2C1_SCL, PILOTEI2C1_FREQUENCE_D_HORLOGE_EN_HZ);
}
