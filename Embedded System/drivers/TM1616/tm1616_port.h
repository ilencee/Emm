#ifndef TM1616_PORT_H
#define TM1616_PORT_H

/* 
 * TM1616 硬件端口适配层 - 平台选择入口
 * 
 * 使用方法:
 * 1. 在编译器预定义中添加宏: MCU_STM32 或 MCU_8BIT
 * 2. 或者在本文件开头取消对应注释
 * 
 * Keil MDK设置方法:
 *   Options → C/C++ → Define 中添加 MCU_STM32 或 MCU_8BIT
 * 
 * GCC编译选项:
 *   -DMCU_STM32 或 -DMCU_8BIT
 */

// #define MCU_STM32    // STM32等32位MCU
// #define MCU_8BIT     // 51/AVR等8位MCU

#if defined(MCU_STM32)
    /* 使用STM32平台配置 */
    #include "tm1616_port_stm32.h"
    
#elif defined(MCU_8BIT)
    /* 使用8位单片机平台配置 */
    #include "tm1616_port_8bit.h"
    
#else
    /* 未定义平台类型，给出错误提示 */
    #error "Please define MCU type in compiler options: MCU_STM32 or MCU_8BIT"
    /* 
     * 临时测试可以使用默认配置（不推荐）:
     * #define MCU_STM32
     * #include "tm1616_port_stm32.h"
     */
#endif

#endif /* TM1616_PORT_H */
