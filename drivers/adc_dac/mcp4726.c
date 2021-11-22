#include "mcp4726.h"

#define  CMD_WRITE (g.addr << 1)
#define  CMD_READ (CMD_WRITE + 1)

enum {
    CMD_WRITE_VOLATILE_DAC_REG = 0, CMD_WRITE_VOLATILE_MEM = 2,
    CMD_WRITE_ALL_MEM = 3, CMD_WRITE_VOLATILE_CFG_BITS = 4
};

static zi2c_t g;

static struct {
    unsigned short cmd_bits;
    unsigned short pd_bits;
    unsigned short vref_bits;
    unsigned short gain_bits;
} cfg;

static void write_volatile_dac_reg(unsigned short data)
{
    cfg.cmd_bits = CMD_WRITE_VOLATILE_CFG_BITS;
//    cfg.pd_bits = PD_NORMAL;

    data &= 0xfff;
    data |= (cfg.cmd_bits & 0x6) << 13;
    data |= (cfg.pd_bits & 0x3) << 12;

    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, data >> 8);
    g.writebyte_f(&g, data & 0xff);
    g.stop_f(&g);
}

static void write_volatile_mem(unsigned short data)
{
    cfg.cmd_bits = CMD_WRITE_VOLATILE_MEM;
//    cfg.pd_bits = PD_NORMAL;

    data <<= 4;
    unsigned char tmp = 0;
    tmp = (cfg.cmd_bits & 0x7) << 5;
    tmp |= (cfg.vref_bits & 0x3) << 3;
    tmp |= (cfg.pd_bits & 0x3) << 1;
    tmp |= (cfg.gain_bits & 0x1);

    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, tmp);
    g.writebyte_f(&g, data >> 8);
    g.writebyte_f(&g, data & 0xff);
    g.stop_f(&g);
}

static void write_all_mem(unsigned short data)
{
    cfg.cmd_bits = CMD_WRITE_ALL_MEM;
    data <<= 4;
    unsigned char tmp = 0;
    tmp = (cfg.cmd_bits & 0x7) << 5;
    tmp |= (cfg.vref_bits & 0x3) << 3;
    tmp |= (cfg.pd_bits & 0x3) << 1;
    tmp |= (cfg.gain_bits & 0x1);

    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, tmp);
    g.writebyte_f(&g, data >> 8);
    g.writebyte_f(&g, data & 0xff);
    g.stop_f(&g);
}

static void write_volatile_cfg_bits(unsigned short data)
{
    cfg.cmd_bits = CMD_WRITE_VOLATILE_CFG_BITS;
    data <<= 4;
    unsigned char tmp = 0;
    tmp = (cfg.cmd_bits & 0x7) << 5;
    tmp |= (cfg.vref_bits & 0x3) << 3;
    tmp |= (cfg.pd_bits & 0x3) << 1;
    tmp |= (cfg.gain_bits & 0x1);

    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, tmp);
    g.stop_f(&g);
}

static void read_all_mem(unsigned char* cfg, unsigned short* data)
{
    unsigned short tmp;
    g.start_f(&g);
    *cfg = g.readbyte_ack_f(&g);
    tmp = g.readbyte_ack_f(&g);
    tmp <<= 8;
    tmp |= g.readbyte_ack_f(&g);
    g.stop_f(&g);
    *data = tmp;
}

void MCP4726_Init(zi2c_t* i2c, int pd, int vref, int gain)
{
    g = *i2c;
    cfg.pd_bits = pd;
    cfg.vref_bits = vref;
    cfg.gain_bits = gain;
}

void MCP4726_Write(unsigned short data)
{
    write_all_mem(data);
}
