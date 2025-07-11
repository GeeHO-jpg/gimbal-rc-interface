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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32g0xx_it.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// uint32_t value[3];
 float setpoint[3];
// volatile uint32_t rc_rise_time[3] = {0};       // สำหรับ TIM_CHANNEL_2/3/4
// volatile uint32_t rc_pulse_width[3] = {1500, 1500, 1500};  // ค่า default ~ 1500 us (center)

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
/* USER CODE BEGIN PFP */
float rc_us_to_normalized(uint32_t pulse_us);
float rc_us_to_angle(uint32_t pulse_us, float max_angle_deg);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//uint32_t IC_Val1,IC_Val2,Difference = 0;
//int Is_First_capture = 0;

/* Measure Frequency */

//float frequency = 0;
//
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
//	{
//		if(Is_First_capture == 0)
//		{
//			IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
//			Is_First_capture =1;
//		}
//		else
//		{
//			IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
//			if(IC_Val2 > IC_Val1)
//			{
//				Difference = IC_Val2 - IC_Val1;
//			}
//			else if(IC_Val1 > IC_Val2)
//			{
//				Difference = (0xffffffff - IC_Val1)+IC_Val2;
//			}
//			float refClock =CLK/PRESCALE;
//
//			frequency = refClock/Difference;
//
//			__HAL_TIM_SET_COUNTER(htim,0); //reset the counter
//			Is_First_capture=0;
//		}
//	}
//}

/* Measure Width */

//float usWidth = 1500;
//
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
//	{
//		if(Is_First_capture == 0)
//		{
//			IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
//			Is_First_capture =1;
//		}
//		else
//		{
//			IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
//			if(IC_Val2 > IC_Val1)
//			{
//				Difference = IC_Val2 - IC_Val1;
//			}
//			else if(IC_Val1 > IC_Val2)
//			{
//				Difference = (htim->Init.Period  - IC_Val1)+IC_Val2;
//			}
//			float refClock =CLK/PRESCALE;
//			float mFactor = 1000000/refClock;
//
//
//
//			usWidth = Difference*mFactor;
//
//
//			__HAL_TIM_SET_COUNTER(htim,0);
//			Is_First_capture=0;
//		}
//	}
//}

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
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
//  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);  // ใช้กับ RC ch2
//  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);  // ใช้กับ RC ch3
//  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);  // ใช้กับ RC ch4
  TIM1->CCR1 = 20;
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  setpoint[0] = rc_us_to_angle(usWidth[0], 45);
	  setpoint[1] = rc_us_to_angle(usWidth[1], 45);
	  setpoint[2] = rc_us_to_angle(usWidth[2], 45);
	  HAL_Delay(500);
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
float rc_us_to_normalized(uint32_t pulse_us) {
    // แปลง 1000–2000us → -1.0 ถึง +1.0
    float value = ((int)pulse_us - 1500) / 500.0f;
    if (value > 1.0f) value = 1.0f;
    if (value < -1.0f) value = -1.0f;
    return value;
}


float rc_us_to_angle(uint32_t pulse_us, float max_angle_deg) {
    return rc_us_to_normalized(pulse_us) * max_angle_deg;
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
