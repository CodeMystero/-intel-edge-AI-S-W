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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"

#define		TEMP									0
#define 	HUMI									1

#define 	SHT20_ADDR 						0b10000000
#define		SHT20_TRG_HM_T 				0b11100011
#define		SHT20_TRG_HM_RH 			0b11100101
#define		SHT20_TRG_NHM_T 			0b11110011
#define		SHT20_TRG_NHM_RH 			0b11110101
#define 	SHT20_W_UR						0b11100110
#define		SHT20_R_UR						0b11100111
#define		SHT20_SOFT_RESET			0b11111110

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
uint8_t rx_data;
char rx_data_container[20] = {0,};
char rx_buffer[20] = {0,};
uint8_t BP = '\b';
uint8_t Blank = ' ';
uint8_t Return_r = '\r';
int cnt = 0;
int piano_flag = 0;

//piano
uint16_t note[7] = {523,587,659,698,784,880,988};
int pwmF;


//adc value
// when it is bright value is around 3600
// when it is dark value is around 2250
//adc_range = adc_max-adc_min;
//adc_unit_range = adc_range/adc_level;

int adc_max = 3500;
int adc_min = 2300;
int adc_level = 8;
int adc_range;
int adc_unit_range;
uint16_t adcVal[2];

//temp humi
int temp_humi_flag = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int fputc (int ch, FILE *stream){
	HAL_UART_Transmit(&huart2,(uint8_t*)&ch,1,0xFFFF);
	return ch;
}

void container_Inti(){
	for(int i = 0; i<20;i++){
		rx_data_container[i] = NULL;
	}
}
void rxBuffer_Inti(){
	for(int i = 0; i<20;i++){
		rx_buffer[i] = NULL;
	}
}
void LED_Init(){
	
	if(strcmp(rx_buffer,"led ona") == 0){
		HAL_GPIO_WritePin(GPIOC, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin,1); 
		HAL_Delay(500);

	}
	
	if(strcmp(rx_buffer,"led offa") == 0){
		HAL_GPIO_WritePin(GPIOC, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin,0); 
		HAL_Delay(500);
	}
	
	if(strcmp(rx_buffer,"led shifta") == 0){
		while(1){
			for(int i = 0; i < 8; i++){
				HAL_GPIO_WritePin(GPIOC, LED0_Pin << i,1);
				HAL_Delay(300);
				HAL_GPIO_WritePin(GPIOC, LED0_Pin << i,0);}
		if(strcmp(rx_buffer,"shift offa") == 0) {;break;}
		
		HAL_Delay(500);
	}
	}
	
	if(strcmp(rx_buffer,"reverse led shifta") == 0){
		while(1){
			for(int i = 0; i < 8; i++){
				HAL_GPIO_WritePin(GPIOC, LED0_Pin << (7-i),1);
				HAL_Delay(300);
				HAL_GPIO_WritePin(GPIOC, LED0_Pin << (7-i),0);}
		if(strcmp(rx_buffer,"shift offa") == 0) {break;}
		
		HAL_Delay(500);
	}
	}
	
}

void Moonlight_Init(){
	
	if(strcmp(rx_buffer,"moonlight ona") == 0){
		for (int i = 0; i <51;i++){
			TIM3->CCR1 = i*2;
			HAL_Delay(40);
		}
		for (int i = 0; i <51;i++){
			TIM3->CCR1 = (100-i*2);
			HAL_Delay(40);
		}
	}
}

void Piano_Init(){
	if(strcmp(rx_buffer,"piano ona") == 0){
		while(1){
			HAL_Delay(10);
			if ((rx_data == '1') && (piano_flag == 0)){pwmF = 1000000 / note[0];TIM4->ARR = pwmF -1;
			TIM4->CCR1 = pwmF/2;HAL_Delay(200);piano_flag = 1- piano_flag;}
			
			if ((rx_data == '2') && (piano_flag == 0)){pwmF = 1000000 / note[1];TIM4->ARR = pwmF -1;
			TIM4->CCR1 = pwmF/2;HAL_Delay(200);piano_flag = 1- piano_flag;}
			
			if ((rx_data == '3') && (piano_flag == 0)){pwmF = 1000000 / note[2];TIM4->ARR = pwmF -1;
			TIM4->CCR1 = pwmF/2;HAL_Delay(200);piano_flag = 1- piano_flag;}
			
			if ((rx_data == '4') && (piano_flag == 0)){pwmF = 1000000 / note[3];TIM4->ARR = pwmF -1;
			TIM4->CCR1 = pwmF/2;HAL_Delay(200);piano_flag = 1- piano_flag;}
			
			if ((rx_data == '5') && (piano_flag == 0)){pwmF = 1000000 / note[4];TIM4->ARR = pwmF -1;
			TIM4->CCR1 = pwmF/2;HAL_Delay(200);piano_flag = 1- piano_flag;}
			
			if ((rx_data == '6') && (piano_flag == 0)){pwmF = 1000000 / note[5];TIM4->ARR = pwmF -1;
			TIM4->CCR1 = pwmF/2;HAL_Delay(200);piano_flag = 1- piano_flag;}
			
			if ((rx_data == '7') && (piano_flag == 0)){pwmF = 1000000 / note[6];TIM4->ARR = pwmF -1;
			TIM4->CCR1 = pwmF/2;HAL_Delay(200);piano_flag = 1- piano_flag;}
			
			if (piano_flag == 1){TIM4->CCR1 = 0;}
			if(strcmp(rx_buffer,"piano offa") == 0){
				TIM4->CCR1 = 0;
				break;
			}
			HAL_Delay(10);
		}
	
	
	}
	
}







void Streetlight_Init(){
	if(strcmp(rx_buffer,"street light ona") == 0){
		while(1){
			if(adcVal[0] <= (adc_max-(adc_unit_range*1))) HAL_GPIO_WritePin(GPIOC, LED0_Pin,1);
			if(adcVal[0] <= (adc_max-(adc_unit_range*2))) HAL_GPIO_WritePin(GPIOC, LED1_Pin,1);
			if(adcVal[0] <= (adc_max-(adc_unit_range*3))) HAL_GPIO_WritePin(GPIOC, LED2_Pin,1);
			if(adcVal[0] <= (adc_max-(adc_unit_range*4))) HAL_GPIO_WritePin(GPIOC, LED3_Pin,1);

			if(adcVal[0] <= (adc_max-(adc_unit_range*5))) HAL_GPIO_WritePin(GPIOC, LED4_Pin,1);
			if(adcVal[0] <= (adc_max-(adc_unit_range*6))) HAL_GPIO_WritePin(GPIOC, LED5_Pin,1);
			if(adcVal[0] <= (adc_max-(adc_unit_range*7))) HAL_GPIO_WritePin(GPIOC, LED6_Pin,1);
			if(adcVal[0] <= (adc_max-(adc_unit_range*8))) HAL_GPIO_WritePin(GPIOC, LED7_Pin,1);
			HAL_Delay(10);
			
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_All,0);
			if(strcmp(rx_buffer,"street light offa") == 0){break;}
			
		}
	}
	
}
float SHT20(int);
void temp_humi_Init(){
	if(strcmp(rx_buffer,"temperaturea") == 0){
		HAL_Delay(500);
		float result;
		result = SHT20(TEMP); 
		printf("temperature >> %.1f celsius degree\n\r", result);
		rxBuffer_Inti();
	}
			
	if(strcmp(rx_buffer,"humiditya") == 0){
		HAL_Delay(500);
		float result;
		result = SHT20(HUMI); 
		printf("humidity >> %.1f %%\n\r", result);
		rxBuffer_Inti();
	}
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
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart2,&rx_data, 1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	TIM3->PSC = 84 -1;
	TIM3->ARR = 100 -1;

	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	TIM4->PSC = 84-1; //1,000,000 Mz
	
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcVal, 2);
	adc_range = adc_max-adc_min;
	adc_unit_range = adc_range/adc_level;
	
	HAL_I2C_Master_Transmit(&hi2c1,SHT20_ADDR,(uint8_t *)SHT20_SOFT_RESET,1, 0xFFFF);

	printf("=========EMBEDDED SYSTEM PROJECT=========\n\r");
	printf("Type one of command listed below to start\n\r");
	printf("1. led on/off, (reverse) led shift/shift off\n\r");
	printf("2. moonlight on\n\r");
	printf("3. piano on/off\n\r");
	printf("4. street light on/off\n\r");
	printf("5. temperature/humidity\n\r");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_Delay(500);

		LED_Init();
		Moonlight_Init();
    Piano_Init();
		Streetlight_Init();
		temp_humi_Init();

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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		HAL_UART_Receive_IT(&huart2,&rx_data, 1);
		if(piano_flag == 1){piano_flag = 0;} //making piano note short
		if(temp_humi_flag == 1){temp_humi_flag = 0;}
		if(rx_data == '\r'){
			
			for(int i = 0; i<cnt;i++){HAL_UART_Transmit(&huart2, &BP,1,0xFFFF);}
			for(int i = 0; i<cnt;i++){HAL_UART_Transmit(&huart2, &Blank,1,0xFFFF);}
			//for(int i = 0; i<cnt;i++){HAL_UART_Transmit(&huart2, &BP,1,0xFFFF);}
			HAL_UART_Transmit(&huart2, &Return_r,1,0xFFFF);

			//for (int init_rx = cnt; init_rx<=strlen(rx_data_container);init_rx++){
			rx_data_container[cnt] = 'a';
			memmove(rx_buffer,rx_data_container,20);
			container_Inti();
			//}
			cnt = 0;
		}else if(rx_data == 0b01111111){
			cnt--;
			rx_data_container[cnt] = NULL;
			HAL_UART_Transmit(&huart2, &BP,1,0xFFFF);
			HAL_UART_Transmit(&huart2, &Blank,1,0xFFFF);
			HAL_UART_Transmit(&huart2, &BP,1,0xFFFF);
			
		}else if(rx_data != '\r'){
			rx_data_container[cnt] = rx_data;
			printf("%c", rx_data_container[cnt]);
			cnt++;
			
		}
		//printf("%s\n\r", rx_data_container);
	}
	//HAL_UART_Transmit(&huart2,&rx_data, 1, 0xFFFF);
}
float SHT20(int selector){
	
	uint8_t I2c_data[3];
	uint16_t received_data;
	float TBR_data;

	
	if (selector == 0){ //TEMP = 0
		I2c_data[0] = SHT20_TRG_NHM_T;
		HAL_I2C_Master_Transmit(&hi2c1, SHT20_ADDR, I2c_data,1,0xFFFF);
		HAL_Delay(100);
		HAL_I2C_Master_Receive(&hi2c1, SHT20_ADDR, I2c_data,2, 0xFFFF);
		received_data = (I2c_data[0]<<8)|I2c_data[1];
		TBR_data = -46.85 +175.72 *((float)received_data/65536);
		return TBR_data;
		
	}else if (selector == 1){ //HUMI = 1
		I2c_data[0] = SHT20_TRG_NHM_RH;
		HAL_I2C_Master_Transmit(&hi2c1, SHT20_ADDR, I2c_data, 1, 0xFFFF);
		HAL_Delay(100);
		HAL_I2C_Master_Receive(&hi2c1, SHT20_ADDR, I2c_data, 1, 0xFFFF);
		received_data = (I2c_data[0]<<8)|I2c_data[1];
		TBR_data = -6 + 125.0*((float)received_data/65536);
		return TBR_data;
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
