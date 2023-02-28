#include <I2ChwLPC3250.h>
#include <LPC3250_I2C_Regs.h>
#include <sleep.h>
#include <constants.h>


void I2Chw::IniHW()
{
	I2CCLK_CTRL = 1;
	*I2C_CTL [num] |= 0x100;
	
	*I2C_CLK_H_DIV[num] = *I2C_CLK_L_DIV [num] =  HCLK_VAL / 200000;

//	*CONCLR =  0x7c;
//	*SCLH = 1000;
//	*SCLL  = 1000;
//	*CONSET = 0x40;
}

bool I2Chw::SendByte(unsigned  char addr, char data)
{
	*TX_FIFO =  dAdrWr;
	*TX_FIFO = addr;
	*TX_FIFO = ( unsigned short ) data | 0x200;
	return true; 
}

bool I2Chw::SendFIFO (const char* data, unsigned char sz )
{	
	while (sz > 0)
	{
		*TX_FIFO = *data++;
		--sz;
	}
	while(*TX_LEV > 0)
	{
	}
	return true;
}

bool I2Chw::SendBuf ( unsigned  char addr, const char* data, unsigned char sz )
{
	*TX_FIFO =  dAdrWr;
	*TX_FIFO = addr;
	--sz;
	unsigned char currSz = (sz  <= 2) ? sz : 2;
	unsigned long	shift = 0;
	while (currSz > 0)
	{
		SendFIFO ( data + shift, currSz);
		shift += currSz;
		sz -= currSz;
		currSz = (sz  <= 4) ? sz : 4;
	}
	unsigned short	lastByte = *(data + shift);
	*TX_FIFO =  lastByte | 0x200;
	return true;
}

bool I2Chw::ReadByte( unsigned  char addr, char* data)
{
	*TX_FIFO = dAdrWr;
	*TX_FIFO = (unsigned short) addr;
	*TX_FIFO = dAdrRd;
	*TX_FIFO = 0x200;
	while(*TX_LEV > 0 )
	{
	}
	while(*RX_LEV > 0)
	{
		*data = *RX_FIFO;
	}
	return true;
}

bool I2Chw::ReadBuf (unsigned  char addr, char* data,  unsigned char sz)
{
	return true;
}

I2Chw::I2Chw(unsigned char ifcNum, unsigned char devAddr)
{
	dAdrWr = (unsigned short) devAddr << 1 | 0x100;
	dAdrRd = dAdrWr | 1;
	num = ifcNum;
	
	RX_FIFO = I2C_RX_FIFO [ num ];
	RX_LEV = I2C_RX_LVL[ num ];
	TX_FIFO = I2C_TX_FIFO [ num ];
	TX_LEV = I2C_TX_LVL[ num];
	
//	CONSET  = I2C_CONSET[num];
//	STAT = I2C_STAT[num];
//	DAT = I2C_DAT[num];
//	ADR = I2C_ADR[num];
//	SCLH = I2C_SCLH[num];
//	SCLL = I2C_SCLL[num];
//	CONCLR = I2C_CONCLR[num] ;
	IniHW();
}

//unsigned char I2Chw::Start()
//{
//	*CONSET = 0x20;   //STA = 1, set start flag
//	while((*CONSET & 8)  == 0)
//	{		
//	}
//	unsigned char ret = *STAT;		
//	*CONCLR = 0x20;
//	return ret;
//}

//unsigned char I2Chw::RawWrite( unsigned char data )
//{
//	*DAT = data;
//	*CONSET = 4;
//	*CONCLR = 8;
//	while((*CONSET & 8) == 0)
//	{
//	}
//	return  *STAT;		
//}

//void  I2Chw::StopWrite()
//{
//	*CONSET = 0x10;
//	*CONCLR = 8;
//}

//void I2Chw::StopRead ()
//{	
//	*CONSET = 0x10;
//	*CONCLR = 0xc;
////	(*(volatile unsigned long *)(I2C_BASE[ifcNum] )) = 0x10;
////	(*(volatile unsigned long *)(I2C_BASE[ifcNum] + 0x18 )) = 0xc;
//}

//unsigned char I2Chw::ContinuedRead(unsigned char* data)
//{
//	*CONSET = 4;//*CONCLR = 0xc; //(*(volatile unsigned long *)(I2C_BASE[ifcNum] + 0x18 )) = 0xc;//I2CxCONCLR
//	*CONCLR = 8;
//	while((*CONSET & 8)  == 0)            //I2CxCONSET
//	{
//	}
//	*data = *DAT;//(*(volatile unsigned long *)(I2C_BASE[ifcNum] + 8 ));//I2CxDAT
//	return  *STAT;//*(volatile unsigned long *)(I2C_BASE[ifcNum] + 4 );//I2CxSTAT	
//}

