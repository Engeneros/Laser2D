#ifndef SSP_H
#define SSP_H
#include <AbstractIO.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\WordOut\SSP.h

enum CLK_POL_TYPE
{
	CLK_LOW = 0,
	CLK_HIGH =1
};

enum CLK_PHASE_TYPE
{
	CLK_FIRST = 0,
	CLK_SECOND = 1
};


class SSP : public AbstractIO
{
public:
	SSP  (unsigned int num);
	virtual void Tx(unsigned long data);
	virtual void FastTx(unsigned long data);
	virtual unsigned long TxRx (unsigned long data);
	virtual  unsigned long Rx();
	virtual unsigned long FastRx ();
	virtual ~ SSP() { }  ;	
protected:
	virtual void Wait() ;//{  while(  (*SSP0_SR & BUSY_BIT)   >   0) {}   }
	volatile unsigned long*  dataReg;
	volatile unsigned long*  statusReg;
};

class SSPifc : public AbstractIO
{
public:
	SSPifc  (AbstractIO* ssp, unsigned int num, unsigned char len, CLK_POL_TYPE clkLev, CLK_PHASE_TYPE ph, unsigned int div);
	virtual void Tx(unsigned long data);
	virtual void FastTx(unsigned long data);
	virtual unsigned long TxRx (unsigned long data);
	virtual  unsigned long Rx();
	virtual ~SSPifc() { }  	
protected:
	volatile unsigned long*  controlReg;
	volatile unsigned long*  divReg;
	void Configure();
	AbstractIO* sspCtl;
	unsigned int cDiv;
	unsigned long cfg;
};

class SSPifcFCM : public AbstractIO
{
public:
	SSPifcFCM  (unsigned int num, unsigned char len, CLK_POL_TYPE clkLev, CLK_PHASE_TYPE ph, unsigned int div);
	virtual void Tx(unsigned long data);
	virtual unsigned long TxRx (unsigned long data);
	virtual  unsigned long Rx();
	virtual ~SSPifcFCM () { }  	
private:
	volatile unsigned long*  dataReg;
	volatile unsigned long*  statusReg;
};

class SSPifcDbl : public SSPifc
{
public:
	SSPifcDbl(AbstractIO* ssp, unsigned int num, unsigned char len, CLK_POL_TYPE clkLev, CLK_PHASE_TYPE ph, unsigned int div);
	virtual void Tx (unsigned long data);
	virtual void FastTx(unsigned long data);
};
#endif



