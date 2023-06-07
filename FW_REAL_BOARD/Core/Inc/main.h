/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PORTS_SER_Pin GPIO_PIN_2
#define PORTS_SER_GPIO_Port GPIOE
#define PORTS_OE_Pin GPIO_PIN_3
#define PORTS_OE_GPIO_Port GPIOE
#define PORTS_RCLK_Pin GPIO_PIN_4
#define PORTS_RCLK_GPIO_Port GPIOE
#define PORTS_SRCLK_Pin GPIO_PIN_5
#define PORTS_SRCLK_GPIO_Port GPIOE
#define PORTS_SRCLR_Pin GPIO_PIN_6
#define PORTS_SRCLR_GPIO_Port GPIOE
#define PMOS_SHFT_1TO5_RCLK_Pin GPIO_PIN_14
#define PMOS_SHFT_1TO5_RCLK_GPIO_Port GPIOC
#define PMOS_SHFT_1TO5_NOE_Pin GPIO_PIN_15
#define PMOS_SHFT_1TO5_NOE_GPIO_Port GPIOC
#define I2C_EEPROM_SDA_Pin GPIO_PIN_0
#define I2C_EEPROM_SDA_GPIO_Port GPIOF
#define I2C_EEPROM_SCL_Pin GPIO_PIN_1
#define I2C_EEPROM_SCL_GPIO_Port GPIOF
#define PMOS_SHFT_1TO5_SRCLK_Pin GPIO_PIN_2
#define PMOS_SHFT_1TO5_SRCLK_GPIO_Port GPIOF
#define PMOS_SHFT_1TO5_SER_Pin GPIO_PIN_5
#define PMOS_SHFT_1TO5_SER_GPIO_Port GPIOF
#define ADC_CH_4_Pin GPIO_PIN_6
#define ADC_CH_4_GPIO_Port GPIOF
#define EEPROM_WP_Pin GPIO_PIN_8
#define EEPROM_WP_GPIO_Port GPIOF
#define MUX_D9_Pin GPIO_PIN_0
#define MUX_D9_GPIO_Port GPIOC
#define V_pin_sense1_Pin GPIO_PIN_0
#define V_pin_sense1_GPIO_Port GPIOA
#define ADC_CH_3_Pin GPIO_PIN_3
#define ADC_CH_3_GPIO_Port GPIOA
#define MUX_D6_Pin GPIO_PIN_6
#define MUX_D6_GPIO_Port GPIOA
#define MUX_D8_Pin GPIO_PIN_0
#define MUX_D8_GPIO_Port GPIOB
#define MUX_D7_Pin GPIO_PIN_1
#define MUX_D7_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define MUX_D10_Pin GPIO_PIN_11
#define MUX_D10_GPIO_Port GPIOF
#define OPTO_OUTPUT_Pin GPIO_PIN_12
#define OPTO_OUTPUT_GPIO_Port GPIOF
#define MUXes_6to10_nEN_Pin GPIO_PIN_14
#define MUXes_6to10_nEN_GPIO_Port GPIOF
#define MUXes_6to10_A0_Pin GPIO_PIN_0
#define MUXes_6to10_A0_GPIO_Port GPIOG
#define MUXes_6to10_A1_Pin GPIO_PIN_1
#define MUXes_6to10_A1_GPIO_Port GPIOG
#define MUXes_6to10_A2_Pin GPIO_PIN_7
#define MUXes_6to10_A2_GPIO_Port GPIOE
#define OPTO_MUX_D_Pin GPIO_PIN_11
#define OPTO_MUX_D_GPIO_Port GPIOE
#define OPTO_MUX_EN_Pin GPIO_PIN_12
#define OPTO_MUX_EN_GPIO_Port GPIOE
#define OPTO_MUX_A2_Pin GPIO_PIN_13
#define OPTO_MUX_A2_GPIO_Port GPIOE
#define OPTO_MUX_A1_Pin GPIO_PIN_14
#define OPTO_MUX_A1_GPIO_Port GPIOE
#define OPTO_MUX_A0_Pin GPIO_PIN_15
#define OPTO_MUX_A0_GPIO_Port GPIOE
#define NMOS_SHFT_6TO10_NOE_Pin GPIO_PIN_14
#define NMOS_SHFT_6TO10_NOE_GPIO_Port GPIOB
#define NMOS_SHFT_6TO10_SER_Pin GPIO_PIN_15
#define NMOS_SHFT_6TO10_SER_GPIO_Port GPIOB
#define NMOS_SHFT_6TO10_RCLK_Pin GPIO_PIN_8
#define NMOS_SHFT_6TO10_RCLK_GPIO_Port GPIOD
#define NMOS_SHFT_6TO10_SRCLK_Pin GPIO_PIN_9
#define NMOS_SHFT_6TO10_SRCLK_GPIO_Port GPIOD
#define NMOS_SHFT_6TO10_SRCLR_Pin GPIO_PIN_10
#define NMOS_SHFT_6TO10_SRCLR_GPIO_Port GPIOD
#define PMOS_SHFT_6TO10_SER_Pin GPIO_PIN_11
#define PMOS_SHFT_6TO10_SER_GPIO_Port GPIOD
#define PMOS_SHFT_6TO10_NOE_Pin GPIO_PIN_12
#define PMOS_SHFT_6TO10_NOE_GPIO_Port GPIOD
#define PMOS_SHFT_6TO10_RCLK_Pin GPIO_PIN_13
#define PMOS_SHFT_6TO10_RCLK_GPIO_Port GPIOD
#define P5V_en_Pin GPIO_PIN_14
#define P5V_en_GPIO_Port GPIOD
#define P3V_en_Pin GPIO_PIN_15
#define P3V_en_GPIO_Port GPIOD
#define PMOS_SHFT_6TO10_SRCLK_Pin GPIO_PIN_2
#define PMOS_SHFT_6TO10_SRCLK_GPIO_Port GPIOG
#define PMOS_SHFT_6TO10_SRCLR_Pin GPIO_PIN_3
#define PMOS_SHFT_6TO10_SRCLR_GPIO_Port GPIOG
#define MUX_D5_Pin GPIO_PIN_4
#define MUX_D5_GPIO_Port GPIOG
#define MUX_D4_Pin GPIO_PIN_5
#define MUX_D4_GPIO_Port GPIOG
#define MUX_D3_Pin GPIO_PIN_6
#define MUX_D3_GPIO_Port GPIOG
#define MUX_D2_Pin GPIO_PIN_7
#define MUX_D2_GPIO_Port GPIOG
#define MUX_D1_Pin GPIO_PIN_8
#define MUX_D1_GPIO_Port GPIOG
#define MUXes_1to5_A0_Pin GPIO_PIN_6
#define MUXes_1to5_A0_GPIO_Port GPIOC
#define MUXes_1to5_nEN_Pin GPIO_PIN_7
#define MUXes_1to5_nEN_GPIO_Port GPIOC
#define MUXes_1to5_A1_Pin GPIO_PIN_8
#define MUXes_1to5_A1_GPIO_Port GPIOC
#define MUXes_1to5_A2_Pin GPIO_PIN_9
#define MUXes_1to5_A2_GPIO_Port GPIOC
#define NMOS_SHFT_1TO5_NOE_Pin GPIO_PIN_15
#define NMOS_SHFT_1TO5_NOE_GPIO_Port GPIOA
#define NMOS_SHFT_1TO5_SER_Pin GPIO_PIN_10
#define NMOS_SHFT_1TO5_SER_GPIO_Port GPIOC
#define NMOS_SHFT_1TO5_RCLK_Pin GPIO_PIN_11
#define NMOS_SHFT_1TO5_RCLK_GPIO_Port GPIOC
#define NMOS_SHFT_1TO5_SRCLK_Pin GPIO_PIN_12
#define NMOS_SHFT_1TO5_SRCLK_GPIO_Port GPIOC
#define NMOS_SHFT_1TO5_SRCLR_Pin GPIO_PIN_2
#define NMOS_SHFT_1TO5_SRCLR_GPIO_Port GPIOD
#define PMOS_SHFT_1TO5_SRCLR_Pin GPIO_PIN_5
#define PMOS_SHFT_1TO5_SRCLR_GPIO_Port GPIOB
#define STATUS_LED_Pin GPIO_PIN_1
#define STATUS_LED_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
