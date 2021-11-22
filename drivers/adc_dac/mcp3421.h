#ifndef _MCP3421_H
#define _MCP3421_H

#include "zi2c.h"

// default addr = 0x68

enum {
    MCP3421_MODE_SINGLE_CONV = 0, MCP3421_MODE_CONTINUOUS_CONV = 1,
    MCP3421_DATA_RATE_240 = 0, MCP3421_DATA_RATE_60 = 1,
    MCP3421_DATA_RATE_15 = 2, MCP3421_DATA_RATE_3_75 = 3, MCP3421_GAIN_1X = 0,
    MCP3421_GAIN_2X = 1, MCP3421_GAIN_4X = 2, MCP3421_GAIN_8X = 3
};

void MCP3421_StartConv(void);
signed long MCP3421_ReadData(void);
void MCP3421_Init(zi2c_t* i2c);
void MCP3421_SetMode(int mode);
void MCP3421_SetDataRate(int datarate);
void MCP3421_SetGain(int gain);

#endif
