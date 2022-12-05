#include "main.h"
#include "piloteI2C1.h"
#include "interfaceVL6180x.h"

//pour des détails: https://www.st.com/resource/en/design_tip/dt0037-vl6180x-range-and-ambient-light-sensor-quick-setup-guide-stmicroelectronics.pdf


//définitions privée
typedef struct
{
	uint16_t adresse;
	uint8_t valeur;
} INTERFACEVL6810X_MESSAGE;

#define INTERFACEVL6180X_ADRESSE 0x29 
#define INTERFACEVL6180X_NOMBRE	40

//variables privées
INTERFACEVL6810X_MESSAGE interfaceVL6810x_message[INTERFACEVL6180X_NOMBRE] =
{
	{0x0207, 0x01}, {0x0208, 0x01}, {0x0096, 0x00}, {0x0097, 0xfd},
	{0x00e3, 0x00}, {0x00e4, 0x04},	{0x00e5, 0x02},	{0x00e6, 0x01},
	{0x00e7, 0x03},	{0x00f5, 0x02},	{0x00d9, 0x05},	{0x00db ,0xce},
	{0x00dc, 0x03},	{0x00dd, 0xf8},	{0x009f, 0x00},	{0x00a3, 0x3c},
	{0x00b7, 0x00},	{0x00bb, 0x3c},	{0x00b2, 0x09},	{0x00ca, 0x09},
	{0x0198, 0x01},	{0x01b0, 0x17},	{0x01ad, 0x00},	{0x00ff, 0x05},
	{0x0100, 0x05},	{0x0199, 0x05},	{0x01a6, 0x1b},	{0x01ac, 0x3e},
	{0x01a7, 0x1f},	{0x0030, 0x00},
	{0x0011, 0x10},// Enables polling for ‘New Sample ready’ when measurement completes
	{0x010a, 0x30},// Set the averaging sample period (compromise between lower noise and increased execution time)
	{0x003f, 0x46},// Sets the light and dark gain (upper nibble). Dark gain should not be changed.
	{0x0031, 0xFF},// sets the # of range measurements after which auto calibration of system is performed 
	{0x0040, 0x63},// Set ALS integration time to 100ms
	{0x002e, 0x01},// perform a single temperature calibration of the ranging sensor 
	{0x001b, 0x09},// *Set default ranging inter-measurement period to 100ms
	{0x003e, 0x31},// *Set default ALS inter-measurement period to 500ms
	{0x0014, 0x24},// *Configures interrupt on ‘New Sample Ready threshold event’
	{0x0016, 0x00} //*change fresh out of set status to 0
};

//fonctions privées
//pas de fonctions privées

//variables publiques
//pas de variables publiques

//fonctions publiques
int interfaceVL6180x_ecrit(uint16_t Registre, uint8_t Donnee)
{
uint8_t message[3];
	message[0] = (uint8_t)(Registre >> 8);
	message[1] = (uint8_t)(Registre & 0xFF);
	message[2] = Donnee;
	if (piloteI2C1_ecritDesOctets(message, 3) < 0)
	{
		printf("erreur: interfaceVL6180x_ecrit\n");
		return -1;
	}
	return 0;
}

int interfaceVL6180x_lit(uint16_t Registre, uint8_t *Donnee)
{
uint8_t Commande[2];
	Commande[0] = (uint8_t)(Registre >> 8);
	Commande[1] = (uint8_t)Registre;
	if (piloteI2C1_litDesOctets(Commande, 2, Donnee, 1) < 0)
	{
		printf("erreur: interfaceVL6180x_lit\n");
		return -1;
	}
	return 0;
}

int interfaceVL6180x_litUneDistance(float *Distance)
{
uint8_t valeur;
	if (interfaceVL6180x_ecrit(0x18, 0x01) < 0)
	{
		printf("erreur: interfaceVL6180x_litUneDistance 1\n");
		return -1;
	}
	if(interfaceVL6180x_lit(0x4F, &valeur) < 0)
	{
		printf("erreur: interfaceVL6180x_litUneDistance 2\n");
		return -1;
	}
	while((valeur & 0x7) != 4)
  {
    if (interfaceVL6180x_lit(0x4F, &valeur) < 0)
    {
    	printf("erreur: interfaceVL6180x_litUneDistance 3\n");
      return -1;
    }
  }
  if (interfaceVL6180x_lit(0x62, &valeur) < 0)
  {
		printf("erreur: interfaceVL6180x_litUneDistance 4\n");
    return -1;
	}
	if (interfaceVL6180x_ecrit(0x15, 0x07) < 0)
  {
  	printf("erreur: interfaceVL6180x_litUneDistance 5\n");
    return -1;
	}
	*Distance = (float)valeur /10.0;
	return 0;
}

int interfaceVL6810x_initialise(void)
{
uint8_t index;
uint8_t valeur;
	if (piloteI2C1_configureLAdresse(INTERFACEVL6180X_ADRESSE) < 0)
	{
		printf("erreur: interfaceVL6810x_initialise 1\n");
		return -1;
	}

  if (interfaceVL6180x_lit(0x16, &valeur) < 0)
  {
  	printf("erreur: interfaceVL6180x_initialise 2\n");
    return -1;
  }
	if (valeur != 1)
	{
		printf("message interfaceVL6180x: le VL6180x va être reconfiguré\n");
	}

	for (index = 0; index < INTERFACEVL6180X_NOMBRE; index++)
	{
		if (interfaceVL6180x_ecrit(interfaceVL6810x_message[index].adresse, 
				interfaceVL6810x_message[index].valeur) < 0)
		{
			printf("erreur: interfaceVL6180x_initialise 3 - index %d\n", index);
			return -1;
		}
	}
	return 0;
}



