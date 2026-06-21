#include "scan.h"

// ==================== 内部变量定义 ====================
// 显示缓冲区 (存储4位数码管的显示内容)
static uint8_t g_display_buffer[4] = {10, 10, 10, 10};  // 初始化为熄灭状态

// 当前扫描位置 (0-3)
static uint8_t g_current_pos = 0;

// 段码查找表 (数字0-9对应的段码)
static const uint8_t seg_code_table[] = {
    SEG_CODE_0,   // 0
    SEG_CODE_1,   // 1
    SEG_CODE_2,   // 2
    SEG_CODE_3,   // 3
    SEG_CODE_4,   // 4
    SEG_CODE_5,   // 5
    SEG_CODE_6,   // 6
    SEG_CODE_7,   // 7
    SEG_CODE_8,   // 8
    SEG_CODE_9,   // 9
    SEG_CODE_OFF  // 10: 熄灭
};

// ==================== 硬件抽象层函数 ====================

#if defined(MCU_8BIT)
/**
 * @brief 设置段选输出 (8位MCU)
 * @param seg_data 段码数据
 */
static void set_segment_output(uint8_t seg_data)
{
    SEG_PORT = seg_data;
}

/**
 * @brief 选择COM口 (8位MCU)
 * @param pos 位置 (0-3)
 */
static void select_com(uint8_t pos)
{
    // 先关闭所有COM口
    COM1 = !SEGMENT_COMMON_CATHODE;
    COM2 = !SEGMENT_COMMON_CATHODE;
    COM3 = !SEGMENT_COMMON_CATHODE;
    COM4 = !SEGMENT_COMMON_CATHODE;
    
    // 根据位置选择对应COM口
    switch(pos)
    {
        case 0: COM1 = SEGMENT_COMMON_CATHODE; break;
        case 1: COM2 = SEGMENT_COMMON_CATHODE; break;
        case 2: COM3 = SEGMENT_COMMON_CATHODE; break;
        case 3: COM4 = SEGMENT_COMMON_CATHODE; break;
        default: break;
    }
}

#elif defined(MCU_32BIT)
/**
 * @brief 初始化GPIO (32位MCU)
 */
static void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能时钟
    RCC_APB2PeriphClockCmd(SEG_GPIO_CLK | COM_GPIO_CLK, ENABLE);
    
    // 配置段选引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | 
                                  SEG_E_PIN | SEG_F_PIN | SEG_G_PIN | SEG_DP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SEG_GPIO_PORT, &GPIO_InitStructure);
    
    // 配置COM引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = COM1_PIN | COM2_PIN | COM3_PIN | COM4_PIN;
    GPIO_Init(COM_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief 设置段选输出 (32位MCU)
 */
static void set_segment_output(uint8_t seg_data)
{
    // 根据seg_data的每一位设置对应引脚
    SEG_GPIO_PORT->BSRR = (uint16_t)(
        ((seg_data & SEG_A_BIT) ? SEG_A_PIN : 0) |
        ((seg_data & SEG_B_BIT) ? SEG_B_PIN << 16 : 0) |
        ((seg_data & SEG_C_BIT) ? SEG_C_PIN << 16 : 0) |
        ((seg_data & SEG_D_BIT) ? SEG_D_PIN << 16 : 0) |
        ((seg_data & SEG_E_BIT) ? SEG_E_PIN << 16 : 0) |
        ((seg_data & SEG_F_BIT) ? SEG_F_PIN << 16 : 0) |
        ((seg_data & SEG_G_BIT) ? SEG_G_PIN << 16 : 0) |
        ((seg_data & SEG_DP_BIT) ? SEG_DP_PIN << 16 : 0)
    );
}

/**
 * @brief 选择COM口 (32位MCU)
 * @param pos 位置 (0-3)
 */
static void select_com(uint8_t pos)
{
    // 先关闭所有COM口
    COM_GPIO_PORT->BSRR = COM1_PIN | COM2_PIN | COM3_PIN | COM4_PIN;  // 置高电平
    
    // 根据位置选择对应COM口 (置低电平)
    switch(pos)
    {
        case 0: COM_GPIO_PORT->BRR = COM1_PIN; break;
        case 1: COM_GPIO_PORT->BRR = COM2_PIN; break;
        case 2: COM_GPIO_PORT->BRR = COM3_PIN; break;
        case 3: COM_GPIO_PORT->BRR = COM4_PIN; break;
        default: break;
    }
}
#endif

// ==================== 延时函数 ====================
/**
 * @brief 简单延时 (用于扫描间隔)
 * @note 实际项目中建议使用定时器或系统滴答计时器
 */
static void delay_us(uint16_t us)
{
#if defined(MCU_8BIT)
    // 8位MCU简单延时 (需根据实际晶振频率调整)
    while(us--)
    {
        unsigned char i;
        for(i = 0; i < 2; i++);  // 空循环
    }
#elif defined(MCU_32BIT)
    // 32位MCU简单延时 (需根据实际晶振频率调整)
    while(us--)
    {
        volatile uint16_t i;
        for(i = 0; i < 10; i++);  // 空循环
    }
#endif
}

// ==================== 公共接口函数 ====================
/**
 * @brief 关闭所有位（消隐，防止鬼影）
 */
static inline void Seg7_Blank(void)
{
    // 先关位选，再改段码，消除切换时的残影
    select_com(0xFF);          // 关闭所有COM口
    set_segment_output(0x00);  // 关闭所有段选
}




/**
 * @brief 初始化数码管扫描驱动
 */
void Segment_Scan_Init(void)
{
#if defined(MCU_32BIT)
    gpio_init();
#endif
    
    // 初始化显示缓冲区为熄灭状态
    g_display_buffer[0] = 10;
    g_display_buffer[1] = 10;
    g_display_buffer[2] = 10;
    g_display_buffer[3] = 10;
    
    // 初始化扫描位置
    g_current_pos = 0;
    
    // 关闭所有COM口
    select_com(0xFF);
    
    // 关闭所有段选
    set_segment_output(0x00);
}

/**
 * @brief 设置四位数码管显示内容
 */
void Segment_Scan_SetDisplay(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4)
{
    // 限制输入范围 (0-10)
    if(digit1 > 10) digit1 = 10;
    if(digit2 > 10) digit2 = 10;
    if(digit3 > 10) digit3 = 10;
    if(digit4 > 10) digit4 = 10;
    
    // 更新显示缓冲区
    g_display_buffer[0] = digit1;
    g_display_buffer[1] = digit2;
    g_display_buffer[2] = digit3;
    g_display_buffer[3] = digit4;
}

/**
 * @brief 数码管扫描刷新函数
 * @note 此函数需要在while(1)循环中持续调用以保持显示
 */
void Segment_Scan_Refresh(void)
{
    uint8_t seg_code;
    
    // 获取当前位置对应的数字
    uint8_t digit = g_display_buffer[g_current_pos];
    
    // 查表获取段码
    seg_code = seg_code_table[digit];
    
    // 输出段码
    set_segment_output(seg_code);
    
    // 选择对应COM口
    select_com(g_current_pos);
    
    // 延时保持显示 (典型值1-5ms)
    delay_us(2000);  // 约2ms
    
    // 消影: 关闭段选和COM口
    set_segment_output(0x00);
    select_com(0xFF);
    
    // 短暂延时
    delay_us(100);  // 约0.1ms
    
    // 切换到下一位
    g_current_pos++;
    if(g_current_pos >= 4)
    {
        g_current_pos = 0;
    }
}
