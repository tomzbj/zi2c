#include "zi2c.h"
#include "qmc5883.h"

#include "xprintf.h" //debug

#define  CMD_WRITE (g.addr << 1)
#define  CMD_READ (CMD_WRITE + 1)

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

void QMC5883_ReadAllRegs(void)
{
    xprintf("%04x %04x %04x\n",
        ReadReg(3) * 256UL + ReadReg(4),
        ReadReg(5) * 256UL + ReadReg(6),
        ReadReg(7) * 256UL + ReadReg(8));
}

void QMC5883_Init(zi2c_t* obj)
{
    g = *obj;
}
