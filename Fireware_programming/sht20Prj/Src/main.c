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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TEMP 												0
#define HUMI 												1
						/* Command set 8*/
#define SHT2x_ADDR									(0x40 << 1) //0b0100 0000 -> 7bit form
#define SHT2x_HOLD_MASTER_T 				0xE3
#define SHT2x_HOLD_MASTER_RH				0xE5
#define SHT2x_NOHOLE_MASTER_T				0xF3
#define SHT2x_NOHOLE_MASTER_RH			0xF5
#define SHT2x_WRITE_USER_REG 				0xE6
#define SHT2x_READ_USER_REG 				0xE7
#define SHT2x_SOFT_RESET 						0xFE


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
FILE __stdout;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int fputc (int ch, FILE *stream){
	HAL_UART_Transmit(&huart2,(uint8_t*)&ch,1,0xFFFF);
	return ch;
}
void SHT20_Init();
float SHT20(int);
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
		float temperature, humidity;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	SHT20_Init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		temperature = SHT20(TEMP);
		humidity = SHT20(HUMI);
		printf("temperature is %.2f Celsius degree\n\r",temperature);
		printf("humidity is %.2f %%\n\n\r",humidity);
		
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void SHT20_Init(void){
	if(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)SHT2x_ADDR,(uint8_t*)SHT2x_SOFT_RESET,1,0xFFFF) == HAL_OK){
		printf("SHT20 RESET FAIL!!");
	}else{
		printf("SHT20 RESET SUCCESS!!");
	}
		
}

float SHT20(int select){
	
	uint8_t I2cData[3];
	uint16_t SLAVER_ADDR = SHT2x_ADDR;
	uint16_t sensor;
	float convData = 0.0;
	
	
	if(select == TEMP){
		I2cData[0] = SHT2x_NOHOLE_MASTER_T;
		HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SLAVER_ADDR, (uint8_t*)I2cData,1,0xFFFF);
		HAL_Delay(100);
		HAL_I2C_Master_Receive(&hi2c1, (uint16_t)SLAVER_ADDR, (uint8_t*)I2cData, 2,0xFFFF);
		sensor = (I2cData[0] << 8)|I2cData[1];
		convData = -46.85+175.72 / 65536 *(float)sensor;
		return convData;
	}
	
	if(select == HUMI){
	I2cData[0] = SHT2x_NOHOLE_MASTER_RH;
		HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)SLAVER_ADDR,(uint8_t*)I2cData,1,0xFFFF);
		HAL_Delay(100);
		HAL_I2C_Master_Receive(&hi2c1,(uint16_t)SLAVER_ADDR,(uint8_t*)I2cData, 2,0xFFFF);
		sensor = (I2cData[0] << 8)|I2cData[1];
		convData = -6 + 125 *((float)sensor/65536);
		return convData;
		
	}
	
	return 0;
	
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
