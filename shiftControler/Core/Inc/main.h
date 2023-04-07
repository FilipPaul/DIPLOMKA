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
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define NMOS_SHFT_1TO5_SRCLK_Pin GPIO_PIN_3
#define NMOS_SHFT_1TO5_SRCLK_GPIO_Port GPIOF
#define NMOS_SHFT_1TO5_SRCLR_Pin GPIO_PIN_5
#define NMOS_SHFT_1TO5_SRCLR_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define NMOS_SHFT_1TO5_NOE_Pin GPIO_PIN_0
#define NMOS_SHFT_1TO5_NOE_GPIO_Port GPIOC
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define NMOS_SHFT_1TO5_RCLK_Pin GPIO_PIN_3
#define NMOS_SHFT_1TO5_RCLK_GPIO_Port GPIOC
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define NMOS_SHFT_1TO5_SER_Pin GPIO_PIN_3
#define NMOS_SHFT_1TO5_SER_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define MUX_A0_Pin GPIO_PIN_12
#define MUX_A0_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define MUX_A1_Pin GPIO_PIN_15
#define MUX_A1_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define NMOS_SHFT_6TO10_RCLK_Pin GPIO_PIN_10
#define NMOS_SHFT_6TO10_RCLK_GPIO_Port GPIOD
#define NMOS_SHFT_6TO10_SRCLR_Pin GPIO_PIN_11
#define NMOS_SHFT_6TO10_SRCLR_GPIO_Port GPIOD
#define NMOS_SHFT_6TO10_SRCLK_Pin GPIO_PIN_12
#define NMOS_SHFT_6TO10_SRCLK_GPIO_Port GPIOD
#define NMOS_SHFT_6TO10_SER_Pin GPIO_PIN_13
#define NMOS_SHFT_6TO10_SER_GPIO_Port GPIOD
#define NMOS_SHFT_6TO10_NOE_Pin GPIO_PIN_14
#define NMOS_SHFT_6TO10_NOE_GPIO_Port GPIOD
#define PMOS_SHFT_6TO10_RCLK_Pin GPIO_PIN_15
#define PMOS_SHFT_6TO10_RCLK_GPIO_Port GPIOD
#define PMOS_SHFT_6TO10_SRCLR_Pin GPIO_PIN_2
#define PMOS_SHFT_6TO10_SRCLR_GPIO_Port GPIOG
#define PMOS_SHFT_6TO10_SRCLK_Pin GPIO_PIN_3
#define PMOS_SHFT_6TO10_SRCLK_GPIO_Port GPIOG
#define PMOS_SHFT_6TO10_SER_Pin GPIO_PIN_4
#define PMOS_SHFT_6TO10_SER_GPIO_Port GPIOG
#define PMOS_SHFT_6TO10_NOE_Pin GPIO_PIN_5
#define PMOS_SHFT_6TO10_NOE_GPIO_Port GPIOG
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define MUX_A2_Pin GPIO_PIN_6
#define MUX_A2_GPIO_Port GPIOC
#define MUX_D1_Pin GPIO_PIN_7
#define MUX_D1_GPIO_Port GPIOC
#define PMOS_SHFT_1TO5_SER_Pin GPIO_PIN_8
#define PMOS_SHFT_1TO5_SER_GPIO_Port GPIOC
#define PMOS_SHFT_1TO5_NOE_Pin GPIO_PIN_9
#define PMOS_SHFT_1TO5_NOE_GPIO_Port GPIOC
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define MUX_nOE_Pin GPIO_PIN_15
#define MUX_nOE_GPIO_Port GPIOA
#define PMOS_SHFT_1TO5_RCLK_Pin GPIO_PIN_10
#define PMOS_SHFT_1TO5_RCLK_GPIO_Port GPIOC
#define PMOS_SHFT_1TO5_SRCLK_Pin GPIO_PIN_11
#define PMOS_SHFT_1TO5_SRCLK_GPIO_Port GPIOC
#define PMOS_SHFT_1TO5_SRCLR_Pin GPIO_PIN_12
#define PMOS_SHFT_1TO5_SRCLR_GPIO_Port GPIOC
#define MUX_D10_Pin GPIO_PIN_1
#define MUX_D10_GPIO_Port GPIOD
#define MUX_D9_Pin GPIO_PIN_2
#define MUX_D9_GPIO_Port GPIOD
#define MUX_D8_Pin GPIO_PIN_3
#define MUX_D8_GPIO_Port GPIOD
#define MUX_D7_Pin GPIO_PIN_4
#define MUX_D7_GPIO_Port GPIOD
#define MUX_D6_Pin GPIO_PIN_5
#define MUX_D6_GPIO_Port GPIOD
#define MUX2_A0_Pin GPIO_PIN_6
#define MUX2_A0_GPIO_Port GPIOD
#define MUX2_A1_Pin GPIO_PIN_7
#define MUX2_A1_GPIO_Port GPIOD
#define MUX2_A2_Pin GPIO_PIN_9
#define MUX2_A2_GPIO_Port GPIOG
#define MUX2_nOE_Pin GPIO_PIN_10
#define MUX2_nOE_GPIO_Port GPIOG
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define MUX_D3_Pin GPIO_PIN_3
#define MUX_D3_GPIO_Port GPIOB
#define MUX_D4_Pin GPIO_PIN_4
#define MUX_D4_GPIO_Port GPIOB
#define MUX_D2_Pin GPIO_PIN_5
#define MUX_D2_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define MUX_D5_Pin GPIO_PIN_8
#define MUX_D5_GPIO_Port GPIOB
#define TIMER_check_Pin GPIO_PIN_9
#define TIMER_check_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
