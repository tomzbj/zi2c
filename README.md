# zi2c

简易的i2c主机库.

## 简介

只需要提供三个回调函数, 分别用于写SDA/写SCL/读SDA脚. 提供start, stop, writebyte, readbyte(带/不带nak)的五个回调函数给驱动, 大部分i2c设备有这五个操作就足够了.
不用再纠缠i2c操作的具体细节, 写外设驱动时轻松简洁多了.
此外, zi2c库和相应的外设驱动及上层用户程序可以直接复制粘贴到其他平台, 完全不作修改, 用户只需要改动底层的三个回调函数即可.

## 使用方法

在STM32F0/F3平台上把SDA引脚初始化为OD方式并打开内置上拉电阻即可, 在STM32F1上则必须给SDA线外接上拉电阻. SCL脚按推挽方式初始化. 

用户提供三个回调函数如下(以DS1307为例):

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

之后按如下方式初始化zi2c库和外设驱动即可使用. 使用多个i2c器件时建立多个zi2c\_t实例, 并分别提供它们的回调函数即可.

    static zi2c_t i2c;
    i2c.setsda_f = setsda;
    i2c.setscl_f = setscl;
    i2c.getsda_f = getsda;
    i2c.addr = 0x68;    // 某些器件用外设管脚的状态来设定不同的i2c从机地址
    zi2c_init(&i2c);
    DS1307_Init(&i2c);

## 已支持器件 (更新中)

### 时钟类

DS1307

### 传感器类

LIS3DHTR MMA7660 MPU9250

### 显示类

SSD1306(OLED屏常用)

### 待添加

ADXL345 ALS31313 TM1650 OPT3001 RDA5807MS 24Cxx PCF8574 TEA5767 QMC5883 SHT30 SHTC3 Si5351 MCP3421 QN8027
