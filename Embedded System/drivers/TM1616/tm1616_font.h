#ifndef TM1616_FONT_H
#define TM1616_FONT_H

#include "type_def.h"
/*
 * 段位定义
 *
 *      a
 *     ---
 *  f |   | b
 *     -g-
 *  e |   | c
 *     ---
 *      d
 *
 * bit0 -> a
 * bit1 -> b
 * bit2 -> c
 * bit3 -> d
 * bit4 -> e
 * bit5 -> f
 * bit6 -> g
 * bit7 -> dp
 */


#define seg_a   0x01
#define seg_b   0x02
#define seg_c   0x04
#define seg_d   0x08
#define seg_e   0x10
#define seg_f   0x20
#define seg_g   0x40
#define seg_dp  0x80


/* =========================
 * 数码管段码表 (0-9, A-F)
 * 用于显示数字和十六进制字符
 * ========================= */
const uint8_t TM1616_HEX_SEG_CODE[16] = {
    seg_a | seg_b | seg_c | seg_d | seg_e | seg_f,           // 0 -> 0x3F
    seg_b | seg_c,                                            // 1 -> 0x06
    seg_a | seg_b | seg_d | seg_e | seg_g,                    // 2 -> 0x5B
    seg_a | seg_b | seg_c | seg_d | seg_g,                    // 3 -> 0x4F
    seg_b | seg_c | seg_f | seg_g,                            // 4 -> 0x66
    seg_a | seg_c | seg_d | seg_f | seg_g,                    // 5 -> 0x6D
    seg_a | seg_c | seg_d | seg_e | seg_f | seg_g,            // 6 -> 0x7D
    seg_a | seg_b | seg_c,                                    // 7 -> 0x07
    seg_a | seg_b | seg_c | seg_d | seg_e | seg_f | seg_g,    // 8 -> 0x7F
    seg_a | seg_b | seg_c | seg_d | seg_f | seg_g,            // 9 -> 0x6F
    seg_a | seg_b | seg_c | seg_e | seg_f | seg_g,            // A -> 0x77
    seg_c | seg_d | seg_e | seg_f | seg_g,                    // b -> 0x7C
    seg_a | seg_d | seg_e | seg_f,                            // C -> 0x39
    seg_b | seg_c | seg_d | seg_e | seg_g,                    // d -> 0x5E
    seg_a | seg_d | seg_e | seg_f | seg_g,                    // E -> 0x79
    seg_a | seg_e | seg_f | seg_g                             // F -> 0x71
};


/* =========================
 * ASCII 字符映射, 包含常用字符（0-9, A-F, -, 空格, 下划线）
 * ========================= */
const uint8_t tm1616_ascii_table[128] = {

    ['0'] = 0x3F,
    ['1'] = 0x06,
    ['2'] = 0x5B,
    ['3'] = 0x4F,
    ['4'] = 0x66,
    ['5'] = 0x6D,
    ['6'] = 0x7D,
    ['7'] = 0x07,
    ['8'] = 0x7F,
    ['9'] = 0x6F,

    ['A'] = 0x77,
    ['B'] = 0x7C,
    ['C'] = 0x39,
    ['D'] = 0x5E,
    ['E'] = 0x79,
    ['F'] = 0x71,

    ['-'] = 0x40,
    [' '] = 0x00,
    ['_'] = 0x08,
};


#endif