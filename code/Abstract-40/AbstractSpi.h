#ifndef ABSTRACT_SPI
#define  ABSTRACT_SPI


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


struct SPICfg
{
	unsigned int len;
	unsigned long div;
	CLK_POL_TYPE pol;
	CLK_PHASE_TYPE phase;
	
	SPICfg(unsigned int dataLn, unsigned long clkDiv, CLK_POL_TYPE clkPol, CLK_PHASE_TYPE clkPhase)
	{
		len = dataLn;
		div = clkDiv;
		pol = clkPol;
		phase = clkPhase;
	}	
};



class AbstractSpi
{
protected:
	unsigned int nWrd;
public:
//hw independed	
	virtual void Config(const SPICfg& cfg)
	{
		SetDataLen (cfg.len);
		SetSpeed( cfg.div);
		SetClockType( cfg.pol, cfg.phase);
	}
//hw	
	virtual void SetDataLen	(unsigned int len) = 0;
	virtual void SetSpeed (unsigned long divider) = 0;
	virtual void SetClockType(CLK_POL_TYPE  pol, CLK_PHASE_TYPE phase) = 0;
//	virtual const SPICfg*  GetConfig ( ) const = 0; 
	virtual void HwPrepareDataLen() = 0;
	virtual void HwPrepareSpeed() = 0;
	virtual  void HwPrepareClock() = 0;
	virtual void HwPrepare() = 0;
	
//	virtual AbstractSpi& operator << (const unsigned long* data) = 0;
	virtual bool IsReady ()  =  0;
	virtual void Write (unsigned long data) = 0;
	virtual bool Read (unsigned long* data) = 0;
	virtual void TxWord (unsigned long data) = 0;
	virtual bool RxWord (unsigned long* data) = 0;
	virtual bool RxWordUltimate(unsigned long*data) = 0;
	virtual ~AbstractSpi() {}
};
#endif
//	virtual void Config(unsigned char bitsPerWord, unsigned int nWords, unsigned long devider,  CLK_POL_TYPE  pol, CLK_PHASE_TYPE phase) 
//	{
//		SetDataLen (bitsPerWord, nWords);
//		SetSpeed (devider);
//		SetClockType (pol, phase);
//	}
