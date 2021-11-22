#include "shtc3.h"
#include "zi2c.h"

#define  CMD_WRITE (ps->addr << 1)
#define  CMD_READ (CMD_WRITE + 1)

void SHTC3_ReadAll(zi2c_t* ps, unsigned char* data)
{
    ps->start_f(ps);
    ps->writebyte_f(ps, CMD_WRITE);
    ps->writebyte_f(ps, 0x35);
    ps->writebyte_f(ps, 0x17);
    ps->stop_f(ps);

//    _delay_ms(25);

    ps->start_f(ps);
    ps->writebyte_f(ps, CMD_WRITE);
    ps->writebyte_f(ps, 0x7c);
    ps->writebyte_f(ps, 0xa2);
    ps->stop_f(ps);

//    _delay_ms(25);

    ps->start_f(ps);
    ps->writebyte_f(ps, CMD_READ);
    for(int i = 0; i < 6; i++) {
        if(i < 6 - 1)
            data[i] = ps->readbyte_ack_f(ps);
        else
            data[i] = ps->readbyte_nack_f(ps);
    }
    ps->stop_f(ps);
}
