#include "main.h"
#include <linux/i2c-dev.h> //for IOCTL defs

#include "piloteI2C1.h"
#define PILOTEI2C1_FICHIER "/dev/i2c-1" 

//variables privées
uint8_t piloteI2C1_adresse;
int piloteI2C1_fichier;

//fonctions privées
//pas de fonctions privées

//variables publiques
//pas de variables publiques

//fonctions publiques
int piloteI2C1_fermeLeBus(void)
{
	if (close(piloteI2C1_fichier) < 0)
	{
		printf("erreur: piloteI2C1_fermeLeBus\n");
	    return -1;
	}
    piloteI2C1_adresse = 0;
	return 0;
}

int piloteI2C1_ecritDesOctets(uint8_t *Source, uint8_t NombreDOctetsAEcrire)
{
	if(write(piloteI2C1_fichier, Source, NombreDOctetsAEcrire) != NombreDOctetsAEcrire)
	{
		printf("erreur: piloteI2C1_ecritDesOctets\n");
		close(piloteI2C1_fichier);
		return -1;
	}
	return 0;
}

int piloteI2C1_litDesOctets(uint8_t *Commande, uint8_t LongueurDeLaCommande,
		uint8_t *Destination, uint8_t NombreDOctetsALire)
{
    if (piloteI2C1_ecritDesOctets(Commande, LongueurDeLaCommande) < 0)
    {
    	printf("erreur: piloteI2C1_litDesOctets 1\n");
    	close(piloteI2C1_fichier);
    	return -1;
    }
	if (read(piloteI2C1_fichier, Destination, NombreDOctetsALire) != NombreDOctetsALire)
	{
		printf("erreur: piloteI2C1_litDesOctets 2\n");
		close(piloteI2C1_fichier);
		return -1;
	}
	return 0;
}

int piloteI2C1_configureLAdresse(uint8_t Adresse)
{
	if(piloteI2C1_adresse == Adresse)
	{
		return 0;
	}
	if(ioctl(piloteI2C1_fichier, I2C_SLAVE, Adresse) < 0)
	{
		printf("erreur: piloteI2C1_configureLAdresse\n");
		close(piloteI2C1_fichier);
		return -1;
	}
	piloteI2C1_adresse = Adresse;
	return 0;
}

int piloteI2C1_initialise(void)
{
	piloteI2C1_adresse = 0x00;
	piloteI2C1_fichier = open(PILOTEI2C1_FICHIER, O_RDWR);
	if(piloteI2C1_fichier == -1)
	{
		printf("erreur: pilote_initialilse 1\n");
		return -1;
	}
	if(ioctl(piloteI2C1_fichier, I2C_SLAVE, piloteI2C1_adresse) < 0)
	{
		printf("erreur: piloteI2C1_initialise 2\n");
		close(piloteI2C1_fichier);
		return -1;
	}
	return 0;
}
