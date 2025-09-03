/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define RED_LED2 GPIO_PIN_2
#define YELLOW_LED2 GPIO_PIN_3
#define GREEN_LED2 GPIO_PIN_4
#define RED_LED GPIO_PIN_5
#define YELLOW_LED GPIO_PIN_6
#define GREEN_LED GPIO_PIN_7
#define ON 1
#define OFF 0
#define RED 1
#define YELLOW 2
#define GREEN 3
#define RED2 4
#define YELLOW2 5
#define GREEN2 6
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t status = GREEN;
uint8_t counter = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int num);
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
  while (1)
  {
	  display7SEG(9 - counter);
	  switch(status){
	  case GREEN:
		  HAL_GPIO_WritePin(GPIOA, GREEN_LED2, OFF);
		  HAL_GPIO_WritePin(GPIOA, RED_LED2, ON);
		  HAL_GPIO_WritePin(GPIOA, YELLOW_LED2, ON);
		  if(counter < 2){
			  HAL_GPIO_WritePin(GPIOA, GREEN_LED, ON);
			  HAL_GPIO_WritePin(GPIOA, RED_LED, OFF);
			  HAL_GPIO_WritePin(GPIOA, YELLOW_LED, ON);
		  }
		  if(counter  == 2 ){
			  status = YELLOW;
		  }
		  break;
	  case YELLOW:
		  HAL_GPIO_WritePin(GPIOA, GREEN_LED2, ON);
		  HAL_GPIO_WritePin(GPIOA, RED_LED2, ON);
		  HAL_GPIO_WritePin(GPIOA, YELLOW_LED2, OFF);
		  if(counter >= 3 && counter < 4){
			  HAL_GPIO_WritePin(GPIOA, GREEN_LED, ON);
			  HAL_GPIO_WritePin(GPIOA, RED_LED, OFF);
			  HAL_GPIO_WritePin(GPIOA, YELLOW_LED, ON);
		  }
		  if(counter == 4){
			  status = RED;
		  }
		  break;
	  case RED:
		  HAL_GPIO_WritePin(GPIOA, GREEN_LED2, ON);
		  HAL_GPIO_WritePin(GPIOA, RED_LED2, OFF);
		  HAL_GPIO_WritePin(GPIOA, YELLOW_LED2, ON);
		  if(counter >= 5 && counter < 8 ){
			  HAL_GPIO_WritePin(GPIOA, GREEN_LED, OFF);
			  HAL_GPIO_WritePin(GPIOA, RED_LED, ON);
			  HAL_GPIO_WritePin(GPIOA, YELLOW_LED, ON);
		  }
		  if(counter >= 8 && counter < 9){
			  HAL_GPIO_WritePin(GPIOA, GREEN_LED, ON);
			  HAL_GPIO_WritePin(GPIOA, RED_LED, ON);
			  HAL_GPIO_WritePin(GPIOA, YELLOW_LED, OFF);
		  }
		  if(counter == 9){
			  counter = -1;
			  status = GREEN;
		  }
		  break;
	  	  default: break;

	  }
	  counter ++;
	  HAL_Delay(1000);
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_LED2_Pin|YELLOW_LED2_Pin|GREEN_LED2_Pin|RED_LED_Pin
                          |YELLOW_LED_Pin|GREEN_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_LED2_Pin YELLOW_LED2_Pin GREEN_LED2_Pin RED_LED_Pin
                           YELLOW_LED_Pin GREEN_LED_Pin */
  GPIO_InitStruct.Pin = RED_LED2_Pin|YELLOW_LED2_Pin|GREEN_LED2_Pin|RED_LED_Pin
                          |YELLOW_LED_Pin|GREEN_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//a-0 b-1 c-2 d-3 e-4 f-5 g-6
void display7SEG(int num){
	switch(num){
	case 0:

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, ON);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, ON);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, OFF);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, OFF);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, OFF);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, OFF);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, OFF);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, ON);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, OFF);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, ON);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, OFF);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, OFF);
		break;
	default: break;

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
