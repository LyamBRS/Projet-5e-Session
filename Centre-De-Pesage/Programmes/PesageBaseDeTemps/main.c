// Main 
// 

#include "main.h"

#include "piloteTimer.h"
#include "piloteI2C1.h"
#include "piloteCAN.h"

#include "interfaceBras.h"
#include "interfaceBalance.h"
#include "interfaceVL6180x.h"

#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"

#include "processusDetection.h"
#include "processusPesage.h"

// Variable Privé
char commande[64];

// Définition privé
void clearComCAN(void);
int main_initialise(void);


// Fonciton privé
int main_initialise(void)
{
    clearComCAN();
    piloteTimer_initialise();
    if(piloteCAN_initialise() < 0)  {printf("erreur: main_initialise CANNNN\n");return -1;}
    if (piloteI2C1_initialise() < 0)	    {printf("erreur: main_initialise piloteI2C1\n");return -1;}
    
    
    if (interfaceVL6810x_initialise() < 0)  {printf("erreur: main_initialise interfaceVL6180x\n");return -1;}
	interfaceBras_initialise();
	interfaceBalance_initialise();
    
    serviceBaseDeTemps_initialise();
    ServiceCommunication_initialise();
    
    processusDetection_initialise();
    processusPesage_initialise();
    piloteCAN_ouvreUneInterface();
    
    return 0;
}


int main(void)
{
    if(main_initialise() < 0)
    {
        printf("erreur: Lancement impossible\n");
		return -1;
    }
    piloteTimer_DemarreAvantWhile();
    
    while(1)
    {
        
    }
    piloteTimer_termine();
    return 0;
}



// Fonction de fermeture Can
void clearComCAN(void)
{
    system("sudo modprobe vcan");
	system("sudo ip link set vcan0 down");
	system("sudo ip link del dev vcan0");
	system("sudo modprobe can");
	system("sudo ip link set can0 down");
	system("sudo ip link del dev can0");
	system("sudo modprobe can");
	system("sudo ip link set can0 down");
	system("sudo ip link del dev can0");
}