#ifndef LPC2478_TIMER_REGS_H
#define LPC2478_TIMER_REGS_H
#include <lpc24xx.h>

volatile unsigned long* const TIM_IR[] =       {  &T0IR ,  &T1IR ,&T2IR ,&T3IR };//1
volatile unsigned long* const TIM_TCR[] =   {  &T0TCR,  &T1TCR,  &T2TCR, &T3TCR};//2
volatile unsigned long* const TIM_TC[] =      {  &T0TC, &T1TC, &T2TC,  &T3TC};//3
volatile unsigned long* const  TIM_PR[] =     {  &T0PR, &T1PR, &T2PR, &T3PR};//4
volatile unsigned long* const  TIM_PC[] =     {  &T0PC, &T1PC, &T2PC, &T3PC};//5
volatile unsigned long* const  TIM_MCR[] =  { &T0MCR, &T1MCR, &T2MCR, &T3MCR};//6

volatile unsigned long* const  TIM_MR0[] =  { &T0MR0, &T1MR0, &T2MR0, &T3MR0};//7
volatile unsigned long* const  TIM_MR1[] =  { &T0MR1, &T1MR1, &T2MR1, &T3MR1};//8
volatile unsigned long* const  TIM_MR2[] =  { &T0MR2, &T1MR2, &T2MR2, &T3MR2};//9
volatile unsigned long* const  TIM_MR3[] =  { &T0MR3, &T1MR3, &T2MR3, &T3MR3};//10
volatile unsigned long* const* TIM_MR[] =   { TIM_MR0, TIM_MR1, TIM_MR2, TIM_MR3};//--

volatile unsigned long* const  TIM_CCR[] =  { &T0CCR, &T1CCR, &T2CCR, &T3CCR};//11
volatile unsigned long* const  TIM_CR0[] =   { &T0CR0, &T1CR0, &T2CR0, &T3CR0};//12
volatile unsigned long* const  TIM_CR1[] =   { &T0CR1, &T1CR1, &T2CR1, &T3CR1};//13
volatile unsigned long* const* TIM_CR[]  =   { TIM_CR0, TIM_CR1};


volatile unsigned long* const  TIM_EMR[] =  { &T0EMR, &T1EMR, &T2EMR, &T3EMR}; //14
volatile unsigned long* const  TIM_CTCR[] =  { &T0CTCR, &T1CTCR, &T2CTCR, &T3CTCR}; //15



/* Timer 0 */
//#define TMR0_BASE_ADDR		0xE0004000
//1#define T0IR           (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x00))
//2#define T0TCR          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x04))
//3#define T0TC           (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x08))
//4#define T0PR           (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x0C))
	//5#define T0PC           (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x10))
//6#define T0MCR          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x14))

//7#define T0MR0          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x18))
//8#define T0MR1          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x1C))
//9#define T0MR2          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x20))
//10#define T0MR3          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x24))

//11#define T0CCR          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x28))
//12#define T0CR0          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x2C))
//13#define T0CR1          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x30))

//14#define T0EMR          (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x3C))
//15#define T0CTCR         (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x70))
#endif


