# TM1616 驱动说明

## 文件结构

```
TM1616/
├── tm1616.c              # 主驱动文件（平台无关的通用逻辑）
├── tm1616.h              # 主驱动头文件
├── tm1616_font.h         # 字体库
├── tm1616_port.h         # 端口适配层入口（平台选择）
├── tm1616_port_stm32.h   # STM32平台配置头文件
├── tm1616_port_stm32.c   # STM32平台实现文件（HAL库相关代码）
├── tm1616_port_8bit.h    # 8位单片机配置头文件
└── tm1616_port_8bit.c    # 8位单片机实现文件
```

## 代码分离说明

### 设计原则
- **tm1616.c**: 包含所有平台无关的通用驱动逻辑（通信协议、显示控制等）
- **tm1616_port_stm32.c**: 仅包含STM32特有的HAL库代码（GPIO初始化等）
- **tm1616_port_8bit.c**: 仅包含8位单片机特有的代码

### 平台选择方法

在编译器预定义中添加宏：
- **STM32平台**: 添加 `MCU_STM32` 宏
- **8位单片机**: 添加 `MCU_8BIT` 宏

#### Keil MDK 设置
```
Options → C/C++ → Define 中添加 MCU_STM32 或 MCU_8BIT
```

#### GCC 编译选项
```bash
-DMCU_STM32   # 用于STM32
-DMCU_8BIT    # 用于8位单片机
```

### 编译配置

#### 使用STM32时
需要编译的文件：
- tm1616.c
- tm1616_port_stm32.c

#### 使用8位单片机时
需要编译的文件：
- tm1616.c
- tm1616_port_8bit.c

## 主要功能

### 初始化
```c
TM1616_Init();  // 自动调用对应平台的端口初始化
```

### 显示控制
```c
TM1616_DisplayNumber(1234);           // 显示整数
TM1616_DisplayDigit(0, 5, 0);         // 在指定位置显示数字
TM1616_DisplayFourChars('A','B','1','2'); // 显示四个字符
TM1616_DisplayClear();                // 清屏
TM1616_SetBrightness(4);              // 设置亮度(1-8)
TM1616_DisplayOn();                   // 开启显示
TM1616_DisplayOff();                  // 关闭显示
```

## 硬件连接

### STM32示例
- CLK → PA0
- DIN → PA1
- STB → PA2

### 8位单片机示例（51系列）
- CLK → P1.0
- DIN → P1.1
- STB → P1.2

**注意**: 具体引脚配置请根据实际硬件修改对应的端口配置文件。
