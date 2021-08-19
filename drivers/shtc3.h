#ifndef _SHTC3_H
#define _SHTC3_H

#include "zi2c.h"
// i2c addr: 0x70

void SHTC3_ReadAll(zi2c_t* ps, unsigned char* data);

#endif
