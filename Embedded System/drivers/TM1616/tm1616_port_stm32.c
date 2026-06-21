#include "tm1616_port_stm32.h"

/**
 * @brief  STM32平台GPIO初始化
 * @note   此函数仅在使用STM32时调用
 */
void TM1616_Port_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* 使能 GPIO 时钟 */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* 配置引脚为推挽输出 */
    GPIO_InitStruct.Pin = TM1616_CLK_PIN | TM1616_DIN_PIN | TM1616_STB_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* 初始状态：全部高电平 */
    TM1616_CLK_HIGH();
    TM1616_DIN_HIGH();
    TM1616_STB_HIGH();
}
