/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int hext[8],hexu[8];
int value=1,i,j;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int convert(int valueRead)
{
	int number[10] = {64,121,36,48,25,18,3,120,0,24};
	int tensdigit,unitsdigit,unitsdigitv,tensdigitv,bolum,kalan;
	tensdigit = (valueRead/10);
	unitsdigit = (valueRead%10);
	
	tensdigitv = number[tensdigit];
	unitsdigitv = number[unitsdigit];
	
	for(int i =0; i<=5;i++)
	{
		
		bolum=tensdigitv/2;
		kalan=tensdigitv%2;
		hext[i]=kalan;
		tensdigitv=bolum;
		if(i==5)
		{
			hext[i+1]=bolum;
		}
	}
	
	for(int i =0; i<=5;i++)
	{
		bolum=unitsdigitv/2;
		kalan=unitsdigitv%2;
		hexu[i]=kalan;
		unitsdigitv=bolum;
		if(i==5)
		{
			hexu[i+1]=bolum;
		}
	}
	
	return 0;
}
int writedis()
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0); // DIGIT 1 LOW
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,1); // DIGIT 0 HIGH
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, hext[0]); //B3
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, hext[1]); //B4
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, hext[2]); //B5
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, hext[3]); //B6
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, hext[4]); //B7
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, hext[5]); //B8
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, hext[6]); //B9
	HAL_Delay(3);
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,0); // DIGIT 0 LOW
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1); // DIGIT 1 HIGH
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, hexu[0]); //B3
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, hexu[1]); //B4
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, hexu[2]); //B5
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, hexu[3]); //B6
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, hexu[4]); //B7
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, hexu[5]); //B8
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, hexu[6]); //B9
	HAL_Delay(3);
	
	
	return 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		int i,k,adc1,loop;
    /* USER CODE BEGIN 3 */
		
			HAL_ADC_Start(&hadc1); // START ADC1
			HAL_ADC_PollForConversion(&hadc1, 1000); // ADC GIVE VALUE 1000 LOOP 
			adc1 = HAL_ADC_GetValue(&hadc1); // WRITE VALUE 
			loop=adc1/41; // 99-0 = (4096/41) OR (0/41)
			if(0<loop && loop<2) loop=0;
			convert(loop); // INT VALUE CONVERT DIGIT 
			for(k=0;k<10;k++) // ALWAYS DISPLAY OPEN 
			{
			writedis(); 
			}
			
		
			
		
		
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DIGIT1_Pin|DIGIT2_Pin|A_Pin|B_Pin
                          |C_Pin|D_Pin|E_Pin|F_Pin
                          |G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DIGIT1_Pin DIGIT2_Pin A_Pin B_Pin
                           C_Pin D_Pin E_Pin F_Pin
                           G_Pin */
  GPIO_InitStruct.Pin = DIGIT1_Pin|DIGIT2_Pin|A_Pin|B_Pin
                          |C_Pin|D_Pin|E_Pin|F_Pin
                          |G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
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
