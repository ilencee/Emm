#include "tm1616_port_8bit.h"

/**
 * @brief  8位单片机平台GPIO初始化
 * @note   此函数仅在使用8位单片机时调用
 * @note   51系列单片机的IO口上电默认为高电平，通常不需要额外初始化
 *         如需配置IO方向寄存器，请在此函数中添加
 */
void TM1616_Port_Init(void)
{
    /* 
     * 对于51系列单片机，IO口默认就是准双向口，无需特别配置
     * 如果需要配置其他8位MCU的IO方向寄存器，请在此添加代码
     * 
     * 示例（AVR）:
     * TM1616_CLK_DDR |= (1 << TM1616_CLK_PIN);
     * TM1616_DIN_DDR |= (1 << TM1616_DIN_PIN);
     * TM1616_STB_DDR |= (1 << TM1616_STB_PIN);
     */

    /* 初始状态：全部高电平 */
    TM1616_CLK_HIGH();
    TM1616_DIN_HIGH();
    TM1616_STB_HIGH();
}
