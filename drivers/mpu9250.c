#include "zi2c.h"
#include "mpu9250.h"

#include "xprintf.h" //debug

#define  CMD_WRITE (g.addr << 1)
#define  CMD_READ (CMD_WRITE | 0x1)

enum {
    REG_PWR = 0x6b, REG_SMPLRT_DIV = 0x19, REG_CONFIG = 0x1a,
    REG_GYRO_CONFIG = 0x1b, REG_ACCEL_CONFIG = 0x1c
};

static zi2c_t g;

static unsigned char ReadReg(unsigned char reg)
{
    unsigned char val;
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, reg);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_READ);
    val = g.readbyte_nack_f(&g);
    g.stop_f(&g);
    return val;
}

static void WriteReg(unsigned char reg, unsigned char val)
{
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, reg);
    g.writebyte_f(&g, val);
    g.stop_f(&g);
}

void MPU9250_ReadAllRegs(void)
{
    xprintf("%02X\n", ReadReg(117));
    xprintf("%02X\n", ReadReg(59));
    xprintf("%02X\n", ReadReg(60));
    xprintf("%02X\n", ReadReg(61));
    xprintf("%02X\n", ReadReg(62));
    xprintf("%02X\n", ReadReg(63));
    xprintf("%02X\n\n", ReadReg(64));
}

void MPU9250_Init(zi2c_t* obj)
{
    g = *obj;
    WriteReg(REG_PWR, 0x00);  //解除休眠状态
    WriteReg(REG_SMPLRT_DIV, 0x07);
    WriteReg(REG_CONFIG, 0x06);
    WriteReg(REG_GYRO_CONFIG, 0x18);
    WriteReg(REG_ACCEL_CONFIG, 0x01);
}
