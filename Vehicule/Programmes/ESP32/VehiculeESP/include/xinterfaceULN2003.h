#ifndef INTERFACEULN2003_H
#define INTERFACEULN2003_H

//MODULE: interfaceULN2003
//DESCRIPTION: pour s'interfacer avec un module ULN2003APG qui permet de commander un moteur pas-a-pas unipolaire. 

//HISTORIQUE:
// 2022-10-18, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceULN2003_appliqueLesNiveaux(unsigned char IN1, unsigned char IN2, unsigned char IN3, unsigned char IN4);
void interfaceULN2003_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
