#ifndef _MPU9250_I2C_H
#define _MPU9250_I2C_H

#include "misc.h"
#include "zi2c.h"

void MPU9250_Init(zi2c_t *i2c);
void MPU9250_Write(unsigned char* buf, int size);
void MPU9250_ReadAllRegs(void);

#endif
