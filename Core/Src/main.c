/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "User/button.h"
#include "User/software_timer.h"
#include "User/led_7seg.h"
#include "User/traffic_light_3color.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
Button_t button1 =
{
	.FILTER_DELAY_COUNT_MAX = 3,
	.HOLD_STATE_DELAY_COUNT_MAX = 50,
	.HOLD_STATE_ACTIVATE_COUNT_MAX = 50,
	.READING_WHEN_PRESSED = GPIO_PIN_RESET,
	.PIN = BUTTON_Pin,
	.PORT = BUTTON_GPIO_Port,

	.current_state = BUTTON_IS_RELEASED,
};

Software_timer_t timer_update_7seg =
{
	.timer_counter = 0,
	.timer_flag = TIMER_FLAG_RESET,
};

Software_timer_t timer_traffic_light =
{
	.timer_counter = 0,
	.timer_flag = TIMER_FLAG_RESET,
};

Two_digit_7seg_t two_digit_7seg =
{
	.CONTROL_PIN = { CONTROL_7SEG_0_Pin, CONTROL_7SEG_1_Pin },
	.CONTROL_PORT = { CONTROL_7SEG_0_GPIO_Port, CONTROL_7SEG_1_GPIO_Port },

	.digit_value = { 9 , 6 },
};

Traffic_light_t traffic_light =
{
	.TRAFFIC_LIGHT_PIN =
	{
		TRAFFIC_LIGHT_RED_Pin,
		TRAFFIC_LIGHT_YELLOW_Pin,
		TRAFFIC_LIGHT_GREEN_Pin
	},
	.TRAFFIC_LIGHT_PORT =
	{
		TRAFFIC_LIGHT_RED_GPIO_Port,
		TRAFFIC_LIGHT_YELLOW_GPIO_Port,
		TRAFFIC_LIGHT_GREEN_GPIO_Port
	},
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	const int update_7seg_period_ms = 200;
	const int each_traffic_light_color_period_ms = 1000;

	uint8_t count_value = 0;
	uint8_t current_7seg_digit = 0;
	Traffic_light_color_t color = TRAFFIC_LIGHT_COLOR_RED;

	software_timer_set_duration_ms(&timer_update_7seg, update_7seg_period_ms);
	software_timer_set_duration_ms(&timer_traffic_light, each_traffic_light_color_period_ms);

	while (1)
	{
		if (software_timer_is_set(&timer_update_7seg))
		{
			software_timer_set_duration_ms(&timer_update_7seg, update_7seg_period_ms);

			two_digit_7seg_display_digit(&two_digit_7seg, current_7seg_digit);
			current_7seg_digit = (current_7seg_digit == 0) ? 1 : 0;
		}

		if (software_timer_is_set(&timer_traffic_light))
		{
			software_timer_set_duration_ms(&timer_traffic_light, each_traffic_light_color_period_ms);
			color = (color + 1) % TRAFFIC_LIGHT_COLOR_NUMBER;

			traffic_light_turn_on_one_color(&traffic_light, color);
		}

		if (button_is_pressed_activated(&button1))
		{
			count_value++;
			two_digit_7seg_update_value(&two_digit_7seg, count_value);
			button_clear_activation(&button1);
		}

		if (button_is_hold_activated(&button1))
		{
			count_value++;
			two_digit_7seg_update_value(&two_digit_7seg, count_value);
			button_clear_activation(&button1);
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8000 - 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10 - 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin|CONTROL_7SEG_0_Pin
                          |CONTROL_7SEG_1_Pin|TRAFFIC_LIGHT_RED_Pin|TRAFFIC_LIGHT_YELLOW_Pin|TRAFFIC_LIGHT_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin SEG3_Pin
                           SEG4_Pin SEG5_Pin SEG6_Pin CONTROL_7SEG_0_Pin
                           CONTROL_7SEG_1_Pin TRAFFIC_LIGHT_RED_Pin TRAFFIC_LIGHT_YELLOW_Pin TRAFFIC_LIGHT_GREEN_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin|CONTROL_7SEG_0_Pin
                          |CONTROL_7SEG_1_Pin|TRAFFIC_LIGHT_RED_Pin|TRAFFIC_LIGHT_YELLOW_Pin|TRAFFIC_LIGHT_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// this function run every 10ms due to timer 2 update
	if (htim->Instance == TIM2)
	{
		software_timer_update_after_tick(&timer_update_7seg);
		software_timer_update_after_tick(&timer_traffic_light);
		button_poll_and_update_state(&button1);
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
