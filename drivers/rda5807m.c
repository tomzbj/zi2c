#include "rda5807m.h"
#include "zi2c.h"

#define  CMD_WRITE (g.addr << 1) //0x20
#define  CMD_READ (CMD_WRITE | 1)

enum {
    REG2 = 2, REG3 = 3, REG4 = 4, REG5 = 5, REGA = 0xa, REGB = 0xb
};

#define REG2_BIT_ENABLE 0
#define REG2_BIT_SOFT_RESET 1
#define REG2_BIT_DHIZ 15
#define REG2_BIT_DMUTE 14
#define REG3_BIT_TUNE 4

static zi2c_t g;

static unsigned short read_reg(unsigned char reg)
{
    unsigned short ret;
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, reg);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_READ);
    ret = g.readbyte_ack_f(&g);
    ret <<= 8;
    ret |= g.readbyte_nack_f(&g);
    g.stop_f(&g);
    return ret;
}

static void write_reg(unsigned char reg, unsigned short data)
{
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, reg);
    g.writebyte_f(&g, data >> 8);
    g.writebyte_f(&g, data & 0xff);
    g.stop_f(&g);
}

#define NUM 16
void RDA5807MS_ReadRegAll(void (*visit_f)(int, unsigned short))
{
    int i;
    for(i = 0; i < NUM; i++) {
        visit_f(i, read_reg(i));
    }
}

static void reg_bit_set(unsigned char reg, int bit)
{
    unsigned short val = read_reg(reg);
    val |= (1 << bit);
    write_reg(reg, val);
}

static void reg_bit_reset(unsigned char reg, int bit)
{
    unsigned short val = read_reg(reg);
    val &= ~(1 << bit);
    write_reg(reg, val);
}

void _delay_ms(volatile int nms);

void RDA5807MS_Init(zi2c_t* obj)
{
    g = *obj;
    write_reg(REG2, 0xc001);    // audio output high-z disable, mute disable, power up
    _delay_ms(600);
//    write_reg(REG3, 0x1a10);
    write_reg(REG4, 0x0400);
    write_reg(REG5, 0x86af);
    write_reg(6, 0x8000);
    write_reg(7, 0x5f1a);
//    reg_bit_set(REG3, REG3_BIT_TUNE);
}

void RDA5807MS_SetFreq(unsigned short freq)
{
    unsigned short val = (freq - 870) << 6;
    val |= (1 << 4);
    xprintf("%04x\n", val);
    write_reg(REG3, val);
    _delay_ms(1000);
}

void RDA5807MS_Tune(void)
{
    reg_bit_set(REG3, REG3_BIT_TUNE);
    _delay_ms(1000);
}

void RDA5807MS_Volume_UP(void)
{
    unsigned short val = read_reg(REG5);
    if((val & 0xf) < 0xf)
        val++;
    write_reg(REG5, val);
}
void RDA5807MS_Volume_DOWN(void)
{
    unsigned short val = read_reg(REG5);
    if((val & 0xf) > 0)
        val--;
    write_reg(REG5, val);
}
void RDA5807MS_Seek_UP(void)
{
    unsigned short val = read_reg(REG2);
    val |= (1 << 9);
    val |= (1 << 8);
    write_reg(REG2, val);
}
void RDA5807MS_Seek_DOWN(void)
{
    unsigned short val = read_reg(REG2);
    val &= ~(1 << 9);
    val |= (1 << 8);
    write_reg(REG2, val);
}
