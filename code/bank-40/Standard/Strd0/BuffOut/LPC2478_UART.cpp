#include <UART.h>
#include <LPC2478_UART_Regs.h>
#include <Service.h>
#include <LPC24xx.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\BuffOut\LPC2478_UART.cpp

UART::UART(unsigned int uartNum)//, unsigned long isrAddr)
{
	num = uartNum;
	if(num == 0)
	{
		PCfg(0,  2,  1);
		PCfg(0,  3,  1);
	}
	else  if(num == 1)
	{
		PCfg(2, 0, 2);
		PCfg(2, 1, 2); 
	}
	else if(num == 2)
	{
		PCfg(0, 10, 1);
		PCfg(0, 11, 1); 
		PCONP |= 1<< 24;//**150805
	}
	else if(num == 3)
	{
		PCfg(0, 0, 2);
		PCfg(0, 1, 2); 
		PCONP |= 1<< 25;
	}
	buff = UART_BUFFERS_REG[num];
	lineStat = UART_LSTAT_REG[num];
	*UART_LC_REG [num] = 0x8f;
	*UART_FDR_REG [num] = 0x7c;
	*UART_DLL_REG  [num] = 12; //115200	
	*UART_LC_REG    [num] = 3;
	*UART_FCR_REG [num] |= 0xc1; // fifo enable rx level = 14 characters
}

void UART::IntEnable ( unsigned long addr )
{
	if( num == 0 )
	{
		VICVectAddr6 = addr;
		VICVectCntl6 = 0x20 | 6;     // use it for Timer 0 Interrupt
		intEn = 0x00000040;
		intDis = ~0x00000040;
		VICIntEnable |= 0x00000040;  // Enable Timer0 Interrupt
		VICVectPriority6 = 5;
	}
	else if ( num == 1 )
	{
		intEn = 0x00000080;
		intDis = ~0x00000080;
		VICVectAddr7 = addr;
		VICVectCntl7 = 0x20 | 7;   		
		VICIntEnable |= 0x00000080;                   
		VICVectPriority7 = 6;
	}
	else if ( num == 2 )
	{
		intEn = 1 << 28;
		intDis = ~(1 << 28);
		VICVectAddr28 = addr;
		VICVectCntl28 = 0x20 | 28;                     
		VICIntEnable |= 1 << 28;
		VICVectPriority28 = 3;
	}
	else if ( num == 3 )
	{
		intEn = 1 << 29;
		intDis = ~(1 << 29);
		VICVectAddr29 = addr;
		VICVectCntl29 = 0x20 | 29;                     
		VICIntEnable |= 1 << 29;
		VICVectPriority29 = 4;
	}
}

void UART::DisableInt()
{
	*UART_IE_REG[num] &=  ~1;//VICIntEnable |= intEn;
}
void UART::EnableInt()
{
	*UART_IE_REG[num] |=  1;//VICIntEnable &= intDis;
}


void UART::SetRxISRAddr ( unsigned long addr )	
{
	*UART_IE_REG[num] |=  1;
	IntEnable(addr);
}

void UART::SetTxISRAddr ( unsigned long addr )	
{
	*UART_IE_REG[num] |= 2;
	IntEnable( addr );
}


bool UART::IsRxReady()
{
	return ( (*lineStat & 1) ==  0 )? false : true;
}

void UART::Tx(unsigned long data)
{
	*buff = (unsigned char) data;
}

void UART::Tx (const  unsigned char* data, unsigned int sz ) 
{
	unsigned char tmp;
	for(int i = 0; sz > 0; --sz)
	{
		tmp =  (unsigned char) data[i++];
		*buff = tmp;
	}	
}

bool UART ::IsTxReady()
{
	return ((*lineStat & 1 << 5) ==  0)? false : true;
}
	
unsigned long UART::Rx()
{
	return (unsigned long) *buff;
}

