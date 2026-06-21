#ifndef TM1616_PORT_8BIT_H
#define TM1616_PORT_8BIT_H

#include "type_def.h"

/* 
 * 8位单片机端口配置
 * 适用于: 51系列、AVR、PIC等8位MCU
 * 注意: 需要根据具体芯片型号调整寄存器操作方式
 */

/* ==================== 引脚配置 - 根据实际硬件修改 ==================== */
/* 示例: 假设使用P1口的0-2引脚 */
sbit TM1616_CLK_PIN = P1^0;  // CLK接P1.0
sbit TM1616_DIN_PIN = P1^1;  // DIN接P1.1
sbit TM1616_STB_PIN = P1^2;  // STB接P1.2

/* ==================== 直接位操作宏 ==================== */
#define TM1616_CLK_HIGH()   (TM1616_CLK_PIN = 1)
#define TM1616_CLK_LOW()    (TM1616_CLK_PIN = 0)

#define TM1616_DIN_HIGH()   (TM1616_DIN_PIN = 1)
#define TM1616_DIN_LOW()    (TM1616_DIN_PIN = 0)

#define TM1616_STB_HIGH()   (TM1616_STB_PIN = 1)
#define TM1616_STB_LOW()    (TM1616_STB_PIN = 0)

/* ==================== 8位单片机专用函数声明 ==================== */
void TM1616_Port_Init(void);

/* 
 * 如果使用AVR单片机，可以这样定义:
 * #define TM1616_CLK_PORT   PORTB
 * #define TM1616_CLK_PIN    PB0
 * #define TM1616_CLK_DDR    DDRB
 * 
 * #define TM1616_CLK_HIGH() (TM1616_CLK_PORT |= (1 << TM1616_CLK_PIN))
 * #define TM1616_CLK_LOW()  (TM1616_CLK_PORT &= ~(1 << TM1616_CLK_PIN))
 */

#endif /* TM1616_PORT_8BIT_H */
