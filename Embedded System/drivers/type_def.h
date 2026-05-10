#ifndef __STDINT_COMPAT_H__
#define __STDINT_COMPAT_H__

/* 
 * 嵌入式常用基础数据类型定义
 * 适用于编译器不支持标准 <stdint.h> 的情况
 */

// 无符号整型 (Unsigned)
typedef unsigned char         uint8_t;    // 8位 (0 到 255)
typedef unsigned int          uint16_t;   // 16位 (0 到 65535)
typedef unsigned long         uint32_t;   // 32位 (0 到 4294967295)

// 有符号整型 (Signed)
typedef signed char           int8_t;     // 8位 (-128 到 127)
typedef signed int            int16_t;    // 16位 (-32768 到 32767)
typedef signed long           int32_t;    // 32位 (-2147483648 到 2147483647)

// 布尔类型定义 (可选)
#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined
/*typedef uint8_t           bool;
*/
    #define true              1
    #define false             0
#endif

#endif /* __STDINT_COMPAT_H__ */