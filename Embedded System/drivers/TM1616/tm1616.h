#ifndef TM1616_H
#define TM1616_H

#include "type_def.h"

/* 引脚配置 - 根据实际硬件修改 */
#define TM1616_CLK_PORT     GPIOA
#define TM1616_CLK_PIN      GPIO_PIN_0
#define TM1616_DIN_PORT     GPIOA
#define TM1616_DIN_PIN      GPIO_PIN_1
#define TM1616_STB_PORT     GPIOA
#define TM1616_STB_PIN      GPIO_PIN_2


/* 宏定义操作引脚 */
#define TM1616_CLK_HIGH()   HAL_GPIO_WritePin(TM1616_CLK_PORT, TM1616_CLK_PIN, GPIO_PIN_SET)
#define TM1616_CLK_LOW()    HAL_GPIO_WritePin(TM1616_CLK_PORT, TM1616_CLK_PIN, GPIO_PIN_RESET)
#define TM1616_DIN_HIGH()   HAL_GPIO_WritePin(TM1616_DIN_PORT, TM1616_DIN_PIN, GPIO_PIN_SET)
#define TM1616_DIN_LOW()    HAL_GPIO_WritePin(TM1616_DIN_PORT, TM1616_DIN_PIN, GPIO_PIN_RESET)
#define TM1616_STB_HIGH()   HAL_GPIO_WritePin(TM1616_STB_PORT, TM1616_STB_PIN, GPIO_PIN_SET)
#define TM1616_STB_LOW()    HAL_GPIO_WritePin(TM1616_STB_PORT, TM1616_STB_PIN, GPIO_PIN_RESET)


/* 显示模式指令 */
#define TM1616_MODE_7SEG_4GRID    0x00  // 7段×4位模式

/* 数据命令设置 */
#define TM1616_DATA_AUTO_INC      0x40  // 地址自动加1模式
#define TM1616_DATA_FIX_ADDR      0x44  // 固定地址模式

/* 显示控制命令（亮度 + 开关） */
#define TM1616_DISP_OFF           0x80  // 显示关闭
#define TM1616_DISP_ON            0x88  // 显示开启（基础值）
#define TM1616_BRIGHTNESS_1       0x88  // 1/16 亮度
#define TM1616_BRIGHTNESS_2       0x89  // 2/16 亮度
#define TM1616_BRIGHTNESS_3       0x8A  // 3/16 亮度
#define TM1616_BRIGHTNESS_4       0x8B  // 4/16 亮度
#define TM1616_BRIGHTNESS_5       0x8C  // 5/16 亮度
#define TM1616_BRIGHTNESS_6       0x8D  // 6/16 亮度
#define TM1616_BRIGHTNESS_7       0x8E  // 7/16 亮度
#define TM1616_BRIGHTNESS_8       0x8F  // 8/16 亮度（最亮）


/* 显存地址 */
#define TM1616_ADDR_DIGIT1        0xC0  // 第1位数码管
#define TM1616_ADDR_DIGIT2        0xC2  // 第2位数码管
#define TM1616_ADDR_DIGIT3        0xC4  // 第3位数码管
#define TM1616_ADDR_DIGIT4        0xC6  // 第4位数码管

extern const uint8_t TM1616_SEG_CODE[16];

/* 函数声明 */
void TM1616_Init(void);
void TM1616_WriteByte(uint8_t data);
void TM1616_WriteCommand(uint8_t cmd);
void TM1616_WriteData(uint8_t addr, uint8_t data);
void TM1616_DisplayDigit(uint8_t pos, uint8_t num, uint8_t dot);
void TM1616_DisplayNumber(int16_t number);
void TM1616_DisplayClear(void);
void TM1616_SetBrightness(uint8_t brightness);
void TM1616_DisplayOn(void);
void TM1616_DisplayOff(void);
void TM1616_DisplayRaw(uint8_t pos, uint8_t seg_data);
void TM1616_DisplayFourChars(char c1, char c2, char c3, char c4);








#endif // TM1616_H
