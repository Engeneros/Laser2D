#ifndef LPC2148_I2C_REGS
#define LPC2148_I2C_REGS
#include <lpc214x.h>

volatile unsigned char* const I2C_CONSET[] = {&I2C0CONSET,  &I2C1CONSET};//,  &I22CONSET};
volatile unsigned char* const I2C_STAT[]   = {&I2C0STAT,   &I2C1STAT};//,        &I22STAT};
volatile unsigned char* const I2C_DAT[]    = {&I2C0DAT,    &I2C1DAT};//,         &I22DAT};
volatile unsigned char* const I2C_ADR[]    = {&I2C0ADR,     &I2C1ADR};//,         &I22ADR};
volatile unsigned short* const I2C_SCLH[]  = {&I2C0SCLH,     &I2C1SCLH};//,       &I22SCLH};
volatile unsigned short* const I2C_SCLL[]  = {&I2C0SCLL,    &I2C1SCLL};//,        &I22SCLL};
volatile unsigned char* const I2C_CONCLR[] = {&I2C0CONCLR,   &I2C1CONCLR};//,  &I22CONCLR};

#endif

