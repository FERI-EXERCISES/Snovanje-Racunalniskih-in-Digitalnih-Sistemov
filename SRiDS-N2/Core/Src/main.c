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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include <string.h>
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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t Animacija = 0;

void AddLEDStateToString(char* str, uint16_t LED_Pin, uint8_t ledIndex) {
    char ledOn[] = "LED_XX_ON ";
    char ledOff[] = "LED_XX_OFF ";
    char* stateString = HAL_GPIO_ReadPin(GPIOD, LED_Pin) == GPIO_PIN_SET ? ledOn : ledOff;

    // Zamenjaj XX z ustrezno številko pina
    stateString[4] = '1';
    stateString[5] = '2' + ledIndex;

    // Dodaj v skupni niz
    strcat(str, stateString);
}

void GetLEDState(char* statusString) {
    // Inicializiraj niz
    statusString[0] = '\0';

    // Dodaj stanje vsake LED
    AddLEDStateToString(statusString, GPIO_PIN_12, 0);
    AddLEDStateToString(statusString, GPIO_PIN_13, 1);
    AddLEDStateToString(statusString, GPIO_PIN_14, 2);
    AddLEDStateToString(statusString, GPIO_PIN_15, 3);

    statusString[strlen(statusString)-1] = '\0';
}

// Funkcija za obdelavo ukazov
void ProcessCommand(char* cmd) {
	char action[4];
	int pinNumber;

	if (strcmp(cmd, "LED_ON") == 0) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);
	} else if (strcmp(cmd, "LED_OFF") == 0) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
	} else if (sscanf(cmd, "LED_%2d_%3s", &pinNumber, action) == 2) {
		if (strcmp(action, "ON") == 0) {
			switch (pinNumber) {
				case 12:
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
					break;
				case 13:
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
					break;
				case 14:
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
					break;
				case 15:
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);
					break;
				default:
					CDC_Transmit_FS((uint8_t*)"ERROR", 5);
					break;
			}
		} else if (strcmp(action, "OFF") == 0) {
			switch (pinNumber) {
			case 12:
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
				break;
			case 13:
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
				break;
			case 14:
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
				break;
			case 15:
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
				break;
			default:
				CDC_Transmit_FS((uint8_t*)"ERROR", 5);
				break;
			}
		}
	} else if(strcmp(cmd, "STANJE") == 0){
		char statusString[500];
		GetLEDState(statusString);

		CDC_Transmit_FS((uint8_t*)statusString, strlen(statusString));
	}else if(strcmp(cmd, "ANIMACIJA_ON") == 0){
		Animacija = 1;
	} else if(strcmp(cmd, "ANIMACIJA_OFF") == 0){
		Animacija = 0;
	} else if(strcmp(cmd, "HELP") == 0){
		const char helpMessage[] =
		        "LED_ON - vklopi vse LED diode\n"
		        "LED_OFF - izklopi vse LED diode\n"
		        "LED_XX_ON - vklopi specificno LED diodo (XX = stevilka pina)\n"
		        "LED_XX_OFF - izklopi specificno LED diodo (XX = stevilka pina)\n"
		        "STANJE - izpise trenutno stanje vseh LED diod\n"
		        "ANIMACIJA_ON - zacne animacijo LED diod\n"
		        "ANIMACIJA_OFF - konca animacijo LED diod\n\n";

		    CDC_Transmit_FS((uint8_t*)helpMessage, strlen(helpMessage));
	} else{
		CDC_Transmit_FS((uint8_t*)"ERROR", 5);
		return;
	}
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
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t counter = 0;

    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    	if(Animacija == 1){
    		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, (counter >> 0) & 1);
    		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, (counter >> 1) & 1);
    		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, (counter >> 2) & 1);
    		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, (counter >> 3) & 1);
    		counter++;
    		HAL_Delay(1000);
    	}else if(Animacija == 0){
    		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
   			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
 			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
   			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
   			counter = 0;
   			Animacija = 2;
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
  RCC_OscInitStruct.PLL.PLLN = 192;
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
