#ifndef _MCP4726_H
#define _MCP4726_H

#include "misc.h"
#include "zi2c.h"

enum {
    MCP4726_PD_NORMAL = 0, MCP4726_PD_1K = 1, MCP4726_PD_125K = 2,
    MCP4726_PD_640K = 3
};

enum {
    MCP4726_VREF_VDD_UNBUFFERED = 0, MCP4726_VREF_EXT_UNBUFFERED = 2,
    MCP4726_VREF_EXT_BUFFERED = 3
};

enum {
    MCP4726_GAIN_1X = 0, MCP4726_GAIN_2X = 1
};

void MCP4726_Init(zi2c_t* i2c, int pd, int vref, int gain);
void MCP4726_Write(unsigned short data);

#endif
