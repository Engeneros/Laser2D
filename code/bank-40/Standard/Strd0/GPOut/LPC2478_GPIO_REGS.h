#ifndef LPC2478_GPIO_REGS_H
#define LPC2478_GPIO_REGS_H
#include <LPC24xx.h>

volatile unsigned long* const GPIO_DIR_REG[] = {  &IODIR0,  &IODIR1,  &FIO2DIR, &FIO3DIR,  &FIO4DIR};//(volatile unsigned char*) 0xE000C00C, (volatile unsigned char*) 0xE001000C,  (volatile unsigned char*) 0xE007800C, (volatile unsigned char*)   0xE007C00C,};
volatile unsigned long* const GPIO_PIN_REG[] = {  &IOPIN0,  &IOPIN1,  &FIO2PIN, &FIO3PIN,  &FIO4PIN};
volatile unsigned long* const GPIO_SET_REG[] = {  &IOSET0,  &IOSET1,  &FIO2SET, &FIO3SET,  &FIO4SET};
volatile unsigned long* const GPIO_CLR_REG[] = {  &IOCLR0,  &IOCLR1,  &FIO2CLR, &FIO3CLR,  &FIO4CLR};
#endif


