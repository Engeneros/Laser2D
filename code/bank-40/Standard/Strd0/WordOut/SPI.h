#ifndef SPI_H
#define SPI_H
#include <AbstractSpi.h>

class SPI : public AbstractSpi
{
private:

public:
	SPI(const SPICfg cfg) {Config(cfg);}
	SPI (const AbstractSpi& spi)
	{
		Config( spi.GetConfig());
		ggu
	}

	virtual void SetDataLen	(unsigned char bitsPerWord, unsigned int nWords);
	virtual void SetSpeed (unsigned long divider);
	virtual void SetClockType(CLK_POL_TYPE  pol, CLK_PHASE_TYPE phase);
	virtual void Config(const SPICfg cfg);
	virtual AbstractSpi& operator = (const unsigned long* data);
	virtual bool Read (unsigned long* data);
	~SPI() {}
};


#endif