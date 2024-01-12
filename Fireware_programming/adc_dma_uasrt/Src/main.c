/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
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
FILE __stdout;
uint16_t adcData[2];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int fputc(int ch, FILE* stream){
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 0xffff);
	
	return ch;
}
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcData, 1);  // adc dma start
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		int cdc_input_min = 2400;
		int cdc_input_max = 3500;
		int input_level = 9;
		int level_0 = ((cdc_input_max-cdc_input_min)/input_level);
		
		
		
		
		if(adcData[0] >= cdc_input_min+(level_0*0) && adcData[0] < cdc_input_min+(level_0*1)){
			HAL_GPIO_WritePin(GPIOC, 0b0000000111111110, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000000000000, 0);
		}else if((adcData[0] >=cdc_input_min+(level_0*1) && (adcData[0] < cdc_input_min+(level_0*2)))){
			HAL_GPIO_WritePin(GPIOC, 0b0000000011111110, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000100000000, 0);
		}else if((adcData[0] >=cdc_input_min+(level_0*2) && (adcData[0] < cdc_input_min+(level_0*3)))){
			HAL_GPIO_WritePin(GPIOC, 0b0000000001111110, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000110000000, 0);
		}else if((adcData[0] >=cdc_input_min+(level_0*3) && (adcData[0] < cdc_input_min+(level_0*4)))){
			HAL_GPIO_WritePin(GPIOC, 0b0000000000111110, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000111000000, 0);
		}else if((adcData[0] >=cdc_input_min+(level_0*4) && (adcData[0] < cdc_input_min+(level_0*5)))){
			HAL_GPIO_WritePin(GPIOC, 0b0000000000011110, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000111100000, 0);
		}else if((adcData[0] >=cdc_input_min+(level_0*5) && (adcData[0] < cdc_input_min+(level_0*6)))){
			HAL_GPIO_WritePin(GPIOC, 0b0000000000001110, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000111110000, 0);
		}else if((adcData[0] >=cdc_input_min+(level_0*6) && (adcData[0] < cdc_input_min+(level_0*7)))){
			HAL_GPIO_WritePin(GPIOC, 0b0000000000000110, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000111111000, 0);
		}else if((adcData[0] >=cdc_input_min+(level_0*7) && (adcData[0] < cdc_input_min+(level_0*8)))){
			HAL_GPIO_WritePin(GPIOC, 0b0000000000000010, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000111111100, 0);
		}else if((adcData[0] >=cdc_input_min+(level_0*8) && (adcData[0] < cdc_input_min+(level_0*9)))){
			HAL_GPIO_WritePin(GPIOC, 0b0000000000000000, 1);
			HAL_GPIO_WritePin(GPIOC, 0b0000000111111110, 0);
		}
			
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
