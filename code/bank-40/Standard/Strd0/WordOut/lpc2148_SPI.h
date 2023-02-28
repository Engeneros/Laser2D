#ifndef SPI_H
#define SPI_H
#include <AbstractSpi.h>

class SSP : public AbstractSpi
{
public:
	SSP(const SPICfg cfg); 
//	SSP (const AbstractSpi& spi);
//	virtual const SPICfg*  GetConfig ( ) const; 
	virtual void SetDataLen	(unsigned int len) ;
	virtual void SetSpeed (unsigned long divider) ;
	virtual void SetClockType ( CLK_POL_TYPE  pol, CLK_PHASE_TYPE phase );
	virtual void HwPrepareDataLen();
	virtual void HwPrepareSpeed();
	virtual  void HwPrepareClock();
	virtual void HwPrepare();
	
//	virtual SSP& operator << (const unsigned long* data);
	virtual bool IsReady () ;
	virtual void Write (unsigned long data) ;
	virtual bool Read (unsigned long* data);
	virtual void TxWord (unsigned long data) ;
	virtual bool RxWord (unsigned long* data) ;
	virtual bool RxWordUltimate(unsigned long*data);
	virtual ~SSP() {}
private:
	unsigned long divRgVal;
	unsigned long ctlRgVal;
	unsigned long nBitsVal;
	unsigned long clkVal;
	unsigned int bitTotLen;
	unsigned int bitsPerWord;
	unsigned long mask;
};

class SPI : public AbstractSpi 
{
public:
	SPI ( const SPICfg cfg );
//	SSP (const AbstractSpi& spi);
//	virtual const SPICfg*  GetConfig ( ) const; 
	virtual void SetDataLen	( unsigned int len );
	virtual void SetSpeed ( unsigned long divider );
	virtual void SetClockType ( CLK_POL_TYPE  pol, CLK_PHASE_TYPE phase );
	virtual void HwPrepareDataLen();
	virtual void HwPrepareSpeed();
	virtual  void HwPrepareClock();
	virtual void HwPrepare();
	
//	virtual SSP& operator << (const unsigned long* data);
	virtual bool IsReady () ;
	virtual void Write (unsigned long data) ;
	virtual bool Read (unsigned long* data);
	virtual void TxWord (unsigned long data) ;
	virtual bool RxWord (unsigned long* data) ;
	virtual bool RxWordUltimate(unsigned long*data);
	virtual ~SPI() {}	
private:
	unsigned long divRgVal;
	unsigned long ctlRgVal;
	unsigned long nBitsVal;
	unsigned long clkVal;
	unsigned int bitTotLen;
	unsigned int bitsPerWord;
	unsigned long mask;
};

#endif
