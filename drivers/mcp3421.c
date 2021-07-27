#include "zi2c.h"
#include "mcp3421.h"

#define  CMD_WRITE (g.addr << 1)
#define  CMD_READ (CMD_WRITE + 1)

static zi2c_t g;
static unsigned char g_reg = 0x90;      // power on default

void MCP3421_StartConv(void)
{
    g_reg |= 0x80;
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, g_reg);
    g.stop_f(&g);
}

static void reset(void)
{
    g.start_f(&g);
    g.writebyte_f(&g, 0x00);            // Broadcast
    g.writebyte_f(&g, 0x06);            // Reset
    g.stop_f(&g);
}

void MCP3421_Init(zi2c_t* i2c)
{
    g = *i2c;
    reset();
}

void MCP3421_SetMode(int mode)
{
    mode &= 0x1;
    g_reg = (g_reg & 0xef) | (mode << 4);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, g_reg);
    g.stop_f(&g);

}
void MCP3421_SetDataRate(int data_rate)
{
    data_rate &= 0x3;
    g_reg = (g_reg & 0xf3) | (data_rate << 2);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, g_reg);
    g.stop_f(&g);
}
void MCP3421_SetGain(int gain)
{
    gain &= 0x3;
    g_reg = (g_reg & 0xfc) | (gain);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, g_reg);
    g.stop_f(&g);
}

signed long MCP3421_ReadData(void)
{
    long data = 0;
    unsigned char i;

    g.start_f(&g);
    g.writebyte_f(&g, CMD_READ);
    for(i = 0; i < 4; i++) {
        data <<= 8;
        if(i < 3)
            data |= g.readbyte_ack_f(&g);
        else
            data |= g.readbyte_nack_f(&g);
    }
    g.stop_f(&g);
    return data;
}
