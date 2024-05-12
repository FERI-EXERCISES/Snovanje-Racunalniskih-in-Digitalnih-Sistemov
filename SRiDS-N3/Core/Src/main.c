#include "stm32f4xx_hal.h"

#define DEBOUNCE_TIME 8
#define SHORT_PRESS_MIN 20
#define SHORT_PRESS_MAX 84
#define LONG_PRESS_MIN 250
#define LONG_PRESS_MAX 850

typedef enum {
  UNSTABLE,
  STABLE_SHORT,
  STABLE_LONG
} DebounceState;
DebounceState debounceState = UNSTABLE;
GPIO_InitTypeDef GPIO_InitStruct;
TIM_HandleTypeDef htim2;
uint8_t buttonState = GPIO_PIN_RESET;
uint8_t lastButtonState = GPIO_PIN_RESET;
uint32_t lastDebounceTime = 0;
uint32_t pressDuration = 0;

void SystemClock_Config(void);
void GPIO_Init(void);
void TIM2_Init(void);

int main(void) {
  HAL_Init();
  SystemClock_Config();

  GPIO_Init();
  TIM2_Init();
  while (1) {
    uint8_t currentButtonState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    if (currentButtonState != lastButtonState) {
      lastDebounceTime = HAL_GetTick();
    }

    if ((HAL_GetTick() - lastDebounceTime) > DEBOUNCE_TIME) {
      if (currentButtonState != buttonState) {
        buttonState = currentButtonState;

        if (buttonState == GPIO_PIN_SET) {
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
        } else {
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
          debounceState = UNSTABLE;
        }
      }
    }


    /*    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
        // Button is pressed
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET); // Wait for button release
        ledCombination = (ledCombination + 1) % 16; // Increment LED combination
    }
     * */

    if (buttonState == GPIO_PIN_SET) {
      pressDuration = HAL_GetTick() - lastDebounceTime;
      if (pressDuration >= SHORT_PRESS_MIN && pressDuration <= SHORT_PRESS_MAX && debounceState != STABLE_SHORT) {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
        debounceState = STABLE_SHORT;
      } else if (pressDuration >= LONG_PRESS_MIN && pressDuration <= LONG_PRESS_MAX && debounceState != STABLE_LONG) {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
        debounceState = STABLE_LONG;
      }
    }

    lastButtonState = currentButtonState;
  }
}




void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
  }
}

void GPIO_Init(void) {
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void TIM2_Init(void) {
  __HAL_RCC_TIM2_CLK_ENABLE();

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000; // 1ms
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
  }

  if (HAL_TIM_Base_Start(&htim2) != HAL_OK) {
  }
}
