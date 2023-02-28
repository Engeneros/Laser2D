#ifndef  AD5662_H
#define AD5662_H
#include <AbstractIO.h>
#include <AbstractPinOut.h>
#include <AbstractWordOut.h>

class AD5662 : public AbstractWordOut
{
public:
	AD5662 (AbstractIO* ssp, AbstractPinOut* chipSel);
	virtual void Send(unsigned long data);
	virtual ~AD5662(){}
protected:
	AbstractIO* ifc;
	AbstractPinOut* sync;
};
class AD5662Fast : public AbstractWordOut
{
public:
	AD5662Fast (AbstractIO* ssp, AbstractPinOut* chipSel);
	virtual void Send(unsigned long data);
	virtual ~AD5662Fast(){}
protected:
	AbstractIO* ifc;
	AbstractPinOut* sync;
};

#endif

//#ifndef AD53X8_H
//#define AD53X8_H
//#include <AbstractIO.h>
//#include <AbstractPinOut.h>
//#include <AbstractWordOut.h>

//class AD53x8 : public AbstractWordOut
//{
//public:
//	AD53x8 (AbstractIO* ssp, AbstractPinOut* synkPin, AbstractPinOut* loadPin);
//	virtual void Send(unsigned long data);
//	virtual ~AD53x8(){}
//protected:
//	AbstractIO* ifc;
//	AbstractPinOut* sync;
//};

//class AD5308ch  : public AbstractWordOut
//{
//public:
//	AD5308ch (AbstractWordOut* dac, unsigned long chan, unsigned long val = 0);
//	virtual void Send(unsigned long data);
//	virtual~AD5308ch() {}
//protected:
//	unsigned long preamble;
//	AbstractWordOut* chip;
//};

//class AD5328ch  : public AbstractWordOut
//{
//public:
//	AD5328ch (AbstractWordOut* dac, unsigned long chan, unsigned long val = 0);
//	virtual void Send(unsigned long data);
//	virtual~AD5328ch() {}
//protected:
//	unsigned long preamble;
//	AbstractWordOut* chip;
//};

//#endif

