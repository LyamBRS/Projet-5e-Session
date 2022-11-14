#ifndef PILOTEI2C1_H
#define PILOTEI2C1_H

//MODULE: piloteI2C1
//DESCRIPTION: pour permettre l'emploi d'un port I2C

// 2021-07-08, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEI2C1_SCL    19  //22 pour adafruit
//#define PILOTEI2C1_SDA    18  //21 pour adafruit
//#define PILOTEI2C1_FREQUENCE_D_HORLOGE_EN_HZ 400000

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
unsigned char piloteI2C1_lisUnOctet(unsigned char Adresse);
void piloteI2C1_ecritUnOctet(unsigned char Adresse, char Octet);
unsigned int piloteI2C1_lisUnEntier(unsigned char Adresse);
void piloteI2C1_ecritUnEntier(unsigned char Adresse, unsigned int Entier);
void piloteI2C1_litUnRegistre(unsigned char Adresse, unsigned char Registre, char *ValeurLue);
void piloteI2C1_ecritUnOctetDansUnRegistre(unsigned char Adresse, unsigned char Registre, char Octet);
void piloteI2C1_litAutomatiquementDesRegistres(unsigned char Adresse, unsigned char Registre, unsigned char Nombre, char *ValeursLues);
void piloteI2C1_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
