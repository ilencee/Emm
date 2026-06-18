#include "stdio.h"
#include "type_def.h"
#include "../drivers/TM1616/tm1616.h"
#include "../drivers/Segment_Scan/scan.h"

typedef enum
{
    SEG_A  = 0x01,
    SEG_B  = 0x02,
    SEG_C  = 0x04,
    SEG_D  = 0x08,
    SEG_E  = 0x10,
    SEG_F  = 0x20,
    SEG_G  = 0x40,
    SEG_DP = 0x80,
    SEG_NONE,
} tm1616_seg_t;

int main(void)
{
    // ==================== 方案1: 使用TM1616驱动芯片 (有显存，只需写一次) ====================
    /*
    TM1616_Init();
    TM1616_DisplayFourChars('0', '1', '1', '1');
    */
    
    // ==================== 方案2: 使用MCU直接扫描数码管 (无显存，需循环刷新) ====================
    // 初始化数码管扫描驱动
    Segment_Scan_Init();
    
    // 设置显示内容: 显示 "1234"
    // 参数说明: digit1, digit2, digit3, digit4 (0-9为数字, 10为熄灭)
    Segment_Scan_SetDisplay(1, 2, 3, 4);
    
    while(1)
    {
        // 重要: MCU扫描方式需要在循环中持续调用刷新函数
        // 这样才能保持数码管显示 (动态扫描原理)
        Segment_Scan_Refresh();
        
        // 主循环，可以做其他任务
        // 注意: 不要在这里添加长时间延时，否则会影响扫描频率导致闪烁
    }
    
    return 0;
}
