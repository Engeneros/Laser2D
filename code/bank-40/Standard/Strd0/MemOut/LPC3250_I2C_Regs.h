#ifndef LPC3250_I2C_REGS
#define LPC3250_I2C_REGS
#include <lpc325x.h>

/* I2C Interface 0 */
//#define I2C0_BASE_ADDR		0x400A0000
//#define I2C0_RX		(*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x00))
//#define I2C0_TX		(*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x00))
//#define I2C0_STS	(*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x04))
//#define I2C0_CTRL	(*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x08))
//#define I2C0_CLKH	(*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x0C))
//#define I2C0_CLKL	(*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x10))

///* I2C Interface 1 */
//#define I2C1_BASE_ADDR		0x400A8000
//#define I2C1_RX		(*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x00))
//#define I2C1_TX		(*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x00))
//#define I2C1_STS	(*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x04))
//#define I2C1_CTRL	(*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x08))
//#define I2C1_CLKH	(*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x0C))
//#define I2C1_CLKL	(*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x10))
//I2Cn_TXFL - 0x400A 001C, 0x400A 801C)
//I2Cn Receive FIFO level (I2Cn_RXFL - 0x400A 0018, 0x400A 8018)


#define I2C0_RX_FIFO_LEVEL	(*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x18))
#define I2C1_RX_FIFO_LEVEL	(*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x18))
#define I2C0_TX_FIFO_LEVEL	(*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x1C))
#define I2C1_TX_FIFO_LEVEL	(*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x1C))

volatile unsigned long* const I2C_RX_LVL[]  = { &I2C0_RX_FIFO_LEVEL, &I2C1_RX_FIFO_LEVEL };
volatile unsigned long* const I2C_TX_LVL[]  = { &I2C0_TX_FIFO_LEVEL, &I2C1_TX_FIFO_LEVEL };

volatile unsigned long* const I2C_TX_FIFO[]  = { &I2C0_TX, &I2C1_TX };
volatile unsigned long* const I2C_RX_FIFO[]  = { &I2C0_RX, &I2C1_RX };
volatile unsigned long* const I2C_CLK_H_DIV[] = {&I2C0_CLKH, &I2C1_CLKH};
volatile unsigned long* const I2C_CLK_L_DIV[] = {&I2C0_CLKL, &I2C1_CLKL};
volatile unsigned long* const I2C_STAT[] = {&I2C0_STS, &I2C1_STS};
volatile unsigned long* const I2C_CTL[] = {&I2C0_CTRL, &I2C1_CTRL};






//volatile unsigned long* const I2C_CONSET[]      =    {&I20CONSET,  &I21CONSET,  &I22CONSET};
//volatile unsigned long* const I2C_STAT[]         =    {&I20STAT,       &I21STAT,        &I22STAT};
//volatile unsigned long* const I2C_DAT[]           =    {&I20DAT,         &I21DAT,         &I22DAT};
//volatile unsigned long* const I2C_ADR[]           =   {&I20ADR,         &I21ADR,         &I22ADR};
//volatile unsigned long* const I2C_SCLH[]         =   {&I20SCLH,        &I21SCLH,       &I22SCLH};
//volatile unsigned long* const I2C_SCLL[]          =   {&I20SCLL,        &I21SCLL,        &I22SCLL};
//volatile unsigned long* const I2C_CONCLR[]    =   {&I20CONCLR,   &I21CONCLR,  &I22CONCLR};

#endif

