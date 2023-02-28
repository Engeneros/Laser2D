#ifndef LPC2148_ADC_REGS_H
#define LPC2148_ADC_REGS_H
#ifdef LPC2148
#include <LPC214x.h>
volatile unsigned long* const ADC0_DATA_REGS[] = { &AD0DR0,  &AD0DR1,  &AD0DR2,  &AD0DR3,  &AD0DR4,  &AD0DR5,  &AD0DR6,  &AD0DR7};
volatile unsigned long* const ADC1_DATA_REGS[] = { &AD1DR0,  &AD1DR1,  &AD1DR2,  &AD1DR3,  &AD1DR4,  &AD1DR5,  &AD1DR6,  &AD1DR7};
#else
#include <LPC24xx.h>
volatile unsigned long* const ADC0_DATA_REGS[] = { &AD0DR0,  &AD0DR1,  &AD0DR2,  &AD0DR3,  &AD0DR4,  &AD0DR5,  &AD0DR6,  &AD0DR7};
#endif
#endif

