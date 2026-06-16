#include "stdio.h"
#include "type_def.h"
//#include "../drivers/TM1616/tm1616.h"
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



static const uint8_t SEG_NUM[] =
{
    [0] = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
    [1] = SEG_B | SEG_C,
    [2] = SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,
    [3] = SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,
    [4] = SEG_B | SEG_C | SEG_F | SEG_G,
    [5] = SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
    [6] = SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    [7] = SEG_A |SEG_B |SEG_C,
    [8] = SEG_A |SEG_B |SEG_C |SEG_D |SEG_E |SEG_F |SEG_G,
    [9] = SEG_A |SEG_B |SEG_C |SEG_D |SEG_F |SEG_G
};
printf("%0x\n",SEG_NONE);
return 0;
}