#include <LPC2148_SSP_Regs.h>


SSP::SSP (unsigned int num)
{	
	dataReg = SSP_DATA[num];
	statusReg = SSP_STATUS[num];
	*SSP_CR1 [num] = SSP_ENABLE_AND_MASTER;
}

void SSP::Tx(unsigned long data)
{
	*dataReg = data;
	Wait();
	unsigned long ret = *dataReg;
}

void SSP::FastTx(unsigned long  data)
{
	*dataReg = data;
}


unsigned long SSP::Rx()
{
	*dataReg = 0;
	Wait();
	return *dataReg;
}

unsigned long SSP::FastRx()
{
	Wait();
	return *dataReg;
}
	

unsigned long SSP::TxRx (unsigned long data)
{
	*dataReg = data;
	Wait();
	return *dataReg;
}

void SSP::Wait()
{ 
	while(  (*statusReg & BUSY_BIT)   !=   0) 
	{
	}  
};

////////////////////
	
SSPifc::SSPifc (AbstractIO* ssp,  unsigned int num, unsigned char len, CLK_POL_TYPE clkLev, CLK_PHASE_TYPE ph, unsigned int div)
{
	unsigned long cLev = (clkLev ==  CLK_LOW)?  CLK_POL_LOW : CLK_POL_HIGH ;
	unsigned long cPh = (ph == CLK_FIRST)? CLK_PHASE_FIRST : CLK_PHASE_SECOND; 
	cfg = (len-1) | cLev | cPh;
	cDiv = div;
	sspCtl = ssp;
	controlReg = SSP_CR0[num];
	divReg = SSP_PREDVD[num];
}

void SSPifc::Configure()
{
	*controlReg =   cfg;
	*divReg = cDiv;
}

void SSPifc::Tx(unsigned long data)
{
	Configure();
	sspCtl->Tx(data);
}

void SSPifc::FastTx(unsigned long data)
{
	Configure();
	sspCtl->FastTx(data);
}

unsigned long SSPifc::Rx()
{
	Configure();
	return sspCtl->Rx();
}
unsigned long SSPifc::TxRx (unsigned long data)
{
	Configure();
	return sspCtl->TxRx(data);
}
//////////////////////////////////////////////////////////////////////////////////
SSPifcFCM::SSPifcFCM( unsigned int num, unsigned char len, CLK_POL_TYPE clkLev, CLK_PHASE_TYPE ph, unsigned int div)
{
	dataReg = SSP_DATA[num];
	statusReg = SSP_STATUS[num];
	*SSP_CR1 [num] = SSP_ENABLE_AND_MASTER;
	unsigned long cLev = (clkLev ==  CLK_LOW)?  CLK_POL_LOW : CLK_POL_HIGH ;
	unsigned long cPh = (ph == CLK_FIRST)? CLK_PHASE_FIRST : CLK_PHASE_SECOND; 
	unsigned long  cfg = (len-1) | cLev | cPh;
	unsigned long  cDiv = div;

	*SSP_CR0[num] = cfg;
	*SSP_PREDVD[num] = cDiv;
}

//	virtual void Tx(unsigned long data);
//	virtual unsigned long TxRx (unsigned long data);
//	virtual  unsigned long Rx();
void SSPifcFCM::Tx(unsigned long data)
{
	while(  (*statusReg & BUSY_BIT)   !=   0) 
	{
	}  
	*dataReg = data;
}

unsigned long SSPifcFCM::Rx()
{
	return *dataReg;
}

unsigned long SSPifcFCM::TxRx(unsigned long data)
{
	Tx(data);
	return Rx();
}

////////////////////////////////////////////////////////////////////////////////////////
SSPifcDbl::SSPifcDbl(AbstractIO* ssp, unsigned int num, unsigned char len, CLK_POL_TYPE clkLev, CLK_PHASE_TYPE ph, unsigned int div) 
						: SSPifc  (ssp, num, len, clkLev, ph, div)
{
	
}

//#include <BoardDevices.h>
//#include <lpc24xx.h>
void SSPifcDbl::Tx( unsigned long data)
{
	Configure();
	unsigned long most4b = data >>12;
	unsigned long least12b = data &0xfff;
	sspCtl->FastTx(most4b);
	sspCtl->FastTx(least12b);
	sspCtl->FastRx();
	sspCtl->FastRx();
}

void set ( )
{
	FIO3SET = 1 <<  28;
}
void clr ( )
{
	FIO3CLR = 1 <<  28;
}

void SSPifcDbl::FastTx( unsigned long data)
{
//	sspCtl->FastRx();
//	sspCtl->FastRx();
//	GetOKLed1()->Toggle();
	Configure();
//	GetOKLed1()->Toggle();
	unsigned long most4b = data >>12;
	unsigned long least12b = data &0xfff;
	sspCtl->FastTx(most4b);
//	GetOKLed1()->Toggle();
	sspCtl->FastTx(least12b);
//	GetOKLed1()->Toggle();
//	GetOKLed1()->Toggle();//1.4uS / 1.4uS
	FIO3SET = 1 <<  28;//50nS  / 40nS
	FIO3CLR = 1 <<  28;
	set();//300nS / 40nS
	clr();
}
