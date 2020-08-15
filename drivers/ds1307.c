#include "ds1307.h"
#include "xprintf.h"

static zi2c_t g;

#define  CMD_WRITE (g.addr << 1)
#define  CMD_READ (CMD_WRITE + 1)

static void WriteReg(unsigned char reg, unsigned char data)
{
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, reg);
    g.writebyte_f(&g, data);
    g.stop_f(&g);
}

void DS1307_ReadData(void* buf, int size)
{
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, 0x00);
    g.stop_f(&g);

    g.start_f(&g);
    g.writebyte_f(&g, CMD_READ);
    for(int i = 0; i < size; i++) {
        if(i < size - 1) {
            *(unsigned char*)buf = g.readbyte_ack_f(&g);
        }
        else {
            *(unsigned char*)buf = g.readbyte_nack_f(&g);
        }
        buf++;
    }
    g.stop_f(&g);
}

void DS1307_Init(zi2c_t* cfg)
{
    g = *cfg;
    WriteReg(0x00, 0x00);
}
