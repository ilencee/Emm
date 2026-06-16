#include "stdio.h"
#include "type_def.h"
#include "../drivers/TM1616/tm1616.h"
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
    // 初始化TM1616显示驱动
    TM1616_Init();
    
    // 显示 "0111"（TM1616有内部显存，写入后会保持显示）
    TM1616_DisplayFourChars('0', '1', '1', '1');
    ·
    while(1)
    {
        
        // 主循环，可以做其他任务
        // 显示会一直保持在 "0111"
    }
    
    return 0;
}