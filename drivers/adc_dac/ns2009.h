#ifndef _NS2009_I2C_H
#define _NS2009_I2C_H

#include "zi2c.h"

#define XPT2046_FILTER_SIZE 8
#define XPT2046_FILTER_DIFF 30

typedef struct {
    unsigned short x, y;
} ns2009_coord_t;

void NS2009_Init(zi2c_t* i2c);
ns2009_coord_t NS2009_Read(void);
int NS2009_ReadX(void);
int NS2009_ReadY(void);

#endif
