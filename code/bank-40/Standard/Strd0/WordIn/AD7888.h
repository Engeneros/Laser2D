#ifndef AD7888_H
#define AD7888_H
#include <AbstractIO.h>
#include  <AbstractWordIn.h>
#include <AbstractPinOut.h>

class AD7888
{
public:
	AD7888 (AbstractIO* ssp, AbstractPinOut* chipSel);
	unsigned long  Read(unsigned long cfg);
	~AD7888(){}
protected:
	AbstractPinOut* cSel;
	AbstractIO* ifc;
	unsigned long prevCfg;
};

class AD7888ch  : public AbstractWordIn
{
public:
	AD7888ch (AD7888* adc, unsigned long chan);
	virtual unsigned long Read();
	virtual~AD7888ch() {}
protected:
	unsigned long preamble;
	AD7888* chip;
};

class AD7888ConMd567
{
public:
	AD7888ConMd567(AbstractIO* ssp,  AbstractPinOut* chipSel);
	unsigned long  Read(unsigned char chan);
	void Router();
	~AD7888ConMd567(){}
private:
	AbstractPinOut* cSel;
	AbstractIO* ifc;
	unsigned short wrData [ 8 ];
	unsigned short rdData [ 8] ;
	unsigned char wrChan, rdChan;
};


#endif

