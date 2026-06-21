#include "TM1616.h"
#include "type_def.h"
#include "tm1616_font.h"
//#include "delay.h"  // 需要微秒级延时函数


/* 显存地址表 */
static const uint8_t digit_addr[4] = {
    TM1616_ADDR_DIGIT1,
    TM1616_ADDR_DIGIT2,
    TM1616_ADDR_DIGIT3,
    TM1616_ADDR_DIGIT4};

/**
 * @brief  微秒级延时（根据主频调整）
 * @note   TM1616 最大时钟频率 1MHz，最小时钟脉宽 400ns
 */
static void TM1616_Delay_us(uint32_t us)
{
    // 简单延时，实际项目中建议使用定时器
    for (volatile uint32_t i = 0; i < us * 8; i++)
        ; // 72MHz 时约 1us
}

/**
 * @brief  TM1616 初始化
 */
void TM1616_Init(void)
{
    /* 调用平台相关的GPIO初始化 */
    TM1616_Port_Init();

    /* 发送初始化命令序列 */
    TM1616_WriteCommand(TM1616_MODE_7SEG_4GRID); // 设置显示模式
    TM1616_WriteCommand(TM1616_DATA_AUTO_INC);   // 地址自动加1模式
    TM1616_DisplayClear();                       // 清屏
    TM1616_WriteCommand(TM1616_BRIGHTNESS_4);    // 设置亮度（中等）
    TM1616_DisplayOn();                          // 开启显示
}

/**
 * @brief  向 TM1616 写入一个字节（串行数据）
 * @param  data: 要写入的数据
 * @note   在 CLK 上升沿采样 DIN 数据，LSB 在前
 */
void TM1616_WriteByte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        TM1616_CLK_LOW();   // CLK 拉低
        TM1616_Delay_us(1); // 等待

        /* 设置数据位（LSB 在前） */
        if (data & 0x01)
            TM1616_DIN_HIGH();
        else
            TM1616_DIN_LOW();

        TM1616_Delay_us(1); // 数据建立时间
        TM1616_CLK_HIGH();  // CLK 上升沿采样
        TM1616_Delay_us(1); // 数据保持时间

        data >>= 1; // 移到下一位
    }
}

/**
 * @brief  发送命令到 TM1616
 * @param  cmd: 命令字节
 */
void TM1616_WriteCommand(uint8_t cmd)
{
    TM1616_STB_LOW(); // STB 拉低，开始传输
    TM1616_Delay_us(1);

    TM1616_WriteByte(cmd); // 发送命令

    TM1616_STB_HIGH(); // STB 拉高，结束传输
    TM1616_Delay_us(1);
}

/**
 * @brief  向指定地址写入显示数据
 * @param  addr: 显存地址
 * @param  data: 显示数据（段码）
 */
void TM1616_WriteData(uint8_t addr, uint8_t data)
{
    TM1616_STB_LOW(); // STB 拉低
    TM1616_Delay_us(1);

    TM1616_WriteByte(addr); // 发送地址
    TM1616_WriteByte(data); // 发送数据

    TM1616_STB_HIGH(); // STB 拉高
    TM1616_Delay_us(1);
}

/**
 * @brief  在指定位置显示一个数字
 * @param  pos: 位置（0-3，0为最左边）
 * @param  num: 数字（0-15，对应 0-9, A-F）
 * @param  dot: 小数点（0=不显示，1=显示）
 */
void TM1616_DisplayDigit(uint8_t pos, uint8_t num, uint8_t dot)
{
    uint8_t seg_data;

    if (pos > 3)
        return;
    if (num > 15)
        num = 15;

    seg_data = TM1616_SEG_CODE[num];
    if (dot)
        seg_data |= 0x80; // 点亮小数点（dp段）

    TM1616_WriteData(digit_addr[pos], seg_data);
}

/**
 * @brief  显示一个整数（-999 ~ 9999）
 * @param  number: 要显示的整数
 */
void TM1616_DisplayNumber(int16_t number)
{
    uint8_t digits[4] = {0, 0, 0, 0};
    uint8_t i;
    uint8_t is_negative = 0;

    TM1616_DisplayClear();

    if (number < 0)
    {
        is_negative = 1;
        number = -number;
    }

    /* 提取各位数字 */
    digits[3] = number % 10;          // 个位
    digits[2] = (number / 10) % 10;   // 十位
    digits[1] = (number / 100) % 10;  // 百位
    digits[0] = (number / 1000) % 10; // 千位

    /* 显示数字，去除前导零 */
    uint8_t leading_zero = 1;
    for (i = 0; i < 4; i++)
    {
        if (digits[i] == 0 && leading_zero && i < 3)
        {
            // 前导零不显示（但保留个位）
            if (is_negative && i == 2)
            {
                // 在合适位置显示负号
                TM1616_WriteData(digit_addr[i], 0x40); // 显示 "-"
                leading_zero = 0;
            }
        }
        else
        {
            TM1616_DisplayDigit(i, digits[i], 0);
            leading_zero = 0;
        }
    }

    /* 如果数字为0，显示0 */
    if (number == 0 && !is_negative)
    {
        TM1616_DisplayDigit(3, 0, 0);
    }
}

/**
 * @brief  清屏（关闭所有显示）
 */
void TM1616_DisplayClear(void)
{
    uint8_t i;

    TM1616_STB_LOW();
    TM1616_Delay_us(1);

    TM1616_WriteByte(TM1616_ADDR_DIGIT1); // 起始地址

    for (i = 0; i < 14; i++)
    {
        TM1616_WriteByte(0x00); // 写入0关闭显示
    }

    TM1616_STB_HIGH();
    TM1616_Delay_us(1);
}

/**
 * @brief  设置亮度
 * @param  brightness: 亮度等级（1-8）
 */
void TM1616_SetBrightness(uint8_t brightness)
{
    if (brightness < 1)
        brightness = 1;
    if (brightness > 8)
        brightness = 8;

    uint8_t cmd = TM1616_DISP_ON | (brightness - 1);
    TM1616_WriteCommand(cmd);
}

/**
 * @brief  开启显示
 */
void TM1616_DisplayOn(void)
{
    TM1616_WriteCommand(TM1616_BRIGHTNESS_4); // 默认中等亮度
}

/**
 * @brief  关闭显示
 */
void TM1616_DisplayOff(void)
{
    TM1616_WriteCommand(TM1616_DISP_OFF);
}

/**
 * @brief  在指定位置显示原始段码
 * @param  pos: 位置（0-3）
 * @param  seg_data: 段码数据（bit0=a, bit1=b, ..., bit7=dp）
 */
void TM1616_DisplayRaw(uint8_t pos, uint8_t seg_data)
{
    if (pos > 3)
        return;
    TM1616_WriteData(digit_addr[pos], seg_data);
}

/**
 * @brief  同时显示四位指定字符
 * @param  c1: 第1位字符（最左边，对应数码管位置0）
 * @param  c2: 第2位字符（对应数码管位置1）
 * @param  c3: 第3位字符（对应数码管位置2）
 * @param  c4: 第4位字符（最右边，对应数码管位置3）
 * @note   支持字符：0-9, A-F, a-f, '-', ' ', '_'
 *         不支持的字符将显示为空白
 * @example TM1616_DisplayFourChars('9', 'A', 'B', '3');  // 显示 "9AB3"
 */
void TM1616_DisplayFourChars(char c1, char c2, char c3, char c4)
{
    uint8_t seg_data[4];
    
    /* 将字符转换为段码 */
    seg_data[0] = (c1 >= 0 && c1 < 128) ? tm1616_ascii_table[(uint8_t)c1] : 0x00;
    seg_data[1] = (c2 >= 0 && c2 < 128) ? tm1616_ascii_table[(uint8_t)c2] : 0x00;
    seg_data[2] = (c3 >= 0 && c3 < 128) ? tm1616_ascii_table[(uint8_t)c3] : 0x00;
    seg_data[3] = (c4 >= 0 && c4 < 128) ? tm1616_ascii_table[(uint8_t)c4] : 0x00;
    
    /* 使用固定地址模式连续写入四位数据 */
    TM1616_STB_LOW();
    TM1616_Delay_us(1);
    
    TM1616_WriteByte(TM1616_ADDR_DIGIT1);  // 起始地址
    TM1616_WriteByte(seg_data[0]);         // 第1位
    TM1616_WriteByte(seg_data[1]);         // 第2位
    TM1616_WriteByte(seg_data[2]);         // 第3位
    TM1616_WriteByte(seg_data[3]);         // 第4位
    
    TM1616_STB_HIGH();
    TM1616_Delay_us(1);
}
