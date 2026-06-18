#ifndef scan_h
#define scan_h

#include "type_def.h"

// 平台选择宏 (取消注释以选择对应平台)
#define MCU_8BIT      // 8位单片机 (如51、AVR)
//#define MCU_32BIT     // 32位单片机 (如STM32)

// ==================== 硬件引脚配置 ====================
#if defined(MCU_8BIT)
    // 8位单片机配置示例 (请根据实际硬件修改)
    //#include <reg52.h>  // 或其他8位MCU头文件
    
    // 段选引脚 (a,b,c,d,e,f,g,dp)
    #define SEG_PORT    P1          // 段选端口
    #define SEG_A       P1_0
    #define SEG_B       P1_1
    #define SEG_C       P1_2
    #define SEG_D       P1_3
    #define SEG_E       P1_4
    #define SEG_F       P1_5
    #define SEG_G       P1_6
    #define SEG_DP      P1_7
    
    // COM口选择引脚 (4位数码管需要4个COM口)
    #define COM_PORT    P2
    #define COM1        P2_0        // 第1位数码管公共端
    #define COM2        P2_1        // 第2位数码管公共端
    #define COM3        P2_2        // 第3位数码管公共端
    #define COM4        P2_3        // 第4位数码管公共端

#elif defined(MCU_32BIT)
    // 32位单片机配置示例 (如STM32，请根据实际硬件修改)
    #include "stm32f1xx.h"  // 或其他32位MCU头文件
    
    // 段选引脚配置 (假设使用GPIOA)
    #define SEG_GPIO_PORT     GPIOA
    #define SEG_GPIO_CLK      RCC_APB2Periph_GPIOA
    
    #define SEG_A_PIN         GPIO_Pin_0
    #define SEG_B_PIN         GPIO_Pin_1
    #define SEG_C_PIN         GPIO_Pin_2
    #define SEG_D_PIN         GPIO_Pin_3
    #define SEG_E_PIN         GPIO_Pin_4
    #define SEG_F_PIN         GPIO_Pin_5
    #define SEG_G_PIN         GPIO_Pin_6
    #define SEG_DP_PIN        GPIO_Pin_7
    
    // COM口选择引脚 (假设使用GPIOB)
    #define COM_GPIO_PORT     GPIOB
    #define COM_GPIO_CLK      RCC_APB2Periph_GPIOB
    
    #define COM1_PIN          GPIO_Pin_0
    #define COM2_PIN          GPIO_Pin_1
    #define COM3_PIN          GPIO_Pin_2
    #define COM4_PIN          GPIO_Pin_3
#endif

// ==================== 数码管类型配置 ====================
// 共阴极: 1 (COM口低电平有效)
// 共阳极: 0 (COM口高电平有效)
#define SEGMENT_COMMON_CATHODE    1

// ==================== 段码定义 (共阴极) ====================
// 使用宏定义支持位运算组合
#define SEG_A_BIT     0x01
#define SEG_B_BIT     0x02
#define SEG_C_BIT     0x04
#define SEG_D_BIT     0x08
#define SEG_E_BIT     0x10
#define SEG_F_BIT     0x20
#define SEG_G_BIT     0x40
#define SEG_DP_BIT    0x80

// 数字0-9的段码 (共阴极)
#define SEG_CODE_0    (SEG_A_BIT | SEG_B_BIT | SEG_C_BIT | SEG_D_BIT | SEG_E_BIT | SEG_F_BIT)
#define SEG_CODE_1    (SEG_B_BIT | SEG_C_BIT)
#define SEG_CODE_2    (SEG_A_BIT | SEG_B_BIT | SEG_D_BIT | SEG_E_BIT | SEG_G_BIT)
#define SEG_CODE_3    (SEG_A_BIT | SEG_B_BIT | SEG_C_BIT | SEG_D_BIT | SEG_G_BIT)
#define SEG_CODE_4    (SEG_B_BIT | SEG_C_BIT | SEG_F_BIT | SEG_G_BIT)
#define SEG_CODE_5    (SEG_A_BIT | SEG_C_BIT | SEG_D_BIT | SEG_F_BIT | SEG_G_BIT)
#define SEG_CODE_6    (SEG_A_BIT | SEG_C_BIT | SEG_D_BIT | SEG_E_BIT | SEG_F_BIT | SEG_G_BIT)
#define SEG_CODE_7    (SEG_A_BIT | SEG_B_BIT | SEG_C_BIT)
#define SEG_CODE_8    (SEG_A_BIT | SEG_B_BIT | SEG_C_BIT | SEG_D_BIT | SEG_E_BIT | SEG_F_BIT | SEG_G_BIT)
#define SEG_CODE_9    (SEG_A_BIT | SEG_B_BIT | SEG_C_BIT | SEG_D_BIT | SEG_F_BIT | SEG_G_BIT)
#define SEG_CODE_OFF  0x00  // 熄灭

// ==================== 函数声明 ====================
/**
 * @brief 初始化数码管扫描驱动
 */
void Segment_Scan_Init(void);

/**
 * @brief 设置四位数码管显示内容
 * @param digit1 第1位数字 (0-9, 10表示熄灭)
 * @param digit2 第2位数字 (0-9, 10表示熄灭)
 * @param digit3 第3位数字 (0-9, 10表示熄灭)
 * @param digit4 第4位数字 (0-9, 10表示熄灭)
 */
void Segment_Scan_SetDisplay(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4);

/**
 * @brief 数码管扫描刷新函数 (需在主循环中调用)
 * @note 此函数需要在while(1)循环中持续调用以保持显示
 */
void Segment_Scan_Refresh(void);

#endif
