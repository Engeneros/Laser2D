#ifndef LPC2478_SSP_REGS_H
#define LPC2478_SSP_REGS_H
#include <lpc214x.h>
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

/////* SPI0 (Serial Peripheral Interface 0) */
////#define S0SPCR          (*((volatile unsigned short*) 0xE0020000))
////#define S0SPSR          (*((volatile unsigned char *) 0xE0020004))
////#define S0SPDR          (*((volatile unsigned short*) 0xE0020008))
////#define S0SPCCR         (*((volatile unsigned char *) 0xE002000C))
////#define S0SPINT         (*((volatile unsigned char *) 0xE002001C))

/////* SSP Controller (SPI1) */
////#define SSPCR0          (*((volatile unsigned short*) 0xE0068000))
////#define SSPCR1          (*((volatile unsigned char *) 0xE0068004))
////#define SSPDR           (*((volatile unsigned short*) 0xE0068008))
////#define SSPSR           (*((volatile unsigned char *) 0xE006800C))
////#define SSPCPSR         (*((volatile unsigned char *) 0xE0068010))
////#define SSPIMSC         (*((volatile unsigned char *) 0xE0068014))
////#define SSPRIS          (*((volatile unsigned char *) 0xE0068018))
////#define SSPMIS          (*((volatile unsigned char *) 0xE006801C))
////#define SSPICR          (*((volatile unsigned char *) 0xE0068020))

volatile unsigned short* const SSP_CR0 =  &SSPCR0; //,      &SSP1CR0};
volatile unsigned char* const  SSP_CR1 =   &SSPCR1; //      &SSP1CR1};
volatile unsigned short* const SSP_DATA = &SSPDR; //,        &SSP1DR};
volatile unsigned char* const SSP_STATUS = &SSPSR; //,        &SSP1SR};
volatile unsigned char* const SSP_PREDVD = &SSPCPSR; //,  &SSP1CPSR};

#endif




