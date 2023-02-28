#ifndef LPC2478_SSP_REGS0_H
#define LPC2478_SSP_REGS0_H
#include <lpc24xx.h>
#include <SSP0.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\WordOut\LPC2478_SSP_Regs0.h

//const unsigned int CLOCK_POL = 6;
//const unsigned int CLOCK_PHASE = 7;
//const unsigned int CLK_DIVIDER = 8;

//const unsigned long CLK_POL_HIGH = CLK_HIGH << CLOCK_POL;
//const unsigned long CLK_POL_LOW = CLK_LOW << CLOCK_POL;
//const unsigned long CLK_PHASE_FIRST = CLK_FIRST << CLOCK_PHASE;
//const unsigned long CLK_PHASE_SECOND = CLK_SECOND << CLOCK_PHASE;
//const unsigned long SSP_ENABLE_AND_MASTER = 2;
//const  unsigned long BUSY_BIT = 1 << 4 ;


volatile unsigned long* const SSP_CR0[] =        {  &SSP0CR0,      &SSP1CR0};
volatile unsigned long* const SSP_CR1[] =        {  &SSP0CR1,      &SSP1CR1};
volatile unsigned long* const SSP_DATA[] =      {  &SSP0DR,        &SSP1DR};
volatile unsigned long* const SSP_STATUS[] = {  &SSP0SR,        &SSP1SR};
volatile unsigned long* const SSP_PREDVD[] = {  &SSP0CPSR,  &SSP1CPSR};

volatile unsigned long* const SSP_IMSC[]  =  { &SSP0IMSC, &SSP1IMSC};
volatile unsigned long* const SSP_RIS[] = { &SSP0RIS, &SSP1RIS};
volatile unsigned long* const SSP_MIS[] = { &SSP0MIS, &SSP1MIS};
volatile unsigned long* const SSP_CR[] = { &SSP0ICR, &SSP1ICR};



#endif




