//interfaceT4:
//Historique: 
// 2018-09-30, , creation

//INCLUSIONS
#include "main.h"
#include "piloteI2C.h"
#include "interfaceUsine.h"
#include "serviceBaseDeTemps.h"
#include "interfaceT3.h"
//Definitions privees
#define INTERFACEUSINE_INTERVAL_TRANSMISSION 20
#define DELAI_MAX_PONT_ACK 200 //100ms
#define DELAI_MAX_PONT_MOTION_COMPLETE 40000 //20sec

#define INTERFACEBV_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ/INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ)
#define INTERFACEBV_COMPTE_INITIAL (\
  INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

#define INTERFACEBR_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ/INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ)
#define INTERFACEBR_COMPTE_INITIAL (\
  INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
int i;

struct CartesI2C
{
  unsigned char PCF1;
  unsigned char PCF2;
  unsigned char PCF3;
  unsigned char PCF4;
  unsigned char PCF5;
};

struct elementUsine{
  unsigned int NoDePcf;
  unsigned int Position;
};

struct elementUsine elementsDuCentreDeTri[34];

union UnionCartesI2CUsine
{
  struct CartesI2C structCartesI2C;
  unsigned char tabCartesI2C[sizeof(structCartesI2C)];
} unionCartesI2CUsine;

unsigned char ucEtatPont;
unsigned char ucPostitonPont;
unsigned char ucRequetePont;
unsigned char etatTraitementRequetePont;

unsigned char compteurAvantLectureV;
unsigned char compteurAntiRebondV;
unsigned char compteurAvantLectureR;
unsigned char compteurAntiRebondR;
//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
INTERFACEBOUTON interfaceUsine_BV;
INTERFACEBOUTON interfaceUsine_BR;
//pas de variables publiques

//Definitions de fonctions publiques:

void interfaceUsine_gere (void)
{  
  static unsigned int compteurDeTransmission;
  if (compteurDeTransmission >= INTERFACEUSINE_INTERVAL_TRANSMISSION)
  {
    compteurDeTransmission = 0;
    piloteI2C_Transmit(INTERFACEUSINE_ADRESSE_PCF1_W, unionCartesI2CUsine.structCartesI2C.PCF1);
    piloteI2C_Transmit(INTERFACEUSINE_ADRESSE_PCF2_W, unionCartesI2CUsine.structCartesI2C.PCF2);
    piloteI2C_Receive(INTERFACEUSINE_ADRESSE_PCF3_R, &unionCartesI2CUsine.structCartesI2C.PCF3);
    piloteI2C_Receive(INTERFACEUSINE_ADRESSE_PCF4_R, &unionCartesI2CUsine.structCartesI2C.PCF4);
    piloteI2C_Receive(INTERFACEUSINE_ADRESSE_PCF5_R, &unionCartesI2CUsine.structCartesI2C.PCF5);
    if (INTERFACEUSINE_INVERSE_PCF3) unionCartesI2CUsine.structCartesI2C.PCF3 = ~unionCartesI2CUsine.structCartesI2C.PCF3;
    if (INTERFACEUSINE_INVERSE_PCF4) unionCartesI2CUsine.structCartesI2C.PCF4 = ~unionCartesI2CUsine.structCartesI2C.PCF4;
    if (INTERFACEUSINE_INVERSE_PCF5) unionCartesI2CUsine.structCartesI2C.PCF5 = ~unionCartesI2CUsine.structCartesI2C.PCF5;
  }

/*
  #pragma region INTERFACEUSINE_BOUTON_VERT
  //Gestion du bouton vert
  compteurAvantLectureV++;
  if (compteurAvantLectureV < INTERFACEBV_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  compteurAvantLectureV = 0;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_BOUTON_VERT) == INTERFACEB1_VALEUR_LUE_SI_APPUYE)
  {
    if (compteurAntiRebondV == INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    compteurAntiRebondV++;
    if (compteurAntiRebondV < INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceUsine_BV.etatDuBouton = INTERFACEUSINE_BV_APPUYE;
    interfaceUsine_BV.information = INFORMATION_DISPONIBLE;       
    return;
  }
  if (compteurAntiRebondV == 0)
  {
    return; 
  }
  compteurAntiRebondV--;
  if (compteurAntiRebondV > 0)
  {
    return;
  } 
  interfaceUsine_BV.etatDuBouton = INTERFACEUSINE_BV_RELACHE;
  interfaceUsine_BV.information = INFORMATION_DISPONIBLE;
  //Fin bouton vert
  #pragma endregion INTERFACEUSINE_BOUTON_VERT


  #pragma region INTERFACEUSINE_BOUTON_ROUGE
  //Gestion du bouton rouge
  compteurAvantLectureR++;
  if (compteurAvantLectureR < INTERFACEBV_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  compteurAvantLectureR = 0;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_BOUTON_VERT) == INTERFACEB1_VALEUR_LUE_SI_APPUYE)
  {
    if (compteurAntiRebondR == INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    compteurAntiRebondR++;
    if (compteurAntiRebondR < INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
    {
      return;
    }
    interfaceUsine_BR.etatDuBouton = INTERFACEUSINE_BV_APPUYE;
    interfaceUsine_BR.information = INFORMATION_DISPONIBLE;       
    return;
  }
  if (compteurAntiRebondR == 0)
  {
    return; 
  }
  compteurAntiRebondR--;
  if (compteurAntiRebondR > 0)
  {
    return;
  } 
  interfaceUsine_BR.etatDuBouton = INTERFACEUSINE_BV_RELACHE;
  interfaceUsine_BR.information = INFORMATION_DISPONIBLE;
  //Fin bouton rouge
  #pragma endregion INTERFACEUSINE_BOUTON_ROUGE
*/
  compteurDeTransmission++;
}


bool interfaceUsine_LitUnElement (unsigned char elementID)
{
return ((unionCartesI2CUsine.tabCartesI2C[elementsDuCentreDeTri[elementID].NoDePcf-1]) & (0x01 << elementsDuCentreDeTri[elementID].Position))? 1 : 0;
}

void interfaceUsine_EcritUnElement (unsigned char elementID, bool etatAEcrire)
{
  if (etatAEcrire) 
  {
    unionCartesI2CUsine.tabCartesI2C[elementsDuCentreDeTri[elementID].NoDePcf-1] |= (0x01 << elementsDuCentreDeTri[elementID].Position);
    return;
  }
  unionCartesI2CUsine.tabCartesI2C[elementsDuCentreDeTri[elementID].NoDePcf-1] &= ~(0x01 << elementsDuCentreDeTri[elementID].Position);
  
}

void interfaceUsine_Reset (void)
{
  unionCartesI2CUsine.structCartesI2C.PCF1 = 0xFF;
  unionCartesI2CUsine.structCartesI2C.PCF2 = 0xFF;
}

void interfaceUsine_Initialise (void)
{
  interfaceT3_allume();
  elementsDuCentreDeTri[INTERFACEUSINE_ID_LED].NoDePcf = INTERFACEUSINE_PCF_LED;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_LED].Position = INTERFACEUSINE_POS_LED;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_VENTOUSE_DESCEND].NoDePcf = INTERFACEUSINE_PCF_VENTOUSE_DESCEND;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_VENTOUSE_DESCEND].Position = INTERFACEUSINE_POS_VENTOUSE_DESCEND;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_VENTOUSE_MONTE].NoDePcf = INTERFACEUSINE_PCF_VENTOUSE_MONTE;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_VENTOUSE_MONTE].Position = INTERFACEUSINE_POS_VENTOUSE_MONTE;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_AIR_TRIG].NoDePcf = INTERFACEUSINE_PCF_AIR_TRIG;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_AIR_TRIG].Position = INTERFACEUSINE_POS_AIR_TRIG;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_ELEVATEUR_DESCEND].NoDePcf = INTERFACEUSINE_PCF_ELEVATEUR_DESCEND;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_ELEVATEUR_DESCEND].Position = INTERFACEUSINE_POS_ELEVATEUR_DESCEND;
  
  elementsDuCentreDeTri[INTERFACEUSINE_ID_ELEVATEUR_MONTE].NoDePcf = INTERFACEUSINE_PCF_ELEVATEUR_MONTE;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_ELEVATEUR_MONTE].Position = INTERFACEUSINE_POS_ELEVATEUR_MONTE;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_EJECTEUR_IN].NoDePcf = INTERFACEUSINE_PCF_EJECTEUR_IN;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_EJECTEUR_IN].Position = INTERFACEUSINE_POS_EJECTEUR_IN;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_EJECTEUR_OUT].NoDePcf = INTERFACEUSINE_PCF_EJECTEUR_OUT;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_EJECTEUR_OUT].Position = INTERFACEUSINE_POS_EJECTEUR_OUT;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_POUSSOIR].NoDePcf = INTERFACEUSINE_PCF_POUSSOIR;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_POUSSOIR].Position = INTERFACEUSINE_POS_POUSSOIR;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_CONVOYEUR].NoDePcf = INTERFACEUSINE_PCF_CONVOYEUR;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_CONVOYEUR].Position = INTERFACEUSINE_POS_CONVOYEUR;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_POS0].NoDePcf = INTERFACEUSINE_PCF_PONT_POS0;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_POS0].Position = INTERFACEUSINE_POS_PONT_POS0;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_POS1].NoDePcf = INTERFACEUSINE_PCF_PONT_POS1;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_POS1].Position = INTERFACEUSINE_POS_PONT_POS1;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_POS2].NoDePcf = INTERFACEUSINE_PCF_PONT_POS2;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_POS2].Position = INTERFACEUSINE_POS_PONT_POS2;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_CONTROLLER].NoDePcf = INTERFACEUSINE_PCF_PONT_CONTROLLER;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_CONTROLLER].Position = INTERFACEUSINE_POS_PONT_CONTROLLER;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_START].NoDePcf = INTERFACEUSINE_PCF_PONT_START;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_START].Position = INTERFACEUSINE_POS_PONT_START;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_VENTOUSE_HAUT].NoDePcf = INTERFACEUSINE_PCF_SENSOR_VENTOUSE_HAUT;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_VENTOUSE_HAUT].Position = INTERFACEUSINE_POS_SENSOR_VENTOUSE_HAUT;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_VENTOUSE_BAS].NoDePcf = INTERFACEUSINE_PCF_SENSOR_VENTOUSE_BAS;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_VENTOUSE_BAS].Position = INTERFACEUSINE_POS_SENSOR_VENTOUSE_BAS;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_MAG].NoDePcf = INTERFACEUSINE_PCF_SENSOR_MAG;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_MAG].Position = INTERFACEUSINE_POS_SENSOR_MAG;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_CAP].NoDePcf = INTERFACEUSINE_PCF_SENSOR_CAP;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_CAP].Position = INTERFACEUSINE_POS_SENSOR_CAP;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_EJECTEUR_IN].NoDePcf = INTERFACEUSINE_PCF_SENSOR_EJECTEUR_IN;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_EJECTEUR_IN].Position = INTERFACEUSINE_POS_SENSOR_EJECTEUR_IN;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_EJECTEUR_OUT].NoDePcf = INTERFACEUSINE_PCF_SENSOR_EJECTEUR_OUT;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_EJECTEUR_OUT].Position = INTERFACEUSINE_POS_SENSOR_EJECTEUR_OUT;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_ELEVATEUR_BAS].NoDePcf = INTERFACEUSINE_PCF_SENSOR_ELEVATEUR_BAS;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_ELEVATEUR_BAS].Position = INTERFACEUSINE_POS_SENSOR_ELEVATEUR_BAS;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_ELEVATEUR_HAUT].NoDePcf = INTERFACEUSINE_PCF_SENSOR_ELEVATEUR_HAUT;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_ELEVATEUR_HAUT].Position = INTERFACEUSINE_POS_SENSOR_ELEVATEUR_HAUT;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_POUSSOIR_IN].NoDePcf = INTERFACEUSINE_PCF_SENSOR_POUSSOIR_IN;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_POUSSOIR_IN].Position = INTERFACEUSINE_POS_SENSOR_POUSSOIR_IN;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_POUSSOIR_OUT].NoDePcf = INTERFACEUSINE_PCF_SENSOR_POUSSOIR_OUT;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_POUSSOIR_OUT].Position = INTERFACEUSINE_POS_SENSOR_POUSSOIR_OUT;
  
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC].NoDePcf = INTERFACEUSINE_PCF_SENSOR_OPTIQUE_BLOC;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC].Position = INTERFACEUSINE_POS_SENSOR_OPTIQUE_BLOC;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_OPTIQUE_CHUTE].NoDePcf = INTERFACEUSINE_PCF_SENSOR_OPTIQUE_CHUTE;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_OPTIQUE_CHUTE].Position = INTERFACEUSINE_POS_SENSOR_OPTIQUE_CHUTE;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_BOUTON_VERT].NoDePcf = INTERFACEUSINE_PCF_BOUTON_VERT;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_BOUTON_VERT].Position = INTERFACEUSINE_POS_BOUTON_VERT;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_BOUTON_ROUGE].NoDePcf = INTERFACEUSINE_PCF_BOUTON_ROUGE;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_BOUTON_ROUGE].Position = INTERFACEUSINE_POS_BOUTON_ROUGE;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_PRESSION].NoDePcf = INTERFACEUSINE_PCF_SENSOR_PRESSION;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_SENSOR_PRESSION].Position = INTERFACEUSINE_POS_SENSOR_PRESSION;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_READY_FOR_OPERATION].NoDePcf = INTERFACEUSINE_PCF_PONT_READY_FOR_OPERATION;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_READY_FOR_OPERATION].Position = INTERFACEUSINE_POS_PONT_READY_FOR_OPERATION;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_DEFAULT_MOTION_COMPLETE].NoDePcf = INTERFACEUSINE_PCF_PONT_DEFAULT_MOTION_COMPLETE;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_DEFAULT_MOTION_COMPLETE].Position = INTERFACEUSINE_POS_PONT_DEFAULT_MOTION_COMPLETE;

  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_DEFAULT_ACK_START].NoDePcf = INTERFACEUSINE_PCF_PONT_DEFAULT_ACK_START;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_DEFAULT_ACK_START].Position = INTERFACEUSINE_POS_PONT_DEFAULT_ACK_START;
  
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_DEFAULT_ERROR].NoDePcf = INTERFACEUSINE_PCF_PONT_DEFAULT_ERROR;
  elementsDuCentreDeTri[INTERFACEUSINE_ID_PONT_DEFAULT_ERROR].Position = INTERFACEUSINE_POS_PONT_DEFAULT_ERROR;
  
  unionCartesI2CUsine.structCartesI2C.PCF1 = 0xFF;
  unionCartesI2CUsine.structCartesI2C.PCF2 = 0xFF;

  
  serviceBaseDeTemps_execute[INTERFACEUSINE_GERE] = interfaceUsine_gere;
}



