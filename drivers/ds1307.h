#ifndef _DS1307_I2C_H
#define _DS1307_I2C_H

#include "zi2c.h"

void DS1307_Init(zi2c_t* i2c);
void DS1307_ReadData(void* buf, int size);

#endif
