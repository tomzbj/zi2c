#ifndef _CCS811_I2C_H
#define _CCS811_I2C_H

#include "misc.h"
#include "zi2c.h"

void CCS811_Init(zi2c_t *i2c);
void CCS811_Write(unsigned char* buf, int size);
void CCS811_ReadAllRegs(void);

#endif
