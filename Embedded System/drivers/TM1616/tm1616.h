#ifndef TM1616_H
#define TM1616_H

#include "type_def.h"
#include "tm1616_port.h"  // 包含端口配置（自动根据平台选择）


/* 显示模式指令 */
#define TM1616_MODE_7SEG_4GRID    0x00  // 7段×4位模式

/* 数据命令设置 */
#define TM1616_DATA_AUTO_INC      0x40  // 地址自动加1模式
#define TM1616_DATA_FIX_ADDR      0x44  // 固定地址模式