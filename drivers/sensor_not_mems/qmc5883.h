#ifndef _QMC5883_I2C_H
#define _QMC5883_I2C_H

#include "misc.h"
#include "zi2c.h"

void QMC5883_Init(zi2c_t *i2c);
void QMC5883_Write(unsigned char* buf, int size);
void QMC5883_ReadAllRegs(void);

#endif
