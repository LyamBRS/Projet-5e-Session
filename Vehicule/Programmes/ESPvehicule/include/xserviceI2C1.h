#ifndef SERVICEI2C1_H
#define SERVICEI2C1_H

//MODULE: serviceI2C1
//DESCRIPTION: pour mettre en place un service de gestion de l'acces au port I2C
//L'acces au port I2C1 est permis lorsque serviceI2C1_acces = SERVICEI2C1_ACCES_PERMIS et
//il ne l'est pas lorsque serviceI2C1_acces = SERVICEI2C1_ACCES_INTERDIT
//Un module obtient l'usage exclusif du port I2C en mettant serviceI2C_acces a
//SERVICEI2C1_INTERDIT et il libere le port en mettant serviceI2C_acces a
//SERVICEI2C1_PERMIS.
//Le module qui a un acces exclusif au port I2C1 doit faire appel aux fonctions
//du module piloteI2C1 pour communiquer I2C et liberer le service une fois
//ses transactions terminees.

//HISTORIQUE:
// 2021-11-22, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define SERVICEI2C1_ACCES_PERMIS 1
#define SERVICEI2C1_ACCES_INTERDIT 0

//Fonctions publiques:
void serviceI2C1_initialise(void);

//Variables publiques:
extern unsigned char serviceI2C1_acces;

#endif
