/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//PROGRAMME: 247-637 S-0009
//DESCRIPTION: programme qui va de pair avec S-0008
//HISTORIQUE:
// 2019-10-27, Yves Roy: creation
#include "stm32f4xx_hal.h"


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define TRIAC_OUT_Pin GPIO_PIN_6
#define TRIAC_OUT_GPIO_Port GPIOE
#define TRIAC_IN_Pin GPIO_PIN_13
#define TRIAC_IN_GPIO_Port GPIOC
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define PDM_OUT_Pin GPIO_PIN_3
#define PDM_OUT_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define CLN_R_Pin GPIO_PIN_1
#define CLN_R_GPIO_Port GPIOA
#define I2S3_WS_Pin GPIO_PIN_4
#define I2S3_WS_GPIO_Port GPIOA
#define STEP3_Pin GPIO_PIN_5
#define STEP3_GPIO_Port GPIOA
#define STEP1_Pin GPIO_PIN_6
#define STEP1_GPIO_Port GPIOA
#define STEP2_Pin GPIO_PIN_7
#define STEP2_GPIO_Port GPIOA
#define RD_Pin GPIO_PIN_0
#define RD_GPIO_Port GPIOB
#define A4_Pin GPIO_PIN_1
#define A4_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define D0_Pin GPIO_PIN_8
#define D0_GPIO_Port GPIOE
#define D1_Pin GPIO_PIN_9
#define D1_GPIO_Port GPIOE
#define D2_Pin GPIO_PIN_10
#define D2_GPIO_Port GPIOE
#define D3_Pin GPIO_PIN_11
#define D3_GPIO_Port GPIOE
#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOE
#define D5_Pin GPIO_PIN_13
#define D5_GPIO_Port GPIOE
#define D6_Pin GPIO_PIN_14
#define D6_GPIO_Port GPIOE
#define D7_Pin GPIO_PIN_15
#define D7_GPIO_Port GPIOE
#define CLK_IN_Pin GPIO_PIN_10
#define CLK_IN_GPIO_Port GPIOB
#define CS0_Pin GPIO_PIN_11
#define CS0_GPIO_Port GPIOB
#define CS1_Pin GPIO_PIN_12
#define CS1_GPIO_Port GPIOB
#define CS2_Pin GPIO_PIN_13
#define CS2_GPIO_Port GPIOB
#define CS3_Pin GPIO_PIN_14
#define CS3_GPIO_Port GPIOB
#define A0_Pin GPIO_PIN_8
#define A0_GPIO_Port GPIOD
#define A1_Pin GPIO_PIN_9
#define A1_GPIO_Port GPIOD
#define A2_Pin GPIO_PIN_10
#define A2_GPIO_Port GPIOD
#define A3_Pin GPIO_PIN_11
#define A3_GPIO_Port GPIOD
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD
#define I2S3_MCK_Pin GPIO_PIN_7
#define I2S3_MCK_GPIO_Port GPIOC
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define I2S3_SCK_Pin GPIO_PIN_10
#define I2S3_SCK_GPIO_Port GPIOC
#define SW_ASC_Pin GPIO_PIN_11
#define SW_ASC_GPIO_Port GPIOC
#define I2S3_SD_Pin GPIO_PIN_12
#define I2S3_SD_GPIO_Port GPIOC
#define Audio_RST_Pin GPIO_PIN_4
#define Audio_RST_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define HORN_Pin GPIO_PIN_6
#define HORN_GPIO_Port GPIOD
#define CLN_B_Pin GPIO_PIN_7
#define CLN_B_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define CLN_V_Pin GPIO_PIN_4
#define CLN_V_GPIO_Port GPIOB
#define CLN_J_Pin GPIO_PIN_5
#define CLN_J_GPIO_Port GPIOB
#define Audio_SCL_Pin GPIO_PIN_6
#define Audio_SCL_GPIO_Port GPIOB
#define Audio_SDA_Pin GPIO_PIN_9
#define Audio_SDA_GPIO_Port GPIOB
#define STEP0_Pin GPIO_PIN_0
#define STEP0_GPIO_Port GPIOE
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

//DEFINITIONS REQUISES PAR LE PROGRAMME:
//Dependances materielles:
#define FREQUENCE_D_OSCILLATEUR_EN_KHZ  84000.0
#define PILOTEIOT1_PORT  LD6_GPIO_Port
#define PILOTEIOT1_SORTIE  LD6_Pin
#define PILOTEIOT2_PORT  LD6_GPIO_Port
#define PILOTEIOT2_SORTIE  LD3_Pin
#define PILOTEIOT3_PORT LD4_GPIO_Port
#define PILOTEIOT3_SORTIE  LD4_Pin
#define PILOTEIOT4_PORT LD5_GPIO_Port
#define PILOTEIOT4_SORTIE  LD5_Pin
#define PILOTEIOB1_PORT B1_GPIO_Port
#define PILOTEIOB1_ENTREE  B1_Pin    
#define INTERFACEB1_VALEUR_LUE_SI_APPUYE  1
#define INTERFACEB1_VALEUR_LUE_SI_RELACHE 0
#define INTERFACEB1_DELAI_ANTI_REBOND_EN_MS  15
#define INTERFACET1_VALEUR_POUR_ALLUMER  1   
#define INTERFACET1_VALEUR_POUR_ETEINDRE 0 
#define INTERFACET2_VALEUR_POUR_ALLUMER  1   
#define INTERFACET2_VALEUR_POUR_ETEINDRE 0 
#define INTERFACET3_VALEUR_POUR_ALLUMER  1   
#define INTERFACET3_VALEUR_POUR_ETEINDRE 0 
#define INTERFACET4_VALEUR_POUR_ALLUMER  1   
#define INTERFACET4_VALEUR_POUR_ETEINDRE 0 

#define PILOTECOLONNE_ROUGE_PORT CLN_R_GPIO_Port
#define PILOTECOLONNE_ROUGE_SORTIE CLN_R_Pin

#define PILOTECOLONNE_VERT_PORT CLN_V_GPIO_Port
#define PILOTECOLONNE_VERT_SORTIE CLN_V_Pin

#define PILOTECOLONNE_JAUNE_PORT CLN_J_GPIO_Port
#define PILOTECOLONNE_JAUNE_SORTIE CLN_J_Pin

#define INTERFACEUSINE_ADRESSE_PCF1_R 0x73
#define INTERFACEUSINE_ADRESSE_PCF1_W 0x72

#define INTERFACEUSINE_ADRESSE_PCF2_R 0x79
#define INTERFACEUSINE_ADRESSE_PCF2_W 0x78

#define INTERFACEUSINE_ADRESSE_PCF3_R 0x77
#define INTERFACEUSINE_ADRESSE_PCF3_W 0x76
#define INTERFACEUSINE_INVERSE_PCF3 1

#define INTERFACEUSINE_ADRESSE_PCF4_R 0x7A
#define INTERFACEUSINE_ADRESSE_PCF4_W 0x7B
#define INTERFACEUSINE_INVERSE_PCF4 0

#define INTERFACEUSINE_ADRESSE_PCF5_R 0x71
#define INTERFACEUSINE_ADRESSE_PCF5_W 0x70
#define INTERFACEUSINE_INVERSE_PCF5 1

#define INTERFACEUSINE_ADRESSE_ADC 0x9B

//D???finition des I/O de l'usine qui sont reli???es au PCF1
#define INTERFACEUSINE_PCF_LED 1
#define INTERFACEUSINE_POS_LED 0
#define INTERFACEUSINE_ID_LED 0

#define INTERFACEUSINE_PCF_VENTOUSE_MONTE 1
#define INTERFACEUSINE_POS_VENTOUSE_MONTE 1
#define INTERFACEUSINE_ID_VENTOUSE_MONTE 1

#define INTERFACEUSINE_PCF_VENTOUSE_DESCEND 1
#define INTERFACEUSINE_POS_VENTOUSE_DESCEND 2
#define INTERFACEUSINE_ID_VENTOUSE_DESCEND 2

#define INTERFACEUSINE_PCF_AIR_TRIG 1
#define INTERFACEUSINE_POS_AIR_TRIG 3
#define INTERFACEUSINE_ID_AIR_TRIG 3

#define INTERFACEUSINE_PCF_ELEVATEUR_MONTE 1
#define INTERFACEUSINE_POS_ELEVATEUR_MONTE 4
#define INTERFACEUSINE_ID_ELEVATEUR_MONTE 4

#define INTERFACEUSINE_PCF_ELEVATEUR_DESCEND 1
#define INTERFACEUSINE_POS_ELEVATEUR_DESCEND 5
#define INTERFACEUSINE_ID_ELEVATEUR_DESCEND 5

#define INTERFACEUSINE_PCF_EJECTEUR_OUT 1
#define INTERFACEUSINE_POS_EJECTEUR_OUT 6
#define INTERFACEUSINE_ID_EJECTEUR_OUT 6

#define INTERFACEUSINE_PCF_EJECTEUR_IN 1
#define INTERFACEUSINE_POS_EJECTEUR_IN 7
#define INTERFACEUSINE_ID_EJECTEUR_IN 7


//D???finition des I/O de l'usine qui sont reli???es au PCF2
#define INTERFACEUSINE_PCF_POUSSOIR 2
#define INTERFACEUSINE_POS_POUSSOIR 0
#define INTERFACEUSINE_ID_POUSSOIR 8

#define INTERFACEUSINE_PCF_CONVOYEUR 2
#define INTERFACEUSINE_POS_CONVOYEUR 1
#define INTERFACEUSINE_ID_CONVOYEUR 9

#define INTERFACEUSINE_PCF_PONT_POS0 2
#define INTERFACEUSINE_POS_PONT_POS0 2
#define INTERFACEUSINE_ID_PONT_POS0 10

#define INTERFACEUSINE_PCF_PONT_POS1 2
#define INTERFACEUSINE_POS_PONT_POS1 3
#define INTERFACEUSINE_ID_PONT_POS1 11

#define INTERFACEUSINE_PCF_PONT_POS2 2
#define INTERFACEUSINE_POS_PONT_POS2 4
#define INTERFACEUSINE_ID_PONT_POS2 12

#define INTERFACEUSINE_PCF_PONT_CONTROLLER 2
#define INTERFACEUSINE_POS_PONT_CONTROLLER 6
#define INTERFACEUSINE_ID_PONT_CONTROLLER 13

#define INTERFACEUSINE_PCF_PONT_START 2
#define INTERFACEUSINE_POS_PONT_START 5
#define INTERFACEUSINE_ID_PONT_START 14


//D???finition des I/O de l'usine qui sont reli???es au PCF3
#define INTERFACEUSINE_PCF_SENSOR_VENTOUSE_HAUT 3
#define INTERFACEUSINE_POS_SENSOR_VENTOUSE_HAUT 0
#define INTERFACEUSINE_ID_SENSOR_VENTOUSE_HAUT 15

#define INTERFACEUSINE_PCF_SENSOR_VENTOUSE_BAS 3
#define INTERFACEUSINE_POS_SENSOR_VENTOUSE_BAS 1
#define INTERFACEUSINE_ID_SENSOR_VENTOUSE_BAS 16

#define INTERFACEUSINE_PCF_SENSOR_MAG 3
#define INTERFACEUSINE_POS_SENSOR_MAG 2
#define INTERFACEUSINE_ID_SENSOR_MAG 17

#define INTERFACEUSINE_PCF_SENSOR_CAP 3
#define INTERFACEUSINE_POS_SENSOR_CAP 3
#define INTERFACEUSINE_ID_SENSOR_CAP 18

#define INTERFACEUSINE_PCF_SENSOR_EJECTEUR_IN 3
#define INTERFACEUSINE_POS_SENSOR_EJECTEUR_IN 4
#define INTERFACEUSINE_ID_SENSOR_EJECTEUR_IN 19

#define INTERFACEUSINE_PCF_SENSOR_EJECTEUR_OUT 3
#define INTERFACEUSINE_POS_SENSOR_EJECTEUR_OUT 5
#define INTERFACEUSINE_ID_SENSOR_EJECTEUR_OUT 20

#define INTERFACEUSINE_PCF_SENSOR_ELEVATEUR_BAS 3
#define INTERFACEUSINE_POS_SENSOR_ELEVATEUR_BAS 6
#define INTERFACEUSINE_ID_SENSOR_ELEVATEUR_BAS 21

#define INTERFACEUSINE_PCF_SENSOR_ELEVATEUR_HAUT 3
#define INTERFACEUSINE_POS_SENSOR_ELEVATEUR_HAUT 7
#define INTERFACEUSINE_ID_SENSOR_ELEVATEUR_HAUT 22

//D???finition des I/O de l'usine qui sont reli???es au PCF4
#define INTERFACEUSINE_PCF_SENSOR_POUSSOIR_IN 4
#define INTERFACEUSINE_POS_SENSOR_POUSSOIR_IN 0
#define INTERFACEUSINE_ID_SENSOR_POUSSOIR_IN 23

#define INTERFACEUSINE_PCF_SENSOR_POUSSOIR_OUT 4
#define INTERFACEUSINE_POS_SENSOR_POUSSOIR_OUT 1
#define INTERFACEUSINE_ID_SENSOR_POUSSOIR_OUT 24

#define INTERFACEUSINE_PCF_SENSOR_OPTIQUE_BLOC 4
#define INTERFACEUSINE_POS_SENSOR_OPTIQUE_BLOC 2
#define INTERFACEUSINE_ID_SENSOR_OPTIQUE_BLOC 25

#define INTERFACEUSINE_PCF_SENSOR_OPTIQUE_CHUTE 4
#define INTERFACEUSINE_POS_SENSOR_OPTIQUE_CHUTE 3
#define INTERFACEUSINE_ID_SENSOR_OPTIQUE_CHUTE 26

#define INTERFACEUSINE_PCF_BOUTON_VERT 4
#define INTERFACEUSINE_POS_BOUTON_VERT 4
#define INTERFACEUSINE_ID_BOUTON_VERT 27

#define INTERFACEUSINE_PCF_BOUTON_ROUGE 4
#define INTERFACEUSINE_POS_BOUTON_ROUGE 5
#define INTERFACEUSINE_ID_BOUTON_ROUGE 28

#define INTERFACEUSINE_PCF_SENSOR_PRESSION 4
#define INTERFACEUSINE_POS_SENSOR_PRESSION 6
#define INTERFACEUSINE_ID_SENSOR_PRESSION 29

//D???finition des I/O de l'usine qui sont reli???es au PCF4
#define INTERFACEUSINE_PCF_PONT_READY_FOR_OPERATION 5
#define INTERFACEUSINE_POS_PONT_READY_FOR_OPERATION 2
#define INTERFACEUSINE_ID_PONT_READY_FOR_OPERATION 30

#define INTERFACEUSINE_PCF_PONT_DEFAULT_MOTION_COMPLETE 5
#define INTERFACEUSINE_POS_PONT_DEFAULT_MOTION_COMPLETE 1
#define INTERFACEUSINE_ID_PONT_DEFAULT_MOTION_COMPLETE 31

#define INTERFACEUSINE_PCF_PONT_DEFAULT_ACK_START 5
#define INTERFACEUSINE_POS_PONT_DEFAULT_ACK_START 0
#define INTERFACEUSINE_ID_PONT_DEFAULT_ACK_START 32

#define INTERFACEUSINE_PCF_PONT_DEFAULT_ERROR 5
#define INTERFACEUSINE_POS_PONT_DEFAULT_ERROR 3
#define INTERFACEUSINE_ID_PONT_DEFAULT_ERROR 33

//Definition des I/O de l'usine relier a l'ascenseur
#define INTERFACEUSINE_ID_ASCENSEUR_Q1 STEP0_Pin
#define INTERFACEUSINE_ID_ASCENSEUR_Q2 STEP1_Pin
#define INTERFACEUSINE_ID_ASCENSEUR_Q3 STEP2_Pin
#define INTERFACEUSINE_ID_ASCENSEUR_Q4 STEP3_Pin
#define INTERFACEUSINE_ID_SW_ASC GPIO_PIN_11
#define INTERFACEUSINE_ID_AMPOULE TRIAC_OUT_Pin

//Dependances logicielles:


//#define MODE_BYPASS_POSTE_DE_COMMANDE


#define FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ 2000.0
#define PILOTETIMER1MODE2_TAUX_DE_BITS 19200.0
#define PILOTETIMER6UP_COMPTE_MAXIMAL  (\
  (unsigned int)((FREQUENCE_D_OSCILLATEUR_EN_KHZ \
  /FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ * 1000.0)-1.0))

#define PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION  (0x301<<5)
#define PILOTECAN1_IDENTIFICATION_EN_RECEPTION  (0x123<<5) //Code mal fait
#define PILOTECAN1_MASQUE_11_BITS_EN_RECEPTION  (0x000) //0x000


#define INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ  100.0
#define INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10
#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS  300
#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS  200
#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS  500
#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS  1000
#define PROCESSUSBOUTONCONNECTE_TEMPS_MAXIMAL_POUR_RECEVOIR_EN_MS 100

//BASE DE TEMPS
<<<<<<< HEAD
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES  8
=======
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES  6
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_PONT 7
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_ASCENSEUR 20
>>>>>>> 4da58d318c6ea7a702745249341195bc18bc6aac
#define INTERFACEB1_PHASE 0
#define SERVICECOMMUNICATION_GERE1 2
#define SERVICECOMMUNICATION_GERE2 1
#define PROCESSUSUSINE_GERE 3
#define INTERFACEUSINE_GERE 4
<<<<<<< HEAD
#define INTERFACEPONT_GERE 5
#define INTERFACECOLONNE_PHASE 6
#define INTERFACESTEPMOTEUR_GERE 7
=======
#define INTERFACECOLONNE_PHASE 5
#define INTERFACEPONT_GERE 8
#define INTERFACEASCENSEUR_GERE 9
>>>>>>> 4da58d318c6ea7a702745249341195bc18bc6aac

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INFORMATION_DISPONIBLE  1
#define INFORMATION_TRAITEE  0
#define REQUETE_ACTIVE  1
#define REQUETE_TRAITEE 0
#define MODULE_EN_FONCTION 1
#define MODULE_PAS_EN_FONCTION 0

#define INTERFACEUSINE_ALLUME 0
#define INTERFACEUSINE_ETEINT 1
#define INTERFACEUSINE_BOUTON_APPUYE 1
#define INTERFACEUSINE_BOUTON_RELACHE 0
#define MONTE 1
#define DESCEND 0
#define INTERFACEUSINE_SENSOR_HIGH 1
#define INTERFACEUSINE_SENSOR_LOW 0
#define INTERFACEUSINE_OUTPUT_HIGH 0
#define INTERFACEUSINE_OUTPUT_LOW 1

#include <string.h>
//Fonctions publiques:
void neFaitRien(void);
void updateMessageEcran (char const string[]);
void updateModeEcran(char const string[]);
void updateEtatEcran(char const string[]);
//Variables publiques:
//copiez et adaptes les lignes qui suivent dans les fichiers .h des modules
//qui utilisent ces variables qui sont definies par htim6
//extern TIM_HandleTypeDef htim6;
//extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
