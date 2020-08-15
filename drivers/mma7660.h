#ifndef _MMA7660_I2C_H
#define _MMA7660_I2C_H

#include "misc.h"
#include "zi2c.h"

typedef struct {
    signed char x, y, z;
} mma7660_data_t;
void MMA7660_Init(zi2c_t* i2c);
void MMA7660_ReadAllRegs(void);
mma7660_data_t MMA7660_Read(void);

#endif
