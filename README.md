# zi2c

简易的i2c主机库.

## 简介

用户只需要提供三个回调函数, 分别用于写SDA/写SCL/读SDA脚.  
之后可以把start, stop, writebyte, readbyte(带/不带nak)这五个函数作为回调传给驱动, 大部分i2c设备有这五个操作就足够了, 不用再纠缠i2c操作的具体细节, 写外设驱动时轻松简洁多了.  
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

之后按如下方式初始化zi2c库和外设驱动即可使用.  使用多个i2c器件时建立多个zi2c\_t实例, 并分别提供它们的回调函数即可.

    static zi2c_t i2c;
    i2c.setsda_f = setsda;
    i2c.setscl_f = setscl;
    i2c.getsda_f = getsda;
    i2c.addr = 0x68;    // 某些器件用外设管脚的状态来设定不同的i2c从机地址
    zi2c_init(&i2c);
    DS1307_Init(&i2c);

## 已支持器件 (更新中)

### 实时时钟

DS1307

### 传感器

加速度传感器/陀螺仪: LIS3DHTR MMA7660 MPU9250  
磁场传感器: QMC5883  
温度传感器: LM75  
CO2和TVOC传感器: CCS811  
湿度传感器: SHTC3  

### 显示

SSD1306(OLED屏常用)

### 时钟发生

Si5351

### ADC

MCP3421 

### DAC

MCP4726

### 触摸屏ADC

NS2009

### FM收音机

RDA5807M

### 待添加

ADXL345 ALS31313 TM1650 OPT3001 24Cxx PCF8574 QN8027

## 附: 常用i2c器件地址

|型号|类型|地址|备注|
|----|----|----|----|
|CAT24C02|EEPROM|0x50~0x57|可由A0~A2脚设置|
|AT24C02|EEPROM|0x50~0x57|同上|
|LM75|SENSOR/TEMP|0x48~0x4f|同上|
|DS1307|RTC|0x68||
|LIS3DHTR|MEMS|0x18~0x19|由SA0脚设置|
|MMA7660|MEMS|0x4c|原厂可定制|
|MPU9250|MEMS|0x68~0x69|由AD0脚设置|
|SSD1306|DISP|0x3c~0x3d|由SA0脚设置(在SPI模式下是DC脚)|
|NS2009|ADC|0x48~0x4b|由A0~A1脚设置|
|RDA5807M|FM|0x10||
|MCP3421|ADC|0x68~0x6f|看型号后缀末位, 默认0x68(原厂可定制)|
|Si5351|PLL|0x60~0x61|由A0脚设置|
|SHTC3|SENSOR|0x70||
|CCS811|SENSOR|0x5a||
|QMC5883|SENSOR|0x0d|原厂可定制|
|ALS31313|SENSOR|0x60~0x6e|由AD0和AD1脚电压决定, 也可由原厂定制|
|MCP4726|DAC|0x60~0x67|看型号后缀末位, 默认0x60(原厂可定制)|
