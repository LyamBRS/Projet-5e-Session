// Main

#include "piloteTimer.h"
#include "piloteI2C1.h"
#include <errno.h>
#include "main.h"
#include "interfaceBras.h"
#include "interfaceVL6180x.h"
#include "serviceBaseDeTemps.h"
#include "processusDetection.h"

int main_initialise(void)
{
    if (piloteI2C1_initialise() < 0)
	{
		printf("erreur: main_initialise piloteI2C1\n");
		return -1;
	}
    if (interfaceVL6810x_initialise() < 0)
	{
		printf("erreur: main_initialise interfaceVL6180x\n");
		return -1;
	}
    piloteTimer_initialise();
    serviceBaseDeTemps_initialise();
    processusDetection_initialise();
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