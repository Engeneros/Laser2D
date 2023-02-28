#ifndef LPC2478_SSP_REGS_H
#define LPC2478_SSP_REGS_H
#include <lpc24xx.h>
#include <SSP.h>

const unsigned int CLOCK_POL = 6;
const unsigned int CLOCK_PHASE = 7;
const unsigned int CLK_DIVIDER = 8;

const unsigned long CLK_POL_HIGH = CLK_HIGH << CLOCK_POL;
const unsigned long CLK_POL_LOW = CLK_LOW << CLOCK_POL;
const unsigned long CLK_PHASE_FIRST = CLK_FIRST << CLOCK_PHASE;
const unsigned long CLK_PHASE_SECOND = CLK_SECOND << CLOCK_PHASE;
const unsigned long SSP_ENABLE_AND_MASTER = 2;
const  unsigned long BUSY_BIT = 1 << 4 ;


volatile unsigned long* const SSP_CR0[] =        {  &SSP0CR0,      &SSP1CR0};
volatile unsigned long* const SSP_CR1[] =        {  &SSP0CR1,      &SSP1CR1};
volatile unsigned long* const SSP_DATA[] =      {  &SSP0DR,        &SSP1DR};
volatile unsigned long* const SSP_STATUS[] = {  &SSP0SR,        &SSP1SR};
volatile unsigned long* const SSP_PREDVD[] = {  &SSP0CPSR,  &SSP1CPSR};




#endif




