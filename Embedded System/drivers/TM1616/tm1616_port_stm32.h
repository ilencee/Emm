#ifndef TM1616_PORT_STM32_H
#define TM1616_PORT_STM32_H

#include "type_def.h"

/* 
 * STM32系列32位单片机端口配置
 * 适用于: STM32F1/F4/H7等使用HAL库的MCU
 */

/* ==================== 引脚配置 - 根据实际硬件修改 ==================== */
#define TM1616_CLK_PORT     GPIOA
#define TM1616_CLK_PIN      GPIO_PIN_0

#define TM1616_DIN_PORT     GPIOA
#define TM1616_DIN_PIN      GPIO_PIN_1

#define TM1616_STB_PORT     GPIOA
#define TM1616_STB_PIN      GPIO_PIN_2

/* ==================== HAL库操作宏 ==================== */
#define TM1616_CLK_HIGH()   HAL_GPIO_WritePin(TM1616_CLK_PORT, TM1616_CLK_PIN, GPIO_PIN_SET)
#define TM1616_CLK_LOW()    HAL_GPIO_WritePin(TM1616_CLK_PORT, TM1616_CLK_PIN, GPIO_PIN_RESET)

#define TM1616_DIN_HIGH()   HAL_GPIO_WritePin(TM1616_DIN_PORT, TM1616_DIN_PIN, GPIO_PIN_SET)
#define TM1616_DIN_LOW()    HAL_GPIO_WritePin(TM1616_DIN_PORT, TM1616_DIN_PIN, GPIO_PIN_RESET)

#define TM1616_STB_HIGH()   HAL_GPIO_WritePin(TM1616_STB_PORT, TM1616_STB_PIN, GPIO_PIN_SET)
#define TM1616_STB_LOW()    HAL_GPIO_WritePin(TM1616_STB_PORT, TM1616_STB_PIN, GPIO_PIN_RESET)

/* ==================== STM32专用函数声明 ==================== */
void TM1616_Port_Init(void);

#endif /* TM1616_PORT_STM32_H */
