#include "mma7660.h"
#include "zi2c.h"
#include "xprintf.h"

enum {
    REG_XOUT = 0x0,
    REG_YOUT = 0x1,
    REG_ZOUT = 0x2,
    REG_TILT = 0x3,
    REG_SRST = 0x4,
    REG_SPCNT = 0x5,
    REG_INTSU = 0x6,
    REG_MODE = 0x7,
    REG_SR = 0x8,
    REG_PDET = 0x9,
    REG_PD = 0xa
};

#define  CMD_WRITE (g.addr << 1)
#define  CMD_READ ((g.addr << 1) + 1)

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

mma7660_data_t MMA7660_Read(void)
{
    mma7660_data_t r;
    r.x = ReadReg(0);
    r.y = ReadReg(1);
    r.z = ReadReg(2);
    if(r.x & 0x20)
        r.x |= 0xc0;
    if(r.y & 0x20)
        r.y |= 0xc0;
    if(r.z & 0x20)
        r.z |= 0xc0;
    return r;
}

void MMA7660_ReadAllRegs(void)
{
    for(unsigned char i = 0; i <= 0xa; i++)
        xprintf("%04x  ", ReadReg(i));
    xprintf("\n");
}

void MMA7660_Init(zi2c_t* obj)
{
    g = *obj;
    WriteReg(REG_MODE, 0x00);
    WriteReg(REG_SPCNT, 0x00);
    WriteReg(REG_INTSU, 0x01);
    WriteReg(REG_SR, 0x02);
    WriteReg(REG_PDET, 0xe0);
    WriteReg(REG_PD, 0x00);
    WriteReg(REG_MODE, 0x41);
}
