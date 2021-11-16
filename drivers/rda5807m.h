#ifndef _RDA5807MS_I2C_H
#define _RDA5807MS_I2C_H

#include "misc.h"
#include "zi2c.h"

void RDA5807MS_Init(zi2c_t* i2c);
void RDA5807MS_ReadRegAll(void (*visit_f)(int, unsigned short));
void RDA5807MS_SetFreq(unsigned short freq);
void RDA5807MS_Tune(void);
void RDA5807MS_Seek_UP(void);
void RDA5807MS_Seek_DOWN(void);
void RDA5807MS_Volume_UP(void);
void RDA5807MS_Volume_DOWN(void);

#endif
