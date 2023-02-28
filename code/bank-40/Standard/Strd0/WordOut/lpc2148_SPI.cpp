#include <lpc2148_SPI.h>
#include <lpc2148_SPI_Regs.h>
//#include <lpc214x.h>
#include <Service.h>

SSP::SSP(const SPICfg cfg)
{
	SSPCR1 = 2;
	ctlRgVal  = 0x0400;
	PCfg(0, 17, 2);
	PCfg(0, 18, 2);
	PCfg(0, 19, 2);
	Config(cfg);
	mask = 0;
	unsigned short tmp = 1;
	for( int i = bitsPerWord; i > 0; --i)
	{
		mask |= tmp;
		tmp <<= 1;
	}
}

void SSP::SetDataLen	(unsigned int len)
{
	unsigned  int nBit ; 
	if( len  < 17)
	{
		nWrd = 1;
		nBit = len;		
	}
	else
	{
		nBit = 16;
		unsigned  int  rem;
		do
		{
			rem = len % nBit;
		}   while (rem != 0 && --nBit > 3);
		nWrd = len / nBit;
	}
	ctlRgVal &= ~0x0000000f;
	nBitsVal = nBit -1;
	ctlRgVal |= nBitsVal;	
	bitTotLen = len;
	bitsPerWord = nBit;
}

void SSP::SetSpeed (unsigned long divider)
{
	divRgVal = divider;
}

void SSP::SetClockType ( CLK_POL_TYPE  pol, CLK_PHASE_TYPE phase )
{
	unsigned long cLev = (pol ==  CLK_LOW)?  CLK_POL_LOW : CLK_POL_HIGH ;
	unsigned long cPh =  (phase == CLK_FIRST)? CLK_PHASE_FIRST : CLK_PHASE_SECOND; 
	ctlRgVal &= ~(3 << 6);
	ctlRgVal |= cLev | cPh;
	clkVal = cLev | cPh;
}

void SSP::HwPrepareDataLen()
{
	SSPCR0	 &= ~0x0000000f;
	SSPCR0 |= nBitsVal;
}

void SSP::HwPrepareSpeed()
{
	SSPCPSR = divRgVal;
}
void SSP::HwPrepareClock()
{
	SSPCR0 &= ~(3 << 6);
	SSPCR0 |= clkVal;
}

//#include <BoardDevices.h>
//#include <stdio.h>
void SSP::HwPrepare()
{
//	static int cnt = 1000;
//	if(--cnt == 0)
//	{
//		char buf [128];
//		cnt = 1000;
//		sprintf(buf, " SSPCR = %d%c%c", ctlRgVal, 13, 10);
//		uartTx1.Send(buf);
//	}
	unsigned short tmp = SSPDR;
	tmp = SSPDR;
	SSPCPSR = divRgVal;
	SSPCR0 = ctlRgVal;
}
	
bool SSP::IsReady ()
{
	return ( (SSPSR & BUSY_BIT) == 0)? true : false;
}

void SSP::Write (unsigned long data)
{
	for( int  pos = bitTotLen; pos > 0;  data >>= bitsPerWord)
	{				
		SSPDR = data &  mask;
		pos -= bitsPerWord;
	}		
}

bool SSP::Read (unsigned long* data)
{
	bool ret = ( (SSPSR & BUSY_BIT) == 0)? true : false;
	*data = 0;
	unsigned long tmpData = 0;
	if (ret != false)
	{
		for( int  pos = bitTotLen; pos > 0;  *data <<= bitsPerWord)
		{		
			tmpData = SSPDR ;	
			*data |= tmpData & mask;
			pos -= bitsPerWord;
		}		
	}
	return ret;
}
#include <BoardDevices.h>
void SSP::TxWord (unsigned long data)
{
	SSPDR = data;
}

bool SSP::RxWord (unsigned long* data) 
{
//	bool ret = ( (SSPSR & BUSY_BIT) == 0)? true : false;
	bool ret = ( (SSPSR & RNE_BIT) != 0)? true : false;
	*data =  (ret != false)? SSPDR : *data;
	return ret;
}

bool SSP::RxWordUltimate(unsigned long* data) 
{
	bool ret = ( (SSPSR &  RNE_BIT) != 0)? true : false;
	*data =  SSPDR;
	return ret;
}

/////////////////////////////////


SPI::SPI(const SPICfg cfg)
{
	PCfg (0, 4, 1);
	PCfg (0, 5, 1);
	PCfg (0, 6, 1);
	ctlRgVal = 4  | (1 << 5);
	Config(cfg);
	
	S0SPCR = ctlRgVal;
	mask = 0;
	unsigned short tmp = 1;
	for(int i = bitsPerWord; i > 0; --i)
	{
		mask |= tmp;
		tmp <<= 1;
	}
}
#include <stdio.h>
#include <boardDevices.h>
void SPI::SetDataLen	(unsigned int len)
{
	unsigned  int nBit ;
	if( len  < 17)
	{
		nWrd = 1;
		nBit = len;
	}
	else
	{
		unsigned  int  rem;
		nBit  = 16;
		do
		{
			rem = len % nBit;
		}   while (rem != 0 && --nBit > 7);
		nWrd = len / nBit;
	}
	nBitsVal = ( nBit & 0xf ) << 8;
	ctlRgVal &= ~0x00000f00;
	ctlRgVal |= nBitsVal;
	bitTotLen =  len;
	bitsPerWord = nBit;
//	char buff[64];
//	sprintf (buff, "nWrd = %d, len = %d, nBit = %d%c%c" , nWrd, len, nBit, 13, 10);
//	uartTx1.Send(buff);
	
}

void SPI::SetSpeed (unsigned long divider)
{
	divRgVal = divider;
}

void SPI::SetClockType ( CLK_POL_TYPE  pol, CLK_PHASE_TYPE phase )
{
	unsigned long cLev = pol  << 4;
	unsigned long cPh =  phase << 3; 
	ctlRgVal &= ~(3 << 3);
	ctlRgVal |= cLev | cPh;
	clkVal = cLev | cPh;
}

void SPI::HwPrepareDataLen()
{
	S0SPCR	 &= ~0x00000f00;
	S0SPCR |= nBitsVal;
}

void SPI::HwPrepareSpeed()
{
	S0SPCCR = divRgVal;
}
void SPI::HwPrepareClock()
{
	S0SPCR &= ~(3 << 3);
	S0SPCR |= clkVal;
}
void SPI::HwPrepare()
{
	S0SPCCR = divRgVal;
	S0SPCR = ctlRgVal;
}
	
bool SPI::IsReady ()
{
	return ( (S0SPSR & 0x80) != 0)? true : false;
}

void SPI::Write (unsigned long data)
{
	for( int  n = nWrd; n > 0;  --n)
	{		
//		vd10Green.Set();///fixx therearenofifo!!!!!!
		S0SPDR = 0x5555;//data &  mask;
//		vd10Green.Clear();
		//data >>= bitsPerWord;
	}		
}

bool SPI::Read (unsigned long* data)
{
	bool ret = ( (S0SPSR & 0x80) != 0)? true : false;
	*data = 0;
	unsigned long tmpData = 0;
	if (ret != false)
	{
		for( int  pos = bitTotLen; pos > 0;  *data <<= bitsPerWord)
		{		
			tmpData = S0SPDR ;	
			*data |= tmpData & mask;
			pos -= bitsPerWord;
		}		
	}
	return ret;
}

void SPI::TxWord (unsigned long data)
{
	S0SPDR = data;
}

bool SPI::RxWord (unsigned long* data) 
{
	bool ret = (  (S0SPSR & 0x80) != 0)? true : false;
	*data =  (ret != false)? S0SPDR : *data;
	return ret;
}

bool SPI::RxWordUltimate(unsigned long* data) 
{
	bool ret = ( (S0SPSR & 0x80) != 0)? true : false;
	*data =  S0SPDR;
	return ret;
}



