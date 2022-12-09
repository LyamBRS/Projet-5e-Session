/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// S-0010:
// Historique:
//  2019-10-27, Yves Roy, creation

// notes sur l'utilisation des timers.
//  https://www.st.com/content/ccc/resource/technical/document/application_note/group0/91/01/84/3f/7c/67/41/3f/DM00236305/files/DM00236305.pdf/jcr:content/translations/en.DM00236305.pdf
// https://stm32f4-discovery.net/2014/05/stm32f4-stm32f429-discovery-pwm-tutorial/
// timer 6 sur APB1
// timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
// default_frequency = 84MHz compte tenu des options choisies avec le "cube"
// TIM_Period = timer_tick_frequency / TIM_frequency - 1
// il faut s'assurer que le compte pour la periode est plus petit que 65536

#include "piloteTimer6Up.h"
#include "piloteCAN1.h"
#include "piloteUSART2.h"
#include "piloteIOB1.h"
#include "piloteIOT1.h"
#include "piloteIOT2.h"
#include "piloteIOT3.h"
#include "piloteIOT4.h"
#include "serviceBaseDeTemps.h"
//#include "serviceProtocole637.h"
#include "interfaceB1.h"
#include "interfaceT1.h"
#include "interfaceT2.h"
#include "interfaceT3.h"
#include "interfaceT4.h"
//#include "processusBoutonConnecte.h"
#include "processusUsine.h"
#include "interfaceUsine.h"
#include "piloteLcd.h"
#include "interfaceLcd.h"
#include "interfaceCAN1.h"
#include "ServiceCommunication.h"
#include "interfaceColonne.h"
#include "piloteColonne.h"
#include "interfaceB1.h"
//#include "stm32f4xx_hal_conf.h" 
//#include "stm32f4xx_it.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM6_Init(void);
static void MX_CAN1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void main_initialiseAvantLeHAL(void);
void main_initialiseApresLeHAL(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void main_initialiseAvantLeHAL(void)
{
  piloteTimer6Up_initialise();
  serviceBaseDeTemps_initialise();
  // piloteCAN1_initialise(); //irait ici en temps normal... mais il y a un bug dans le cube
  // piloteUSART2_initialise();
  piloteIOB1_initialise();
  piloteIOT1_initialise();
  piloteIOT2_initialise();
  piloteIOT3_initialise();
  piloteIOT4_initialise();
  
  interfaceT1_initialise();
  interfaceT2_initialise();
  interfaceT3_initialise();
  interfaceT4_initialise();
  
  interfaceB1_initialise();
  interfaceColonne_initialise();  
  interfaceUsine_Initialise();  
}

void main_initialiseApresLeHAL(void)
{
  
  piloteTimer6Up_permetLesInterruptions();
  piloteCAN1_initialise();
  ServiceCommunication_initialise();
  vInitGLcd();
  interfaceLcd_Clear_Swipe(0);
  processusUsine_initialise();
}

void neFaitRien(void)
{
}

// Variables globales
bool bFlagUpdateMessageEcran;
bool bFlagUpdateEtatEcran;
bool bFlagUpdateModeEcran;
bool flagTexteFini = 0;
char messageEcran[40];
char etatEcran[20];
char modeEcran[20];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  main_initialiseAvantLeHAL();

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  MX_CAN1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  main_initialiseApresLeHAL();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  interfaceColonne_allume(INTERFACECOLONNE_ROUGE);
  interfaceColonne_allume(INTERFACECOLONNE_VERT);
  interfaceColonne_allume(INTERFACECOLONNE_JAUNE);

  
  
  interfaceLcd_Draw_Shape_RectF(0,43,128,2,1);
  interfaceLcd_Draw_Shape_RectF(0,27,128,2,1);
  interfaceLcd_Draw_Shape_RectF(0,11,128,2,1);
  vPutStringGLcd("Mode:               ", 4, 5);
  vPutStringGLcd("Etat:Attend Bouton  ", 2, 5);
  unsigned char oldBruh = 0;
  while (1)
  {
    /*
    //Test du step moteur
    HAL_GPIO_WritePin(STEP0_GPIO_Port, STEP0_Pin, (GPIO_PinState)1);  
    HAL_GPIO_WritePin(STEP1_GPIO_Port, STEP1_Pin, (GPIO_PinState)0); 
    HAL_GPIO_WritePin(STEP2_GPIO_Port, STEP2_Pin, (GPIO_PinState)0); 
    HAL_GPIO_WritePin(STEP3_GPIO_Port, STEP3_Pin, (GPIO_PinState)0); 
    */
    if (bFlagUpdateMessageEcran)
    {
      flagTexteFini = 0;
      for (int i = 0; i <= 39; i++)
      {
        if (i <= 19)
        {
          if (!flagTexteFini)vPutCharGLcd(messageEcran[i], 6, i, 5);
          else vPutCharGLcd(' ', 6, i, 5);
        }
        else if (i <= (39))
        {
          if (!flagTexteFini)vPutCharGLcd(messageEcran[i], 7, i - 20, 5);
          else vPutCharGLcd(' ', 7, i - 20, 5);
        }
        if (messageEcran[i + 1] == '\0')flagTexteFini = 1;
      }
      bFlagUpdateMessageEcran = 0;
    }

    if (bFlagUpdateEtatEcran)
    {
      flagTexteFini = 0;
      for (int i = 0; i+5 <= 19; i++)
      {       
        if (!flagTexteFini)vPutCharGLcd(etatEcran[i], 2, i+5, 5);
        else vPutCharGLcd(' ', 2, i+5, 5);
        if (etatEcran[i + 1] == '\0') flagTexteFini = 1;
      }
      bFlagUpdateEtatEcran = 0;
    }
    
    if (bFlagUpdateModeEcran)
    {
      flagTexteFini = 0;
      for (int i = 0; i+5 <= 19; i++)
      {       
        if (!flagTexteFini)vPutCharGLcd(modeEcran[i], 4, i+5, 5);
        else vPutCharGLcd(' ', 4, i+5, 5);
        if (modeEcran[i + 1] == '\0') flagTexteFini = 1;
      }
      bFlagUpdateModeEcran = 0;
    }

    //Affichage de l'état du CAN
    if (!ModuleData.CantConnect) // Pas connecté
    {
      vPutStringGLcd("CAN Connected       ", 0, 5);
    }
    else
    {
      vPutStringGLcd("CAN Disconnected    ", 0, 5);
    }
    
     if (piloteCAN1_messageDisponible()) // Pas connecté
    {
      //vPutStringGLcdINV("Message disponible  ", 2, 5);
    }
    else
    {
      //vPutStringGLcdINV("No Message?         ", 2, 5);
    }

    if(true)
    {
      unsigned int bruh = piloteCAN1_litLesErreurs();
      static unsigned char index = 0;

      if(bruh != oldBruh)
      {
        interfaceLcd_Draw_Text_Integer(32,16+(6*index),bruh,3,1);
        index++;
        oldBruh = bruh;
      }  
    }

    //interfaceLcd_Draw_Text_Integer(0,32,ModuleData.Mode,2,1);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 168;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_3TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = PILOTETIMER6UP_COMPTE_MAXIMAL;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 19200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|TRIAC_OUT_Pin|STEP0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CLN_R_Pin|STEP3_Pin|STEP1_Pin|STEP2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RD_Pin|A4_Pin|CS0_Pin|CS1_Pin
                          |CS2_Pin|CS3_Pin|CLN_V_Pin|CLN_J_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, A0_Pin|A1_Pin|A2_Pin|A3_Pin
                          |LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin|CLN_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin TRIAC_OUT_Pin STEP0_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|TRIAC_OUT_Pin|STEP0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : TRIAC_IN_Pin */
  GPIO_InitStruct.Pin = TRIAC_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TRIAC_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CLN_R_Pin STEP3_Pin STEP1_Pin STEP2_Pin */
  GPIO_InitStruct.Pin = CLN_R_Pin|STEP3_Pin|STEP1_Pin|STEP2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : I2S3_WS_Pin */
  GPIO_InitStruct.Pin = I2S3_WS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(I2S3_WS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RD_Pin A4_Pin CS0_Pin CS1_Pin
                           CS2_Pin CS3_Pin CLN_V_Pin CLN_J_Pin */
  GPIO_InitStruct.Pin = RD_Pin|A4_Pin|CS0_Pin|CS1_Pin
                          |CS2_Pin|CS3_Pin|CLN_V_Pin|CLN_J_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin D1_Pin D2_Pin D3_Pin
                           D4_Pin D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin
                          |D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : A0_Pin A1_Pin A2_Pin A3_Pin
                           LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin CLN_B_Pin */
  GPIO_InitStruct.Pin = A0_Pin|A1_Pin|A2_Pin|A3_Pin
                          |LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin|CLN_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : I2S3_MCK_Pin I2S3_SCK_Pin I2S3_SD_Pin */
  GPIO_InitStruct.Pin = I2S3_MCK_Pin|I2S3_SCK_Pin|I2S3_SD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void updateMessageEcran(char const string[])
{
  bFlagUpdateMessageEcran = 1;
  for (int i = 0; i <= 39; i++)
  {
    messageEcran[i] = string[i];
    if (string[i] == '\0')
      return;
  }
}

void updateEtatEcran(char const string[])
{
  bFlagUpdateEtatEcran = 1;
  for (int i = 0; i <= 20; i++)
  {
    etatEcran[i] = string[i];
    if (string[i] == '\0')
      return;
  }
}

void updateModeEcran(char const string[])
{
  bFlagUpdateModeEcran = 1;
  for (int i = 0; i <= 20; i++)
  {
    modeEcran[i] = string[i];
    if (string[i] == '\0')
      return;
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
