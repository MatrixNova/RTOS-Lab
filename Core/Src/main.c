/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
//void clearAllClock();
//void setNumberOnClock(int num);
//void clearNumberOnClock(int num);
//void displayTime(int hour, int minutes, int seconds);
void timer_isr();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int hour = 2;
  int minutes = 5;
  int seconds = 18;
  while (1)
  {
	  HAL_GPIO_WritePin(GPIOA, L0_Pin|L1_Pin|L2_Pin|L3_Pin|L4_Pin|L5_Pin|L6_Pin|L7_Pin|L8_Pin|L9_Pin|L10_Pin|L11_Pin, GPIO_PIN_RESET);

	  if (seconds == 60)
	  {
		  seconds = 0;
		  minutes++;
	  }

	  if (minutes == 60)
	  {
		  minutes = 0;
		  hour++;
	  }

	  if (hour == 24)
	  {
		  hour = 0;
	  }

	  displayTime(hour, minutes, seconds);

	  seconds++;
	  HAL_Delay(10);
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
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, L0_Pin|L1_Pin|L2_Pin|L3_Pin|L4_Pin|L5_Pin|L6_Pin|L7_Pin|L8_Pin|L9_Pin|L10_Pin|L11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : L0_Pin_Pin L1_Pin_Pin L2_Pin_Pin L3_Pin_Pin
                           L4_Pin_Pin L5_Pin_Pin L6_Pin_Pin L7_Pin_Pin
                           L8_Pin_Pin L9_Pin_Pin L10_Pin_Pin L11_Pin_Pin */
  GPIO_InitStruct.Pin = L0_Pin|L1_Pin|L2_Pin|L3_Pin|L4_Pin|L5_Pin|L6_Pin|L7_Pin|L8_Pin|L9_Pin|L10_Pin|L11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void clearAllClock()
{
	HAL_GPIO_WritePin(GPIOA, L0_Pin|L1_Pin|L2_Pin|L3_Pin
	              |L4_Pin|L5_Pin|L6_Pin|L7_Pin
	              |L8_Pin|L9_Pin|L10_Pin|L11_Pin, GPIO_PIN_SET);
}

void setNumberOnClock(int num)
{
    switch (num) {
        case 0:
            HAL_GPIO_WritePin(GPIOA, L0_Pin, GPIO_PIN_RESET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOA, L1_Pin, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOA, L2_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, L3_Pin, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOA, L4_Pin, GPIO_PIN_RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOA, L5_Pin, GPIO_PIN_RESET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOA, L6_Pin, GPIO_PIN_RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOA, L7_Pin, GPIO_PIN_RESET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOA, L8_Pin, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOA, L9_Pin, GPIO_PIN_RESET);
            break;
        case 10:
            HAL_GPIO_WritePin(GPIOA, L10_Pin, GPIO_PIN_RESET);
            break;
        case 11:
            HAL_GPIO_WritePin(GPIOA, L11_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

void clearNumberOnClock(int num)
{
    switch (num) {
        case 0:
            HAL_GPIO_WritePin(GPIOA, L0_Pin, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOA, L1_Pin, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOA, L2_Pin, GPIO_PIN_SET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, L3_Pin, GPIO_PIN_SET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOA, L4_Pin, GPIO_PIN_SET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOA, L5_Pin, GPIO_PIN_SET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOA, L6_Pin, GPIO_PIN_SET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOA, L7_Pin, GPIO_PIN_SET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOA, L8_Pin, GPIO_PIN_SET);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOA, L9_Pin, GPIO_PIN_SET);
            break;
        case 10:
            HAL_GPIO_WritePin(GPIOA, L10_Pin, GPIO_PIN_SET);
            break;
        case 11:
            HAL_GPIO_WritePin(GPIOA, L11_Pin, GPIO_PIN_SET);
            break;
        default:
            break;
    }
}

void displayTime(int hour, int minutes, int seconds)
{
	clearAllClock();
	int temp_hour = hour - 1;
	if (temp_hour >= 12)
	{
		temp_hour -= 12;
	}

	if (minutes == 0 || seconds == 0) clearNumberOnClock(temp_hour - 1);

	setNumberOnClock(temp_hour);

	if (minutes % 12 == 0)
	{
		clearNumberOnClock((minutes - 1)%12);
	}
	setNumberOnClock(minutes%12);

	if (seconds % 12 == 0)
	{
		clearNumberOnClock((seconds - 1)%12);
	}
	setNumberOnClock(seconds%12);
}

int num = 0;



//void timer_isr()
//{
//	if (num % 100 == 0)
//	{
//		HAL_GPIO_WritePin(GPIOA, L1_Pin, RESET);
//	}
//	if (num % 200 == 0)
//	{
//		HAL_GPIO_WritePin(GPIOA, L1_Pin, SET);
//	}
//	num++;
//}



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
  while (1){
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
