#ifndef SSP_H
#define SSP_H
#include <AbstractIO.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\WordOut\SSP0.h

enum CLK_POL_TYPE
{
	CLK_LOW = 0,
	CLK_HIGH =1
};

enum CLK_PHASE_TYPE
{
	CLK_FIRST = 0,
	CLK_SECOND = 1
};

const unsigned int CLOCK_POL = 6;
const unsigned int CLOCK_PHASE = 7;
const unsigned int CLK_DIVIDER = 8;

const unsigned long CLK_POL_HIGH = CLK_HIGH << CLOCK_POL;
const unsigned long CLK_POL_LOW = CLK_LOW << CLOCK_POL;
const unsigned long CLK_PHASE_FIRST = CLK_FIRST << CLOCK_PHASE;
const unsigned long CLK_PHASE_SECOND = CLK_SECOND << CLOCK_PHASE;
const unsigned long SSP_ENABLE_AND_MASTER = 2;
const  unsigned long BUSY_BIT = 1 << 4 ;
//(  1, 16, CLK_LOW, CLK_SECOND, 4)

void  SSPini (unsigned char len, CLK_POL_TYPE clkLev, CLK_PHASE_TYPE ph, unsigned int div, unsigned char sspNum = 1);
void SSPIntIni(unsigned int isrAddr, unsigned char sspNum = 1);
void SSPrxIntEnable(unsigned char sspNum = 1);
void SSPrxIntDisable(unsigned char sspNum = 1);
void SSPTimOrxIntEnable(unsigned char sspNum = 1);
void SSPTimOrxDisable(unsigned char sspNum = 1);
void SSPtxIntEnable(unsigned char sspNum = 1);
void SSPtxIntDisable(unsigned char sspNum = 1);

#endif



