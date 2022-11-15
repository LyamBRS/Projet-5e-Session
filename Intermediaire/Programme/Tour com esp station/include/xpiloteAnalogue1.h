#ifndef PILOTEANALOGUE1_H
#define PILOTEANALOGUE1_H

//MODULE: piloteAnalogue1
//DESCRIPTION: pour permettre la lecture d'une entree analogue
//ENVIRONNEMENT ESP32 et Arduino 
//exemple de reference : https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
//exemple de video : https://www.youtube.com/watch?v=RlKMJknsNpo&t=145s
//La configuration du convertisseur qui est utilisée impose:
//une conversion a 12 bits
//une representation des valeurs avec 12 bits
//une attenuation de 11dB pour une plage d'entree allant de 0 a 3v
//l'initialisation ferait en sorte qu'une acquisition prendrait 433us environ
//selon https://www.youtube.com/watch?v=RlKMJknsNpo&t=145s
//un marge de manoeuvre recommandee peut donc etre obtenue attendant plus de 1ms avant
//de faire une autre conversion (voir les specifications techniques du esp32 a ce sujet)

// 2021-04-19, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEANALOGUE1_BROCHE A4

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned int piloteAnalogue1_lit(void);
void piloteAnalogue1_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
