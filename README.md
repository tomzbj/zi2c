# zi2c

简易的i2c主机库.

## 简介

只需要提供三个回调函数, 分别用于写SDA/写SCL/读SDA脚. 提供start, stop, writebyte, readbyte(带/不带nak)的五个回调函数给驱动. 大部分i2c设备有这五个操作就足够了.

## 使用方法

在STM32F0/F3平台上把SDA引脚初始化为OD方式并打开内置上拉电阻,  在STM32F1上则必须给SDA线外接上拉电阻. SCL脚按推挽方式. 

提供三个回调函数如下(以DS1307为例):

    #define DS1307_GPIO GPIOA
    #define DS1307_SDA GPIO_Pin_2
    #define DS1307_SCL GPIO_Pin_3

    static void setsda(int s)
    {
        (s) ? (DS1307_GPIO->BSRR = DS1307_SDA) : (DS1307_GPIO->BRR = DS1307_SDA);
        _delay_us(3);
    }

    static void setscl(int s)
    {
        (s) ? (DS1307_GPIO->BSRR = DS1307_SCL) : (DS1307_GPIO->BRR = DS1307_SCL);
        _delay_us(3);
    }

    static int getsda(void)
    {
        _delay_us(3);
        return (DS1307_GPIO->IDR & DS1307_SDA);
    }

之后按如下方式初始化zi2c库和外设驱动即可使用.

    static zi2c_t i2c;
    i2c.setsda_f = setsda;
    i2c.setscl_f = setscl;
    i2c.getsda_f = getsda;
    i2c.addr = 0x68;
    zi2c_init(&i2c);
    DS1307_Init(&i2c);

## 已支持器件

### 时钟类

DS1307

### 传感器类

LIS3DHTR MMA7660 MPU9250

### 显示类

SSD1306(OLED屏常用)

### 待添加(更新中)

ADXL345 ALS31313 TM1650 OPT3001 RDA5807MS 24Cxx PCF8574 TEA5767 QMC5883 SHT30 SHTC3 Si5351 MCP3421 QN8027
