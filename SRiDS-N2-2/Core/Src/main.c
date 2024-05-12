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
#include "usbd_custom_hid_if.h"
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
extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  uint8_t tipkovnica[9]={0};
  GPIO_PinState lastButtonState = GPIO_PIN_RESET;
  int counter = 0;

  void printChar(USBD_HandleTypeDef hUsbDeviceFS, int Code, int Modifier){
	  tipkovnica[0] = Modifier;
	  tipkovnica[4] = Code;

	  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, tipkovnica, 8);

	  HAL_Delay(100);

	  // spustimo tipko
	  tipkovnica[0] = 0;
	  tipkovnica[4] = 0;

	  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, tipkovnica, 8);

	  HAL_Delay(175);
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  GPIO_PinState currentButtonState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	      	if (currentButtonState == GPIO_PIN_RESET && lastButtonState == GPIO_PIN_SET)
	      	{
	      		counter++;

	      		if(counter == 2){ //sodo
	      			// Shift = 0x02
	      			// AltGr = 0x04

	      			for(int i = 33;i<36;i++) // $%&
	      				printChar(hUsbDeviceFS, i, 0x02);

	      			printChar(hUsbDeviceFS, 0x2c, 0);
	      			printChar(hUsbDeviceFS, 0x37, 0x4);
	      			printChar(hUsbDeviceFS, 0x19, 0x4);
	      			printChar(hUsbDeviceFS, 0x36, 0x4);
	      			printChar(hUsbDeviceFS, 0x9, 0x4);
	      			printChar(hUsbDeviceFS, 0x14, 0x4);
	      			printChar(hUsbDeviceFS, 0xa, 0x4);
	      			printChar(hUsbDeviceFS, 0x21, 0x4);
	      			printChar(hUsbDeviceFS, 0x24, 0x4);
	      			printChar(hUsbDeviceFS, 0x5, 0x4);
	      			printChar(hUsbDeviceFS, 0x1a, 0x4);

	      			printChar(hUsbDeviceFS, 0x2D, 0); // '
      				printChar(hUsbDeviceFS, 37, 0x02); // (
      				printChar(hUsbDeviceFS, 38, 0x02); // )
      				printChar(hUsbDeviceFS, 0x2E, 0x02); // *
      				printChar(hUsbDeviceFS, 0x2E, 0); // +
      				printChar(hUsbDeviceFS, 0x36, 0); // ,
      				printChar(hUsbDeviceFS, 0x2C, 0); // space
      				printChar(hUsbDeviceFS, 0x38, 0); // -
      				printChar(hUsbDeviceFS, 0x37, 0); // .
      				printChar(hUsbDeviceFS, 36, 0x02); // /

	      			printChar(hUsbDeviceFS, 39, 0); // 0
	      			for(int i = 30;i<39;i++) // 1-9
	      				printChar(hUsbDeviceFS, i, 0);

      				printChar(hUsbDeviceFS, 0x37, 0x02); // :
      				printChar(hUsbDeviceFS, 0x36, 0x02); // ;

      				printChar(hUsbDeviceFS, 0x36, 0x04); // <
      				printChar(hUsbDeviceFS, 39, 0x02); // =
      				printChar(hUsbDeviceFS, 0x37, 0x04); // >

      				printChar(hUsbDeviceFS, 0x2D, 0x02); // ?
      				printChar(hUsbDeviceFS, 25, 0x04); // @

	      			for(int i = 4;i<28;i++){ //A-Z
	      				printChar(hUsbDeviceFS, i, 0x02);
	      			}
	      			printChar(hUsbDeviceFS, 29, 0x02); // Y
	      			printChar(hUsbDeviceFS, 28, 0x02); // Z

      				printChar(hUsbDeviceFS, 9, 0x04); // F [
      				printChar(hUsbDeviceFS, 20, 0x04); // \.
      				printChar(hUsbDeviceFS, 10, 0x04); // G ]
      				printChar(hUsbDeviceFS, 33, 0x04); // ^
      				printChar(hUsbDeviceFS, 0x38, 0x02); // _
      				printChar(hUsbDeviceFS, 36, 0x04); // `

	      			for(int i = 4;i<28;i++){ //a-z
	      				printChar(hUsbDeviceFS, i, 0);
	      			}
	      			printChar(hUsbDeviceFS, 29, 0); // y
	      			printChar(hUsbDeviceFS, 28, 0); // z

      				printChar(hUsbDeviceFS, 5, 0x04); // b {
      				printChar(hUsbDeviceFS, 26, 0x04); // |

      				//printChar(hUsbDeviceFS, 17, 0x04); // n }

	      			break;
	      		}else if(counter == 1){ //liho

	      			int nums[] = {0x1F, 0x24, 0x20, 0x1E, 0x1F};

	      			for(int i = 0;i<5;i++){
	      				// pritisnemo tipko
	      				tipkovnica[4] = nums[i];

	      				USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, tipkovnica, 8);

	      				HAL_Delay(100);

	      				// spustimo tipko
	      				tipkovnica[4] = 0;

	      				USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, tipkovnica, 8);

	      				HAL_Delay(175);
	      			}
	      		}

	      		lastButtonState = currentButtonState;
	      	}else{
	      		lastButtonState = currentButtonState;
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
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
