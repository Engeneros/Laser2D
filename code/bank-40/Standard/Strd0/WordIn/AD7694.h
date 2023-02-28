#ifndef AD7694_H
#define AD7694_H
#include <AbstractIO.h>
#include  <AbstractWordIn.h>
//#include <AbstractWordOut.h>
#include <AbstractPinOut.h>

class AD7694 : public AbstractWordIn
{
public:
	AD7694 (AbstractIO* ssp, AbstractPinOut* chipSel);
	virtual  unsigned long  Read();
	virtual ~AD7694() {}
protected:
	AbstractPinOut* cSel;
	AbstractIO* ifc;
};

#endif

