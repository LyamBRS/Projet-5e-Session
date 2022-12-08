//piloteUSBbal
//Historique: 
//2018-11-12, Yves Roy, creation

//voir le site https://en.wikibooks.org/wiki/Serial_Programming/termios
//pour des explications
//un bon site: http://unixwiz.net/techtips/termios-vmin-vtime.html

//INCLUSIONS
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "main.h"
#include "piloteUSBbal.h"

//Definitions privees
//#define piloteUSBbras_TTY "/dev/ttyACM0"

#define piloteUSBbal_TTY "/dev/ttyUSB0"

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
int piloteUSBbal_fichier;
struct termios piloteUSBbal_configuration;

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
int piloteUSBbal_initialise(void)
{
  memset(&piloteUSBbal_configuration,0,sizeof(piloteUSBbal_configuration));
  piloteUSBbal_configuration.c_iflag=0;
  piloteUSBbal_configuration.c_oflag=0;
  piloteUSBbal_configuration.c_cflag=0; //CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
  piloteUSBbal_configuration.c_lflag=0;
  piloteUSBbal_configuration.c_cc[VMIN]= 0; //1;
  piloteUSBbal_configuration.c_cc[VTIME]=0; //5;

  piloteUSBbal_fichier = open(piloteUSBbal_TTY, O_RDWR | O_NONBLOCK);
  
  if (piloteUSBbal_fichier == -1)
  {
    printf("erreur d'ouverture de la balance\n");
    return 1;
  }
  
  if(tcgetattr(piloteUSBbal_fichier, &piloteUSBbal_configuration) < 0)
  {
    printf("erreur de lecture d'attributs\n");
    return 1;
  }

  //configuration en entree
  piloteUSBbal_configuration.c_iflag &= ~IGNBRK; //pas de "break" en entrée
  piloteUSBbal_configuration.c_iflag &= ~BRKINT; //pas d'interruptions en entrée
  piloteUSBbal_configuration.c_iflag &= ~ICRNL;  //pas de conversion \n en entrée
  piloteUSBbal_configuration.c_iflag &= ~INLCR;  //pas de conversion \r en entrée
  piloteUSBbal_configuration.c_iflag &= ~PARMRK; //pas d'erreur de parité en entrée
  piloteUSBbal_configuration.c_iflag &= ~INPCK;  //pas de vérification de la parité en entrée
  piloteUSBbal_configuration.c_iflag &= ~ISTRIP; //pas de retrait de la bit de poids fort en entrée
  piloteUSBbal_configuration.c_iflag &= ~IXON;   //pas de XON/XOFF en entrée

  //configuration en sortie
  piloteUSBbal_configuration.c_oflag &= ~OCRNL;  //pas de conversion \r en \n en sortie
  piloteUSBbal_configuration.c_oflag &= ~ONLCR;  //pas de conversion \n en \r en sortie
  piloteUSBbal_configuration.c_oflag &= ~ONLRET; //pas de conversion \n en ret en sortie
  piloteUSBbal_configuration.c_oflag &= ~ONOCR;  //pas de suppression de colonne 0 en sortie
  piloteUSBbal_configuration.c_oflag &= ~OFILL;  //pas de remplissage par des caracteres en sortie
  piloteUSBbal_configuration.c_oflag &= ~OLCUC;  //pas de conversion des minuscules en majuscules
  piloteUSBbal_configuration.c_oflag &= ~OPOST;  //pas de traitement local en sortie
  //ONOEOT cause erreur

  //configuration pour les lignes
  piloteUSBbal_configuration.c_lflag &= ~ECHO;   //pas d'echo
//  piloteUSBbal_configuration.c_lflag &= ~ECHONL; //pas d'echo pour les changements de ligne
  piloteUSBbal_configuration.c_lflag |= ECHONL; //echo pour les changements de ligne
  piloteUSBbal_configuration.c_lflag &= ~IEXTEN; //pas de traitement des entrees "extended"
  piloteUSBbal_configuration.c_lflag &= ~ISIG ;  //pas de signalisation de caracteres
  piloteUSBbal_configuration.c_lflag &= ~ECHOE;  //pas d'echo...
  piloteUSBbal_configuration.c_lflag |= ICANON;  //mode canonique pour fonctionner par ligne
//  piloteUSBbal_configuration.c_lflag &= ~ICANON;  //mode canonique pour ne pas fonctionner par ligne
  
//configuration materielle
  piloteUSBbal_configuration.c_cflag &= ~CSIZE; //efface la configuration actuelle du nombre de bits
  piloteUSBbal_configuration.c_cflag &= ~PARENB; //pas de parite 
  piloteUSBbal_configuration.c_cflag |= CS8; // 8 bits
  
  piloteUSBbal_configuration.c_cflag &= ~CRTSCTS;  //pas de traitement local en sortie  
  

  //configuration des lectures si en mode "raw"
  piloteUSBbal_configuration.c_cc[VMIN]  = 0;  
  piloteUSBbal_configuration.c_cc[VTIME] = 20;  
//  piloteUSBbal_configuration.c_cc[VMIN]  = 1;  //au moins un octet a la fois
//  piloteUSBbal_configuration.c_cc[VTIME] = 0;  //pas de "timeout"  

  if (cfsetispeed(&piloteUSBbal_configuration, PILOTEUSBBAL_BAUDRATE_AVEC_B_AU_DEBUT) < 0)
  {
    return -1;
  }
  if (cfsetospeed(&piloteUSBbal_configuration, PILOTEUSBBAL_BAUDRATE_AVEC_B_AU_DEBUT) < 0)
  {
    return -1;
  }

  if(tcsetattr(piloteUSBbal_fichier, TCSAFLUSH, &piloteUSBbal_configuration) < 0)  
  
  {
    return -1;
  }
  
  tcflush(piloteUSBbal_fichier, TCIOFLUSH);
  return 0;
}

int piloteUSBbal_termine(void)
{
  
  tcflush(piloteUSBbal_fichier, TCIOFLUSH);   
  close(piloteUSBbal_fichier);
  return 0;
}



int piloteUSBbal_ecrit(char *Source, unsigned char NombreATransmettre)
{
  tcflush(piloteUSBbal_fichier, TCOFLUSH);  
  return (int)write(piloteUSBbal_fichier,Source, NombreATransmettre);
}

int piloteUSBbal_attendLaFinDeLEcriture(void)
{
  return (int)tcdrain(piloteUSBbal_fichier);
}

int piloteUSBbal_lit(char *Destination, unsigned char NombreMaximalDeLectures)
{
int retour = read(piloteUSBbal_fichier, Destination, NombreMaximalDeLectures);  
  tcflush(piloteUSBbal_fichier, TCIFLUSH);  
  return retour;
}
