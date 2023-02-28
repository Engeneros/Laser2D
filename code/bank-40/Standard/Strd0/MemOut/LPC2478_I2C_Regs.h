#ifndef LPC2478_I2C_REGS
#define LPC2478_I2C_REGS
#include <lpc24xx.h>

volatile unsigned long* const I2C_CONSET[]      =    {&I20CONSET,  &I21CONSET,  &I22CONSET};
volatile unsigned long* const I2C_STAT[]         =    {&I20STAT,       &I21STAT,        &I22STAT};
volatile unsigned long* const I2C_DAT[]           =    {&I20DAT,         &I21DAT,         &I22DAT};
volatile unsigned long* const I2C_ADR[]           =   {&I20ADR,         &I21ADR,         &I22ADR};
volatile unsigned long* const I2C_SCLH[]         =   {&I20SCLH,        &I21SCLH,       &I22SCLH};
volatile unsigned long* const I2C_SCLL[]          =   {&I20SCLL,        &I21SCLL,        &I22SCLL};
volatile unsigned long* const I2C_CONCLR[]    =   {&I20CONCLR,   &I21CONCLR,  &I22CONCLR};

#endif

