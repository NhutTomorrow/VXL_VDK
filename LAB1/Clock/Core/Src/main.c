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

#define INTERFACE 0
#define MINUTE 1
#define HOURS  2
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t status = 0;
uint8_t counter = 0;
uint8_t ps = -1;
uint8_t pm = -1;
uint8_t ph = -1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int num);
void clearAllClock();
void setNumberOnClock(int num);
void clearNumberOnClock(int num);
void updateClock(uint8_t s, uint8_t m, uint8_t h);
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
uint8_t s, h, m;
s = h = m = 0;
clearAllClock();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  HAL_Delay(100);
	 	     s++;
	 	     if(s == 60){
	 	         s = 0;
	 	         m++;
	 	     }
	 	     if(m == 60){
	 	         m = 0;
	 	         h++;
	 	     }
	 	     if(h == 12){
	 	         h = 0;
	 	     }
	 	     updateClock(s, m, h);
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
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7
                           PA8 PA9 PA10 PA11
                           PA12 PA13 PA14 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void updateClock(uint8_t s, uint8_t m, uint8_t h){
	// xoa kim cu
	if(ps != -1 ) clearNumberOnClock(ps/5);
	if(pm != -1 ) clearNumberOnClock(pm/5);
	if(ph != -1 ) clearNumberOnClock(ph);

	//set kim moi
	setNumberOnClock(s/5);
	setNumberOnClock(m /5);
	setNumberOnClock(h);

	ps = s;
	pm = m;
	ph = h;
}
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
void clearAllClock(){

	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, ON);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, ON);
}
void setNumberOnClock(int num){

	switch(num){

		  case 0:
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, OFF);

			  break;
		  case 1:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, OFF);

			  break;
		  case 2:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, OFF);

			  break;

		  case 3:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, OFF);

			  break;
		  case 4:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, OFF);

			  break;
		  case 5:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, OFF);

			  break;
		  case 6:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, OFF);

			  break;
		  case 7:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, OFF);

			  break;
		  case 8:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, OFF);

			  break;
		  case 9:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, OFF);

			  break;
		  case 10:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, OFF);

			  break;
		  case 11:

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, OFF);

			  break;
		  default: break;
	  }
}
void clearNumberOnClock(int num){
	switch(num){

			  case 0:
				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, ON);

				  break;
			  case 1:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ON);

				  break;
			  case 2:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ON);

				  break;

			  case 3:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ON);

				  break;
			  case 4:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ON);

				  break;
			  case 5:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, ON);

				  break;
			  case 6:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, ON);

				  break;
			  case 7:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, ON);

				  break;
			  case 8:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, ON);

				  break;
			  case 9:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, ON);

				  break;
			  case 10:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, ON);

				  break;
			  case 11:

				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, ON);

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
