//processusClignotant:
//Historique: 
// 2018-09-24, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteCAN1.h"
#include "serviceBaseDeTemps.h"
#include "interfaceT2.h"
#include "interfacePass.h"
#include "processusCom.h"

//Definitions privees
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
    
//Declarations de fonctions privees:
void processusClignotant_eteintUnPeu(void);
void processusClignotant_allumeUnPeu(void);

//Definitions de variables privees:
unsigned int processusClignotant_compteur;

//Definitions de fonctions privees:
void processusClignotant_eteintUnPeu(void)
{
  interfacePassUartToCAN();
  interfacePassCANtoUart();
}
/*****************************************************************************************/
void processusClignotant_allumeUnPeu(void)
{
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME)
  {
    return;
  }
  interfacePassCANtoUart();
  processusClignotant_compteur = 0;
  interfaceT2_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintUnPeu;  
}
/*****************************************************************************************/
void processusCom_initialise(void)
{
  processusClignotant_compteur = 0;
  interfaceT2_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintUnPeu;
}
