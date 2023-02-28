#include <Service.h>
#include <LPC24xx.h>

//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\LPC2478Service.cpp

void PCfg(unsigned char portNumM, unsigned char portNumL, unsigned char func)
{
	unsigned long groupN = (unsigned long) portNumM;
	unsigned long pinN =  (unsigned long) portNumL;
	volatile unsigned long* const PIN_SEL_RG = &PINSEL0 + (groupN << 1) + ( (pinN  & 0x10)>> 4) ;
	pinN &= 0xf;
	*PIN_SEL_RG  &= ~(3 << pinN * 2);
	*PIN_SEL_RG |= func << pinN * 2;
}


//////////////===============Timers
void  IntervalGenerator(unsigned char nT, unsigned int nClk, unsigned long isrAddr)
{
	unsigned long baseAddr;
	switch(nT)
	{	
		case 0 :
			baseAddr = TMR0_BASE_ADDR;		
			break;
		case 1 : 
			baseAddr = TMR1_BASE_ADDR;	
			break;
		case 2 :
			baseAddr = TMR2_BASE_ADDR;		
			break;
		case 3 : 
			baseAddr = TMR3_BASE_ADDR;	
			break;
		default :
		break;	
	}	
	(*(volatile unsigned long *)(baseAddr + 0x04)) = 2;//T1TCR = 2; // Stop and reset timer.
	(*(volatile unsigned long *)(baseAddr + 0x0C)) = 0;//T1PR  = 0x00; // Set prescaler to zero.
	(*(volatile unsigned long *)(baseAddr + 0x18)) = nClk;//T1MR0 = nClk; // Set Value.
	(*(volatile unsigned long *)baseAddr) = 0xff;//T1IR  = 0xff; // Reset all interrrupt flags.
	(*(volatile unsigned long *)(baseAddr + 0x14)) = 3;//T1MCR = 3; // Timer reset and Interrupt
	switch(nT)
	{	
		case 0 : 
		{
			VICVectAddr4 = isrAddr;
		    VICVectCntl4 = 0x20 | 4;     // use it for Timer 0 Interrupt
		    VICIntEnable |= 0x00000010;  // Enable Timer0 Interrupt
		}
			break;
		case 1 :
		{
			VICVectAddr5 = isrAddr;
		    VICVectCntl5 = 0x20 | 5;                     
		    VICIntEnable |= 0x00000020;                   
		}
			break;
		case 2 : 
		{
			VICVectAddr26 = isrAddr;
		    VICVectCntl26 = 0x20 | 26;     // use it for Timer 0 Interrupt
		    VICIntEnable |= 1 << 26;  // Enable Timer0 Interrupt
		}
			break;
		case 3 :
		{
			VICVectAddr27 = isrAddr;
		    VICVectCntl27 = 0x20 | 27;                     
		    VICIntEnable |= 1 << 27;
		}
			break;
		default:
			break;
	}
	(*(volatile unsigned long *)(baseAddr + 0x04)) = 1;//T1TCR = 1;
}

void TimerStop(unsigned char nT)
{	
	switch(nT)
	{	
		case 0 :	T0TCR  = 0;
			break;
		case 1 : 	T1TCR  = 0;
			break;
		case 2 :	T2TCR  = 0;
			break;
		case 3 : 	T3TCR  = 0;
			break;
		default:
			break;
	}
}

void TimerStart(unsigned char nT)
{
	switch(nT)
	{	
		case 0 :	T0TCR  = 1;
			break;
		case 1 : 	T1TCR  = 1;
			break;
		case 2 :	T2TCR  = 1;
			break;
		case 3 : 	T3TCR  = 1;
			break;
		default:
			break;
	}
}
void TimerReset(unsigned char nT)
{
	switch(nT)
	{	
		case 0 :	T0TCR  = 2;
			break;
		case 1 : 	T1TCR  = 2;
			break;
		default:
			break;
	}
}
