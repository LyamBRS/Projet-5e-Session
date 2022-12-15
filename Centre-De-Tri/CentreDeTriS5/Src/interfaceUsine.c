/**
 * @file interfaceUsine.c
 * @author Renaud Gagnon
 * @brief Fichier qui contient le code permettant de gérer toute l'usine incluant le pont.
 * @warning Tout le code de ce fichier a été écrit par Renaud Gagnon. Incluant le code relatif au pont du centre de tri.
 * @version 0.1
 * @date 2022-12-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// INCLUSIONS
#include "main.h"
#include "piloteI2C.h"
#include "interfaceUsine.h"
#include "serviceBaseDeTemps.h"
#include "interfaceT3.h"
#include "interfaceT1.h"
#include "interfaceT2.h"
// Definitions privees
/**
 * @brief Définit le délai entre chaque communication avec les cartes I2C en 1/2ms
 * 
 */
#define INTERFACEUSINE_INTERVAL_TRANSMISSION 20

/**
 * @brief Définit le délai maximal après lequel les fonctions du pont tombent en erreur si elles n'ont pas reçu de ack de sa part
 * 
 */
#define DELAI_MAX_PONT_ACK 200               // 100ms

/**
 * @brief Définit le délai maximal après lequel les fonctions du pont tombent en erreur si elles n'ont pas reçu de ack de sa part
 * 
 */
#define DELAI_MAX_PONT_MOTION_COMPLETE 40000 // 20sec

#define INTERFACEBV_COMPTE_MAXIMUM_AVANT_LECTURE ( \
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ / INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ)
#define INTERFACEBV_COMPTE_INITIAL ( \
    INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION / 2)

#define INTERFACEBR_COMPTE_MAXIMUM_AVANT_LECTURE ( \
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ / INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ)
#define INTERFACEBR_COMPTE_INITIAL ( \
    INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION / 2)
// pas de definitions privees

// Declarations de fonctions privees:
/**
 * @brief Fonction qui gere l'anti rebond et la detection de front du bouton vert du centre de tri.
 * 
 */
void gereLeBoutonVert(void);

/**
 * @brief Fonction qui gere l'anti rebond et la detection de front du bouton rouge du centre de tri.
 * 
 */
void gereLeBoutonRouge(void);

/**
 * @brief Fonction qui gere le timing du pont
 * @author Renaud Gagnon
 * @warning Négligence de la part de Karl
 */
void gereLePont(void);
// pas de fonction privees

// Definitions de variables privees:
int i;

/**
 * @brief Structure qui sert de variable temporaire pour la mise à jour des valeurs des cartes I2C
 * 
 */
struct CartesI2C
{
  unsigned char PCF1;
  unsigned char PCF2;
  unsigned char PCF3;
  unsigned char PCF4;
  unsigned char PCF5;
};


/**
 * @brief Structure qui représente un I/O de l'usine (ex: la lumière verte)
 * 
 */
struct elementUsine
{
  unsigned int NoDePcf;
  unsigned int Position;
};

/**
 * @brief Ceci est un tableau de structure de type \ref elementUsine. Il y a une case de tableau pour chaque élément de l'usine. 
 * On pourra donc utiliser une seule valeur (l'ID de l'élément, qui est équivalent à la position dans ce tableau) 
 * pour aller chercher le # de PCF de cet élément et le bit correspondant à l'élément sur ce pcf.
 * 
 */
struct elementUsine elementsDuCentreDeTri[34];

/**
 * @brief Union permettant d'adresser de plusieurs façons les variables correspondantes aux ports des cartes I2C
 * 
 */
union UnionCartesI2CUsine
{
  struct CartesI2C structCartesI2C;
  unsigned char tabCartesI2C[sizeof(structCartesI2C)];
} unionCartesI2CUsine;

/**
 * @brief Variable temporaire de la valeur lue par l'ADC
 * 
 */
uint8_t valeurDuADC;

unsigned char ucEtatPont;
unsigned char ucPostitonPont;
unsigned char ucRequetePont;
unsigned char etatTraitementRequetePont;

// Definitions de fonctions privees:
// pas de fonctions privees

// Definitions de variables publiques:
INTERFACEBOUTON interfaceUsine_BV;
INTERFACEBOUTON interfaceUsine_BR;
// pas de variables publiques

// Definitions de fonctions publiques:

/**
 * @brief Fonction de gestion de lusine qui est appelée par la base de temps. 
 * Elle met a jour la valeur des variables temporaires en fonction de l'état des I/O des cartes I2C et inversement.
 * Elle appele les fonctions de gestion de boutons de l'usine et la fonction de gestion du pont.
 * 
 */
void interfaceUsine_gere(void)
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
    piloteI2C_Receive(INTERFACEUSINE_ADRESSE_ADC, &valeurDuADC);
    if (INTERFACEUSINE_INVERSE_PCF3)
      unionCartesI2CUsine.structCartesI2C.PCF3 = ~unionCartesI2CUsine.structCartesI2C.PCF3;
    if (INTERFACEUSINE_INVERSE_PCF4)
      unionCartesI2CUsine.structCartesI2C.PCF4 = ~unionCartesI2CUsine.structCartesI2C.PCF4;
    if (INTERFACEUSINE_INVERSE_PCF5)
      unionCartesI2CUsine.structCartesI2C.PCF5 = ~unionCartesI2CUsine.structCartesI2C.PCF5;
  }

  gereLePont();
  gereLeBoutonRouge();
  gereLeBoutonVert();
  compteurDeTransmission++;
}

void gereLeBoutonVert(void)
{
  static unsigned char compteurAvantLectureV;
  static unsigned char compteurAntiRebondV;
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
}

void gereLeBoutonRouge(void)
{
  static unsigned char compteurAvantLectureR;
  static unsigned char compteurAntiRebondR;
  compteurAvantLectureR++;
  if (compteurAvantLectureR < INTERFACEBV_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  compteurAvantLectureR = 0;
  if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_BOUTON_ROUGE) == INTERFACEUSINE_BOUTON_APPUYE)
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
    interfaceUsine_BR.etatDuBouton = INTERFACEUSINE_BR_APPUYE;
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
  interfaceUsine_BR.etatDuBouton = INTERFACEUSINE_BR_RELACHE;
  interfaceUsine_BR.information = INFORMATION_DISPONIBLE;
}

void gereLePont(void)
{
  static unsigned int compteurDelaiPont;

  static bool flagDelaiPont;

  if (etatTraitementRequetePont == 2 && compteurDelaiPont >= 20)
  {
    if (ucRequetePont != INTERFACEUSINE_PONT_POSITIONH) interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START, INTERFACEUSINE_OUTPUT_HIGH);
    if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_ACK_START) == INTERFACEUSINE_SENSOR_HIGH && compteurDelaiPont >= 80)
    {
      //interfaceT1_allume();
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_START, INTERFACEUSINE_OUTPUT_LOW);
      if (interfaceUsine_LitUnElement(INTERFACEUSINE_ID_PONT_DEFAULT_MOTION_COMPLETE) == INTERFACEUSINE_SENSOR_HIGH && compteurDelaiPont >= 100)
      {
        //interfaceT2_allume();
        interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0, INTERFACEUSINE_OUTPUT_LOW);
        interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1, INTERFACEUSINE_OUTPUT_LOW);
        interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2, INTERFACEUSINE_OUTPUT_LOW);
        ucPostitonPont = ucRequetePont;
        ucRequetePont = INTERFACEUSINE_PONT_REQUETE_TRAITEE;
        ucEtatPont = INTERFACEUSINE_PONT_ETAT_FINI;
        flagDelaiPont = 0;
        compteurDelaiPont = 0;
        
        etatTraitementRequetePont = 0;
      }
    }
  }

  if (etatTraitementRequetePont == 1)
  {
    switch (ucRequetePont)
    {
    case INTERFACEUSINE_PONT_POSITIONH:
      flagDelaiPont = 1;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_CONTROLLER, INTERFACEUSINE_OUTPUT_HIGH);
      etatTraitementRequetePont = 2;
      break;
    case INTERFACEUSINE_PONT_POSITION0:
      flagDelaiPont = 1;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0, INTERFACEUSINE_OUTPUT_HIGH);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2, INTERFACEUSINE_OUTPUT_LOW);
      etatTraitementRequetePont = 2;
      break;
    case INTERFACEUSINE_PONT_POSITION1:
      flagDelaiPont = 1;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1, INTERFACEUSINE_OUTPUT_HIGH);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2, INTERFACEUSINE_OUTPUT_LOW);
      etatTraitementRequetePont = 2;

      break;
    case INTERFACEUSINE_PONT_POSITION2:
      flagDelaiPont = 1;
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS0, INTERFACEUSINE_OUTPUT_HIGH);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS1, INTERFACEUSINE_OUTPUT_LOW);
      interfaceUsine_EcritUnElement(INTERFACEUSINE_ID_PONT_POS2, INTERFACEUSINE_OUTPUT_HIGH);
      etatTraitementRequetePont = 2;
      break;
    }
  }

  //if (compteurDelaiPont > DELAI_MAX_PONT_ACK && ackRecieved) // ERREUR DELAI ACK D�PASS�!!!
  //if (compteurDelaiPont > DELAI_MAX_PONT_MOTION_COMPLETE)  // ERREUR DELAI MOUVEMENT D�PASS�!!!
      if (flagDelaiPont)
        compteurDelaiPont++;
      else
        compteurDelaiPont = 0;
}

bool interfaceUsine_RequetePont(unsigned char ucPositiondemandee)
{
  //if (ucRequetePont != INTERFACEUSINE_PONT_REQUETE_TRAITEE)return 0;
  interfaceT1_eteint();
  interfaceT2_eteint();
  ucRequetePont = ucPositiondemandee;
  ucEtatPont = INTERFACEUSINE_PONT_ETAT_EN_COURS;
  ucPostitonPont = INTERFACEUSINE_PONT_POSITION_DEPLACEMENT;
  etatTraitementRequetePont = 1;
  return 1;
}

unsigned char interfaceUsine_PositionPont(void)
{
  return ucPostitonPont;
}

unsigned char interfaceUsine_EtatPont(void)
{
  return ucEtatPont;
}

bool interfaceUsine_LitUnElement(unsigned char elementID)
{
  return ((unionCartesI2CUsine.tabCartesI2C[elementsDuCentreDeTri[elementID].NoDePcf - 1]) & (0x01 << elementsDuCentreDeTri[elementID].Position)) ? 1 : 0;
}

unsigned char interfaceUsine_LitADC (void)
{  
  return valeurDuADC;
}

void interfaceUsine_EcritUnElement(unsigned char elementID, bool etatAEcrire)
{
  if (etatAEcrire)
  {
    unionCartesI2CUsine.tabCartesI2C[elementsDuCentreDeTri[elementID].NoDePcf - 1] |= (0x01 << elementsDuCentreDeTri[elementID].Position);
    return;
  }
  unionCartesI2CUsine.tabCartesI2C[elementsDuCentreDeTri[elementID].NoDePcf - 1] &= ~(0x01 << elementsDuCentreDeTri[elementID].Position);
}

void interfaceUsine_Reset(void)
{
  unionCartesI2CUsine.structCartesI2C.PCF1 = 0xFF;
  unionCartesI2CUsine.structCartesI2C.PCF2 = 0xFF;
}

void interfaceUsine_Initialise(void)
{
  //interfaceT3_allume();
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
