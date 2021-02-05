#include "zi2c.h"
#include "ns2009.h"

static zi2c_t g;

#define  CMD_WRITE (g.addr << 1)
#define  CMD_READ ((g.addr << 1) + 1)

static unsigned short read_reg(unsigned char reg)
{
    unsigned short val = 0;
    g.start_f(&g);
    g.writebyte_f(&g, CMD_WRITE);
    g.writebyte_f(&g, reg);
    g.start_f(&g);
    g.writebyte_f(&g, CMD_READ);
    val = g.readbyte_ack_f(&g);
    val <<= 8;
    val |= g.readbyte_ack_f(&g);
    g.stop_f(&g);
    return val >> 4;
}

void NS2009_Init(zi2c_t* obj)
{
    g = *obj;
}

static unsigned short __read(unsigned char c)
{
    unsigned short t, sum = 0;
    unsigned short data[NS2009_FILTER_SIZE];

    for(int i = 0; i < NS2009_FILTER_SIZE; i++)
        data[i] = read_reg(c);

    for(int i = 0; i < NS2009_FILTER_SIZE - 1; i++) {
        for(int j = i + 1; j < NS2009_FILTER_SIZE; j++) {
            if(data[i] < data[j]) {
                ( {  t = data[i]; data[i] = data[j]; data[j] = t;});
            }
        }
    }
    for(int i = NS2009_FILTER_SIZE / 4; i < NS2009_FILTER_SIZE * 3 / 4; i++)
        sum += data[i];

    return sum / (NS2009_FILTER_SIZE / 2);
}
#define abs(x) ((x) > 0?(x):(-x))

ns2009_coord_t NS2009_Read(void)
{
    static ns2009_coord_t c;
    unsigned short t1, t2;
    t1 = __read(0x84);
    t2 = __read(0x84);
    if(abs(t2 - t1) < NS2009_FILTER_DIFF)
        c.x = (t1 + t2) / 2;
    t1 = __read(0x94);
    t2 = __read(0x94);
    if(abs(t2 - t1) < NS2009_FILTER_DIFF)
        c.y = (t1 + t2) / 2;

    return c;
}

int NS2009_ReadX(void)
{
    unsigned short t1, t2;
    t1 = __read(0x84);
    t2 = __read(0x84);
    if(abs(t2 - t1) < NS2009_FILTER_DIFF) {
        return (t1 + t2) / 2;
    }
    else
        return -1;
}

int NS2009_ReadY(void)
{
    unsigned short t1, t2;
    t1 = __read(0x94);
    t2 = __read(0x94);
    if(abs(t2 - t1) < NS2009_FILTER_DIFF) {
        return (t1 + t2) / 2;
    }
    else
        return -1;
}
