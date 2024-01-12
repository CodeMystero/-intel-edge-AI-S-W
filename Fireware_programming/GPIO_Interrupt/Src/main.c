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
#include "usart.h"
#include "gpio.h"

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
volatile int userBtnIsr = 0;
volatile int userBtnIsr1 = 0;
//volatile int __flag__ = 0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	int j = 0;
  while (1)
  {
		/*
		if(userBtnIsr ==0) {}
			
		if(userBtnIsr ==1) {
			HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),1);
			HAL_Delay(300);
			HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),0);
			if (userBtnIsr ==1){j++;}
			if (j >7){ j = 0;}
		}
		
		if(userBtnIsr ==2) {
			HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),1);
			HAL_Delay(300);
			HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),0);
			if (userBtnIsr ==2){j--;}
			if (j <0){ j = 7;}
		}
		*/
		/*
		if (userBtnIsr1 ==0){
			HAL_GPIO_WritePin(GPIOC,LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin,0);
			HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),1);
			HAL_Delay(300);
			HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),0);
			if (userBtnIsr ==0){j++;}
			if (userBtnIsr ==1){j--;}
			if (j >7){ j = 0;}
			if (j <0){ j = 7;}
		}else if((userBtnIsr1 ==1)){	
			HAL_GPIO_WritePin(GPIOC,LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin,1);
			HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),0);
			HAL_Delay(300);
			HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),1);
			if (userBtnIsr ==0){j++;}
			if (userBtnIsr ==1){j--;}
			if (j >7){ j = 0;}
			if (j <0){ j = 7;}
	 }*/
	 
		
		HAL_GPIO_WritePin(GPIOC,LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin,userBtnIsr1);
		HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),1-userBtnIsr1);
		HAL_Delay(300);
		HAL_GPIO_WritePin(GPIOC,LED0_Pin << (j),userBtnIsr1);
		if (userBtnIsr ==0){j++;}
		if (userBtnIsr ==1){j--;}
		if (j >7){ j = 0;}
		if (j <0){ j = 7;}
 }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//PB0_Pin = pin num 12
	if(GPIO_Pin == PB0_Pin){
			/*int __flag__rn = __flag__% 3;
			__flag__++;
			if (__flag__rn !=0){userBtnIsr = __flag__rn;}*/
			userBtnIsr = 1 - userBtnIsr;
	}
	
	if(GPIO_Pin == PB1_Pin){
			userBtnIsr1 = 1 - userBtnIsr1;
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
