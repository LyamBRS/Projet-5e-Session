//serviceProtocole637:
//Historique: 
// 2018-10-28, Yves Roy, creation

//INCLUSIONS
#include "xmain.h"
#include "xpiloteUART2.h"
#include "piloteUDPStation.h"
#include "xserviceBaseDeTemps.h"
#include "serviceProtocole637.h"

//Definitions privees
#define SERVICEPROTOCOLE637_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_TRANSMISSION (\
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
    /SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ )
#define SERVICEPROTOCOLE637_TRANSMISSION_PERMISE 1
#define SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE 0
#define SERVICEPROTOCOLE637_RECEPTION_PERMISE 1
#define SERVICEPROTOCOLE637_RECEPTION_RETARDEE 0
#define SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE 0
#define SERVICEPROTOCOLE637_LECTURE_DISPONIBLE 1
#define SERVICEPROTOCOLE637_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS (\
    SERVICEPROTOCOLE637_TEMPS_D_ATTENTE_MAXIMAL_EN_MS \
    * SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ / 1000.0)
#define SERVICEPROTOCOLE637_TEMPS_DEPASSE 1
#define SERVICEPROTOCOLE637_TEMPS_PAS_DEPASSE 0
#define SERVICEPROTOCOLE637_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION (\
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
    /SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ)
//Declarations de fonctions privees:
void serviceProtocole637_attendUneRequete(void);
void serviceProtocole637_transmetLaLongueur(void);
void serviceProtocole637_transmetUneDonnee(void);
void serviceProtocole637_transmetUnZero(void);
void serviceProtocole637_transmetUnChecksum(void);
unsigned char serviceProtocole637_gereLaSynchronisationDesTransmissions(void);
void serviceProtocole637_attendUnDebut(void);
void serviceProtocole637_attendLaLongueur(void);
void serviceProtocole637_attendUneDonnee(void);
void serviceProtocole637_attendUnZero(void);
void serviceProtocole637_attendUnChecksum(void);
unsigned char serviceProtocole637_gereLaSynchronisationDesReceptions(void);
unsigned char serviceProtocole637_gereLeTempsDAttente(void);
unsigned char serviceProtocole637_gereUneReception(void);

//Definitions de variables privees:
unsigned char serviceProtocole637_compteurDeSynchronisationDesTransmissions;
unsigned char serviceProtocole637_compteurDeSynchronisationDesReceptions;
unsigned char serviceProtocole637_compteurDeTransmissions;
unsigned char serviceProtocole637_compteurDeReceptions;
unsigned char serviceProtocole637_compteurDeTempsDAttente;
unsigned char serviceProtocole637_reception;
unsigned char serviceProtocole637_checksum;
unsigned char serviceProtocole637_checksumDeReception;
unsigned char serviceProtocole637_checksumDeTransmission;
unsigned char ucChecksum = 0x00;

//Definitions de fonctions privees:

// machine a etats serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION]

void serviceProtocole637_attendUneRequete(void)
{
  if (serviceProtocole637_gereLaSynchronisationDesTransmissions()
      == SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
  {
    return;
  }
  if (serviceProtocole637.requete == REQUETE_TRAITEE)
  {
    return;
  }
  piloteUART2_TX(SERVICEPROTOCOLE637_DEBUT_DE_TRAME);
  serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
      serviceProtocole637_transmetLaLongueur;
    return;
}

void serviceProtocole637_transmetLaLongueur(void)
{
  if (serviceProtocole637_gereLaSynchronisationDesTransmissions()
      == SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
  {
    return;
  }
  piloteUART2_TX(serviceProtocole637.nombreATransmettre);
  serviceProtocole637_compteurDeTransmissions = 0;
  serviceProtocole637_checksumDeTransmission = 0;
  ucChecksum = 0x00;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
      serviceProtocole637_transmetUneDonnee;
}

void serviceProtocole637_transmetUneDonnee(void)
{
  static unsigned char donnee = 0;
  if (serviceProtocole637_gereLaSynchronisationDesTransmissions() == SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
  {
    return;
  }
 if(donnee == 0)
  {
    piloteUART2_TX(readBuffer[0]);
    ucChecksum += readBuffer[0];
    donnee = 1;
    return;
  }
  else if(donnee == 1)
  {
    piloteUART2_TX(readBuffer[1]);
    ucChecksum += readBuffer[1];
    donnee = 2;
    return;
  }
  else if(donnee == 2)
  {
    piloteUART2_TX(readBuffer[2]);
    ucChecksum += readBuffer[2];
    donnee = 3;
    return;
  }
  else if(donnee == 3)
  {
    piloteUART2_TX(readBuffer[3]);
    ucChecksum += readBuffer[3];
    donnee = 4;
    return;
  }
  else if(donnee == 4)
  {
    piloteUART2_TX(readBuffer[4]);
    ucChecksum += readBuffer[4];
    donnee = 5;
    return;
  }
   else if(donnee == 5)
 {
   piloteUART2_TX(readBuffer[5]);
   ucChecksum += readBuffer[5];
   donnee = 6;
   return;
 }
  else if(donnee == 6)
 {
   piloteUART2_TX(readBuffer[6]);
   ucChecksum += readBuffer[6];
   donnee = 7;
   return;
 }
  else if(donnee == 7)
 {
   piloteUART2_TX(readBuffer[7]);
   ucChecksum += readBuffer[7];
   donnee = 0;
 }

 for(int i=0; i<8; ++i)
 {
  readBuffer[i] = 0;
 }
 serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] = serviceProtocole637_transmetUnChecksum;
}

void serviceProtocole637_transmetUnChecksum(void)
{
  if (serviceProtocole637_gereLaSynchronisationDesTransmissions()== SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
  {
    return;
  }
  piloteUART2_TX(ucChecksum);
  serviceProtocole637.requete = REQUETE_TRAITEE;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
serviceProtocole637_attendUneRequete;
// insérez votre code ici    
}

unsigned char serviceProtocole637_gereLaSynchronisationDesTransmissions(void)
{
  serviceProtocole637_compteurDeSynchronisationDesTransmissions++;
  if (serviceProtocole637_compteurDeSynchronisationDesTransmissions <
      SERVICEPROTOCOLE637_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_TRANSMISSION)
  {
    return SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE;
  }
  serviceProtocole637_compteurDeSynchronisationDesTransmissions = 0;
  return SERVICEPROTOCOLE637_TRANSMISSION_PERMISE;
}

// machine a etats serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION]

void serviceProtocole637_attendUnDebut(void)
{
  piloteUART2_TX('A');
  if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
  {
    return;
  }
  piloteUART2_TX('B');
  if (serviceProtocole637_reception != SERVICEPROTOCOLE637_DEBUT_DE_TRAME)
  {
    serviceProtocole637_compteurDeTempsDAttente = 0;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendLaLongueur;
    return;
  }
  piloteUART2_TX('C');
  serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_EN_ATTENTE;
  serviceProtocole637.information = INFORMATION_DISPONIBLE;
}

void serviceProtocole637_attendLaLongueur(void)
{
  piloteUART2_TX('D');
  if (serviceProtocole637_gereLaSynchronisationDesReceptions()
      == SERVICEPROTOCOLE637_RECEPTION_RETARDEE)
  {
    return;
  }
  piloteUART2_TX('E');
  if (serviceProtocole637_gereLeTempsDAttente() == SERVICEPROTOCOLE637_TEMPS_DEPASSE)
  {
    serviceProtocole637.statut = SERVICEPROTOCOLE637_TEMPS_DEPASSE;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;
  }
  piloteUART2_TX('F');
  if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
  {
    return;
  }
  piloteUART2_TX('I');
  serviceProtocole637_compteurDeTempsDAttente = 0;
  serviceProtocole637_reception = piloteUART2_RX();
  piloteUART2_TX(serviceProtocole637_reception);
  if (serviceProtocole637_reception == 0x00)
  {
    serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_LONGUEUR_NULLE;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;
  }
  piloteUART2_TX('J');
  if (serviceProtocole637_reception > SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM)
  {
    serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_LONGUEUR_TROP_GRANDE;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;
  }
  piloteUART2_TX('L');
  serviceProtocole637.nombreARecevoir = serviceProtocole637_reception;
  serviceProtocole637_compteurDeReceptions = 0;
  serviceProtocole637_checksum = 0;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
      serviceProtocole637_attendUneDonnee;
}

void serviceProtocole637_attendUneDonnee(void)
{piloteUART2_TX('N');
  if (serviceProtocole637_gereLaSynchronisationDesReceptions()
      == SERVICEPROTOCOLE637_RECEPTION_RETARDEE)
  {
    return;
  }
  if (serviceProtocole637_gereLeTempsDAttente()
      == SERVICEPROTOCOLE637_TEMPS_DEPASSE)
  {
    serviceProtocole637.statut = SERVICEPROTOCOLE637_TEMPS_DEPASSE;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;
    return;
  }
  if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
  {
    return;
  }
  serviceProtocole637_reception = piloteUART2_RX();
  piloteUART2_TX(serviceProtocole637_reception);
  serviceProtocole637_compteurDeTempsDAttente = 0;
  serviceProtocole637.octetsRecus[serviceProtocole637_compteurDeReceptions]
      = serviceProtocole637_reception;
  serviceProtocole637_compteurDeReceptions++;
    if (serviceProtocole637_compteurDeReceptions == serviceProtocole637.nombreARecevoir)
  {
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
         serviceProtocole637_attendUnChecksum;      
    return;
  }
}

void serviceProtocole637_attendUnChecksum(void)
{
 if (serviceProtocole637_gereLaSynchronisationDesReceptions()
      == SERVICEPROTOCOLE637_RECEPTION_RETARDEE)
  {
    return;
  }
  if (serviceProtocole637_gereLeTempsDAttente()
      == SERVICEPROTOCOLE637_TEMPS_DEPASSE)
  {
    serviceProtocole637.statut = SERVICEPROTOCOLE637_TEMPS_DEPASSE;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;
    return;
  }
  if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
  {
      return;
  }
  serviceProtocole637_compteurDeTempsDAttente = 0;
 serviceProtocole637_reception = piloteUART2_RX();
 piloteUART2_TX(serviceProtocole637_reception);
  if (serviceProtocole637_reception == serviceProtocole637_checksumDeReception)
  {
    serviceProtocole637.statut = SERVICEPROTOCOLE637_PAS_D_ERREURS;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;      
    return;
  }
  serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_MAUVAIS_CHECKSUM;
  serviceProtocole637.information = INFORMATION_DISPONIBLE;
   serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;      
}

unsigned char serviceProtocole637_gereLaSynchronisationDesReceptions(void)
{
  serviceProtocole637_compteurDeSynchronisationDesReceptions++;
  if (serviceProtocole637_compteurDeSynchronisationDesReceptions <
      SERVICEPROTOCOLE637_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION)
  {
    return SERVICEPROTOCOLE637_RECEPTION_RETARDEE;
  }
  serviceProtocole637_compteurDeSynchronisationDesReceptions = 0;
  return SERVICEPROTOCOLE637_RECEPTION_PERMISE;
}

unsigned char serviceProtocole637_gereLeTempsDAttente(void)
{
  serviceProtocole637_compteurDeTempsDAttente++;
  if (serviceProtocole637_compteurDeTempsDAttente <
      SERVICEPROTOCOLE637_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS)
  {
    return SERVICEPROTOCOLE637_TEMPS_PAS_DEPASSE; 
  }
  return SERVICEPROTOCOLE637_TEMPS_DEPASSE;
}

unsigned char serviceProtocole637_gereUneReception(void)
{
  if (Serial2.available())
  {
  return SERVICEPROTOCOLE637_LECTURE_DISPONIBLE;
  }
  return SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE;
}

//Definitions de variables publiques:
SERVICEPROTOCOLE637 serviceProtocole637;

//Definitions de fonctions publiques:
void serviceProtocole637_initialise(void)
{
  serviceProtocole637.etatDuModuleDeReception = MODULE_PAS_EN_FONCTION;
  serviceProtocole637.information = INFORMATION_TRAITEE;
  serviceProtocole637_compteurDeSynchronisationDesTransmissions = 0;
  serviceProtocole637.requete = REQUETE_TRAITEE;
  serviceProtocole637_compteurDeSynchronisationDesReceptions = 0;
  serviceProtocole637.information = INFORMATION_TRAITEE;
  serviceProtocole637.statut = SERVICEPROTOCOLE637_PAS_D_ERREURS;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
      serviceProtocole637_attendUneRequete;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
      serviceProtocole637_attendUnDebut;
}
