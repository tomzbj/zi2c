#include "zi2c.h"
#include "ccs811.h"

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
    g.stop_f(&g);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_READ);
    val = g.readbyte_nack_f(&g);
    g.stop_f(&g);
    return val;
}

static void ReadNReg(unsigned char reg, unsigned char* buf, int count)
{
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, reg);
//    g.stop_f(&g);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_READ);

    for(int i = 0; i < count - 1; i++) {
        *buf = g.readbyte_ack_f(&g);
        buf++;
    }
    *buf = g.readbyte_nack_f(&g);
    g.stop_f(&g);
}

static void WriteReg(unsigned char reg, unsigned char val)
{
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, reg);
    g.writebyte_f(&g, val);
    g.stop_f(&g);
}

void CCS811_ReadStatus(void)
{
    xprintf("%02x\n", ReadReg(0x0));
}

void CCS811_Start(void)
{
    WriteReg(0xf4, 0x00);
}
void CCS811_ReadErrorStatus(void)
{
    xprintf("%02x\n", ReadReg(0xe0));
}

void CCS811_ReadAllRegs(void)
{
    unsigned char buf[8];
    ReadNReg(0x2, buf, 8);
    for(int i = 0; i < 8; i++) {
        xprintf("%02X ", buf[i]);
    }
    xprintf("\n");
}

void CCS811_Init(zi2c_t* obj)
{
    g = *obj;
    printf("### %02X\n", ReadReg(0x20));
    printf("### %02X\n", ReadReg(0x20));
//    WriteReg(0xf4, 0x0);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, 0xf4);
    g.stop_f(&g);
    printf("### %02X\n", ReadReg(0x0));
    WriteReg(0x1, 0x10);
    printf("### %02X\n", ReadReg(0x1));
    _delay_ms(100);
}
